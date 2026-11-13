#!/usr/bin/env bash
set -euo pipefail

# Paths and environment setup
cd "$(dirname "${BASH_SOURCE[0]}")"

CYQLONE_ROOT="$(cd ../.. && pwd)"
export CONAN_HOME="${CYQLONE_ROOT}/.conan2"

CONAN_JSON="conan.json"
PRESET_DEFAULT="conan-release"
RESULTS_DIR="${PWD}/results"

# User-configurable variables with defaults
: "${CONF_PRESET:=$PRESET_DEFAULT}"
: "${BUILD_PRESET:=$PRESET_DEFAULT}"
: "${OMP_NUM_THREADS:=8}"             # Total processor count p in the paper
: "${OMP_PLACES:=0:$OMP_NUM_THREADS}" # Bind to first CPU cores (ideally physical P-cores)


# -----------------------------------------------------------------------------
# Dependencies
# -----------------------------------------------------------------------------

deps() {
    local profiles=(
        "-pr:h"
        "${CYQLONE_ROOT}/scripts/dev/profiles/dev-minimal"
    )

    local profiles_dir="${CYQLONE_ROOT}/scripts/ci/conan-profiles/profiles"
    local with_mkl=False
    local editable=0
    local lock=0
    local extra_args=()

    while [[ $# -gt 0 ]]; do
        if [[ $1 = "--" ]]; then
            shift
            extra_args+=("$@")
            break
        fi

        case "$1" in
            --gcc)
                ;;

            --gcc-*)
                extra_args+=(
                    "-s:h"
                    "compiler.version=${1#--gcc-}"
                )
                ;;

            --clang*)
                profiles+=(
                    "-pr:h"
                    "${profiles_dir}/toolchain/clang-linux.profile"
                )
                export TTTAPA_CONAN_PROFILES_CLANG_SUFFIX="${1#--clang}"
                ;;

            --icx)
                profiles+=(
                    "-pr:h"
                    "${profiles_dir}/toolchain/icx-linux.profile"
                )
                ;;

            --with-mkl)
                with_mkl=True
                ;;

            --sccache)
                profiles+=(
                    "-pr:h"
                    "${profiles_dir}/sccache/only-self.profile"
                )
                ;;

            --editable|-e)
                editable=1
                ;;

            --lock)
                lock=1
                ;;

            --help|-h)
                echo "Usage: $0 {deps|all} [OPTIONS]" >&2
                echo "" >&2
                echo "Options:" >&2
                echo "  --gcc[-VERSION]  Use GCC toolchain (default)" >&2
                echo "  --clang[-SUFFIX] Use Clang toolchain, optional version suffix" >&2
                echo "  --icx            Use Intel oneAPI DPC++/C++ compiler" >&2
                echo "  --with-mkl       Build with MKL support (OpenBLAS by default)" >&2
                echo "  --editable,-e    Set up Cyqlone as editable Conan package" >&2
                echo "  --lock           Create or update Conan lockfile" >&2
                echo "  --sccache        Enable sccache (must be installed)" >&2
                echo "" >&2
                echo "Additional Conan arguments can be passed after '--'." >&2
                exit 0
                ;;

            *)
                echo "Unknown option '$1'. Use '$0 deps --help'." >&2
                exit 1
                ;;
        esac

        shift
    done

    if ! command -v conan &>/dev/null; then
        echo "Conan not found in PATH. Please install Conan 2.x and try again." >&2
        echo "https://conan.io" >&2
        exit 1
    fi

    set -x

    mkdir -p "${CONAN_HOME}"

    conan profile detect -e
    conan remote add \
        --force \
        cyqlone \
        "${CYQLONE_ROOT}/scripts/ci/conan-recipes"

    conan config install \
        "${CYQLONE_ROOT}/scripts/ci/conan-profiles/settings_user.yml"

    local conan_args=(
        "${profiles[@]}"

        -c tools.build:skip_test=True
        -o "guanaqo/*:with_mkl=${with_mkl}"
        -o "qpoases-e/*:with_mkl=${with_mkl}"

        # mold >= 2.41 requires C++20 in the build profile.
        -s:b compiler.cppstd=20

        --build=missing
        --lockfile-partial

        "${extra_args[@]}"
    )

    if [[ $editable -eq 1 ]]; then
        find "${CYQLONE_ROOT}/build" \
            -name CMakeCache.txt \
            -delete || :

        conan build \
            "${CYQLONE_ROOT}" \
            "${conan_args[@]}"

        conan editable add "${CYQLONE_ROOT}"
    else
        conan editable remove "${CYQLONE_ROOT}" || :
        conan export "${CYQLONE_ROOT}"
    fi

    if [[ $lock -eq 1 ]]; then
        conan lock create . "${conan_args[@]}"
        conan lock remove --requires="cyqlone/*"
    fi

    conan install . \
        "${conan_args[@]}" \
        --format=json > "${CONAN_JSON}"
}


# -----------------------------------------------------------------------------
# jq helper
# -----------------------------------------------------------------------------

_jq() {
    local jq_url="https://github.com/jqlang/jq/releases/download/jq-1.8.1/"
    local dest="${CYQLONE_ROOT}/.local/bin"

    export PATH="${dest}:${PATH}"

    if ! command -v jq &>/dev/null; then
        echo "jq not found in PATH. Downloading ..." >&2

        case "$(uname -s)-$(uname -m)" in
            Linux-x86_64)
                jq_url+="jq-linux-amd64"
                ;;
            Linux-aarch64)
                jq_url+="jq-linux-arm64"
                ;;
            Darwin-x86_64)
                jq_url+="jq-macos-amd64"
                ;;
            Darwin-arm64)
                jq_url+="jq-macos-arm64"
                ;;
            *)
                echo "Unsupported platform. Please install jq manually." >&2
                exit 1
                ;;
        esac

        mkdir -p "${dest}"

        if [[ ! -f "${dest}/.gitignore" ]]; then
            echo '*' > "${dest}/.gitignore"
        fi

        wget -O "${dest}/jq" "${jq_url}"
        chmod +x "${dest}/jq"
    fi

    jq "$@"
}


# -----------------------------------------------------------------------------
# Build and tests
# -----------------------------------------------------------------------------

build() {
    if [[ ! -f CMakeUserPresets.json || ! -f "${CONAN_JSON}" ]]; then
        echo "Conan files not found. Run '$0 deps' first." >&2
        exit 1
    fi

    local generators_folder
    generators_folder="$(
        _jq -r '.graph.nodes."0".generators_folder' "${CONAN_JSON}"
    )"

    set +ux
    # shellcheck disable=SC1090
    source "${generators_folder}/conanbuild.sh"
    set -ux

    cmake --fresh --preset "${CONF_PRESET}"
    cmake --build --preset "${BUILD_PRESET}"
}


tests() {
    if [[ ! -f CMakeUserPresets.json || ! -f "${CONAN_JSON}" ]]; then
        echo "Conan files not found. Run '$0 deps' and '$0 build' first." >&2
        exit 1
    fi

    local build_folder
    local generators_folder

    build_folder="$(
        _jq -r '.graph.nodes."0".build_folder' "${CONAN_JSON}"
    )"

    generators_folder="$(
        _jq -r '.graph.nodes."0".generators_folder' "${CONAN_JSON}"
    )"

    set +ux
    # shellcheck disable=SC1090
    source "${generators_folder}/conanrun.sh"
    set -ux

    cmake --build \
        --preset "${BUILD_PRESET}" \
        --target testing

    ctest \
        --test-dir "${build_folder}" \
        --output-on-failure
}


# -----------------------------------------------------------------------------
# Benchmark wrappers
# -----------------------------------------------------------------------------

run_benchmark() {
    local executable="$1"
    local result_file="$2"
    shift 2
    local args=()

    while [[ $# -gt 0 ]]; do
        case "$1" in
            --benchmark_out=*)
                result_file="${1#*=}"
                ;;
            --benchmark_out)
                if [[ $# -lt 2 ]]; then
                    echo "Missing filename after --benchmark_out." >&2
                    return 2
                fi
                result_file="$2"
                shift
                ;;
            *)
                args+=("$1")
                ;;
        esac
        shift
    done

    case "${result_file}" in
        /*) ;;
        results/*|./results/*) result_file="${PWD}/${result_file#./}" ;;
        *) result_file="${RESULTS_DIR}/${result_file}" ;;
    esac
    mkdir -p "$(dirname "${result_file}")"

    OMP_NUM_THREADS="${OMP_NUM_THREADS}" \
    OMP_PLACES="${OMP_PLACES}" \
    OMP_PROC_BIND=close \
    OMP_WAIT_POLICY=ACTIVE \
    OMP_DYNAMIC=FALSE \
        "${executable}" "${args[@]}" "--benchmark_out=${result_file}"
}


benchmark() {
    if [[ ! -f CMakeUserPresets.json || ! -f "${CONAN_JSON}" ]]; then
        echo "Conan files not found. Run '$0 deps' and '$0 build' first." >&2
        exit 1
    fi

    local build_folder
    local generators_folder

    build_folder="$(
        _jq -r '.graph.nodes."0".build_folder' "${CONAN_JSON}"
    )"

    generators_folder="$(
        _jq -r '.graph.nodes."0".generators_folder' "${CONAN_JSON}"
    )"

    set +ux
    # shellcheck disable=SC1090
    source "${generators_folder}/conanrun.sh"
    set -ux

    if [[ ! -x "${build_folder}/spring-mass" ]]; then
        echo "Benchmark executable not found. Run '$0 build' first." >&2
        exit 1
    fi

    run_benchmark "${build_folder}/spring-mass" benchmark-spring-mass.json "$@"
}


benchmark_quadruped() {
    if [[ ! -f CMakeUserPresets.json || ! -f "${CONAN_JSON}" ]]; then
        echo "Conan files not found. Run '$0 deps' and '$0 build' first." >&2
        exit 1
    fi

    local build_folder
    local generators_folder

    build_folder="$(
        _jq -r '.graph.nodes."0".build_folder' "${CONAN_JSON}"
    )"

    generators_folder="$(
        _jq -r '.graph.nodes."0".generators_folder' "${CONAN_JSON}"
    )"

    set +ux
    # shellcheck disable=SC1090
    source "${generators_folder}/conanrun.sh"
    set -ux

    if [[ ! -x "${build_folder}/centroidal-quadruped" ]]; then
        echo "Quadruped benchmark executable not found. Run '$0 build' first." >&2
        exit 1
    fi

    run_benchmark "${build_folder}/centroidal-quadruped" benchmark-quad.json \
        --benchmark_repetitions=1 \
        --benchmark_min_time=0.1s \
        "$@"
}


# -----------------------------------------------------------------------------
# Quick sanity check
# -----------------------------------------------------------------------------

benchmark_quick() {
    benchmark \
        --problem wang-boyd-2008 \
        --no-serial \
        -I 1 \
        -p "${OMP_NUM_THREADS}" \
        -N 16 \
        -M 12 \
        -J 2 \
        --benchmark_repetitions=1 \
        --benchmark_report_aggregates_only \
        --benchmark_min_time=0.01s \
        --benchmark_out=benchmark-quick.json \
        "$@"
}


# -----------------------------------------------------------------------------
# Figure 2: parallelism study
# -----------------------------------------------------------------------------

# Figure 2a:
# M = 12, J = 4, varying horizon N and (np, np_bar, nv).
benchmark_scaling_p() {
    benchmark \
        -I 1 \
        -p8 \
        -p4 \
        -v4 \
        -v1 \
        -M 12 \
        -J 4 \
        -N 32 64 96 128 160 192 224 256 \
        --benchmark_repetitions=10 \
        --benchmark_report_aggregates_only \
        --benchmark_min_time=0.01s \
        --benchmark_out=benchmark-scaling-p.json \
        "$@" \
        --no-hpipm \
        --no-treeqp \
        --no-piqp \
        --serial
}


# Figure 2b:
# M = 12, N = 64, varying number of branches J.
benchmark_scaling_J() {
    benchmark \
        -I 1 \
        -p "${OMP_NUM_THREADS}" \
        -v4 \
        -M 12 \
        -J 1 2 4 8 \
        -N 64 \
        --benchmark_repetitions=10 \
        --benchmark_report_aggregates_only \
        --benchmark_min_time=0.01s \
        --benchmark_out=benchmark-scaling-J.json \
        "$@" \
        --no-hpipm \
        --no-treeqp \
        --no-piqp \
        --serial
}


# -----------------------------------------------------------------------------
# Figures 3-4: spring-mass solver benchmarks
# -----------------------------------------------------------------------------

# Figure 3:
# M = 12, J = 4, varying horizon N.
benchmark_scaling() {
    benchmark \
        -I 10 \
        -p "${OMP_NUM_THREADS}" \
        -v4 \
        -M 12 \
        -N 32 64 96 128 160 192 224 256 \
        -J 4 \
        --benchmark_repetitions=3 \
        --benchmark_report_aggregates_only \
        --benchmark_min_time=0.01s \
        --benchmark_out=benchmark-scaling.json \
        "$@"
}


# Figure 4:
# N = 64, J = 4, varying number of masses M.
benchmark_scaling_states() {
    benchmark \
        --problem wang-boyd-2008 \
        -I 10 \
        -p "${OMP_NUM_THREADS}" \
        -v4 \
        -N 64 \
        -M6 \
        -M10 \
        -M14 \
        -M18 \
        -M22 \
        -M26 \
        -M30 \
        -J 4 \
        --benchmark_repetitions=3 \
        --benchmark_report_aggregates_only \
        --benchmark_min_time=0.01s \
        --benchmark_out=benchmark-scaling-states.json \
        "$@"
}


# -----------------------------------------------------------------------------
# Figures 5-6: quadruped solver benchmarks
# -----------------------------------------------------------------------------

# Figure 5:
# J = 4, varying horizon N.
benchmark_quad_scaling() {
    benchmark_quadruped \
        -I 10 \
        -p "${OMP_NUM_THREADS}" \
        -v4 \
        -N 32 64 96 128 160 192 224 256 \
        -J 4 \
        --benchmark_repetitions=3 \
        --benchmark_report_aggregates_only \
        --benchmark_min_time=0.01s \
        --benchmark_out=benchmark-quad-scaling.json \
        "$@"
}


# Figure 6:
# N = 64, varying number of branches J.
benchmark_quad_scaling_J() {
    benchmark_quadruped \
        -I 10 \
        -p "${OMP_NUM_THREADS}" \
        -v4 \
        -N 64 \
        -J 1 2 4 8 \
        --benchmark_repetitions=3 \
        --benchmark_report_aggregates_only \
        --benchmark_min_time=0.01s \
        --benchmark_out=benchmark-quad-scaling-J.json \
        "$@"
}


# -----------------------------------------------------------------------------
# Cleanup
# -----------------------------------------------------------------------------

clean() {
    set -x

    rm -rf \
        conan.json \
        build \
        CMakeUserPresets.json

    rm -f \
        "${RESULTS_DIR}/benchmark-grid.json" \
        "${RESULTS_DIR}/benchmark-spring-mass.json" \
        "${RESULTS_DIR}/benchmark-quick.json" \
        "${RESULTS_DIR}/benchmark-scaling.json" \
        "${RESULTS_DIR}/benchmark-scaling2.json" \
        "${RESULTS_DIR}/benchmark-scaling-p.json" \
        "${RESULTS_DIR}/benchmark-scaling-J.json" \
        "${RESULTS_DIR}/benchmark-scaling-states.json" \
        "${RESULTS_DIR}/benchmark-quad.json" \
        "${RESULTS_DIR}/benchmark-quad-scaling.json" \
        "${RESULTS_DIR}/benchmark-quad-scaling-J.json"
}


# -----------------------------------------------------------------------------
# CLI
# -----------------------------------------------------------------------------

main() {
    local cmd="${1:-help}"
    local exit_code=0

    if [[ $# -gt 0 ]]; then
        shift
    else
        exit_code=1
    fi

    case "${cmd}" in
        deps)
            deps "$@"
            ;;

        build)
            build
            ;;

        tests)
            tests
            ;;

        benchmark-quick)
            benchmark_quick "$@"
            ;;

        # Figure 2a
        benchmark-scaling-p)
            benchmark_scaling_p "$@"
            ;;

        # Figure 2b
        benchmark-scaling-J)
            benchmark_scaling_J "$@"
            ;;

        # Figure 3
        benchmark-scaling)
            benchmark_scaling "$@"
            ;;

        # Figure 4
        benchmark-scaling-states)
            benchmark_scaling_states "$@"
            ;;

        # Figure 5
        benchmark-quad-scaling)
            benchmark_quad_scaling "$@"
            ;;

        # Figure 6
        benchmark-quad-scaling-J)
            benchmark_quad_scaling_J "$@"
            ;;

        benchmark)
            benchmark "$@"
            ;;

        benchmark-quadruped)
            benchmark_quadruped "$@"
            ;;

        all)
            deps "$@"
            build

            benchmark_quick

            # Figure 2
            benchmark_scaling_p
            benchmark_scaling_J

            # Figures 3-4
            benchmark_scaling
            benchmark_scaling_states

            # Figures 5-6
            benchmark_quad_scaling
            benchmark_quad_scaling_J

            ;;

        clean)
            clean
            ;;

        help|-h|--help)
            echo "Usage: $0 COMMAND [OPTIONS]" >&2
            echo "" >&2
            echo "Build commands:" >&2
            echo "  deps [...]                 Install dependencies using Conan" >&2
            echo "  build                      Build the benchmark project" >&2
            echo "  tests                      Build and run tests" >&2
            echo "" >&2
            echo "Paper benchmarks:" >&2
            echo "  benchmark-scaling-p        Fig. 2a: horizon / processor scaling" >&2
            echo "  benchmark-scaling-J        Fig. 2b: branch scaling" >&2
            echo "  benchmark-scaling          Fig. 3: spring-mass horizon scaling" >&2
            echo "  benchmark-scaling-states   Fig. 4: spring-mass mass/state scaling" >&2
            echo "  benchmark-quad-scaling     Fig. 5: quadruped horizon scaling" >&2
            echo "  benchmark-quad-scaling-J   Fig. 6: quadruped branch scaling" >&2
            echo "" >&2
            echo "Other commands:" >&2
            echo "  benchmark-quick            Run a quick sanity benchmark" >&2
            echo "  benchmark [...]            Run a custom spring-mass benchmark" >&2
            echo "  benchmark-quadruped [...]  Run a custom quadruped benchmark" >&2
            echo "  all                        Build and run all paper benchmarks" >&2
            echo "  clean                      Remove build and benchmark outputs" >&2
            echo "" >&2
            echo "Benchmark JSON results are saved in ${RESULTS_DIR}." >&2
            echo "" >&2
            echo "Dependency options:" >&2
            echo "  Run '$0 deps --help' for Conan/toolchain options." >&2
            echo "" >&2
            echo "Environment variables:" >&2
            echo "  CONF_PRESET      CMake configure preset (default: conan-release)" >&2
            echo "  BUILD_PRESET     CMake build preset (default: conan-release)" >&2
            echo "  OMP_NUM_THREADS  Total processor count (default: 8)" >&2
            echo "  OMP_PLACES       OpenMP places (default: 0:\$OMP_NUM_THREADS)" >&2
            exit "${exit_code}"
            ;;

        *)
            echo "Unknown command '${cmd}'." >&2
            echo "Run '$0 help' for available commands." >&2
            exit 1
            ;;
    esac
}


main "$@"
