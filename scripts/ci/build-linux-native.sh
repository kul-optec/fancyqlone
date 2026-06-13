#!/usr/bin/env bash
cd "$( dirname "${BASH_SOURCE[0]}" )"/../..
set -ex

# Package and output directories
pkg_dir="${1:-.}"
out_dir="${2:-dist}"
install_stubs_dir="$3"

# Create a py-build-cmake config file
pbc_config="$PWD/native-py-build-cmake.local.pbc"
profiles="$PWD/scripts/ci/conan-profiles/profiles"
cat << EOF > "$pbc_config"
conan.profile_host=["default"]
conan.profile_host+=["$PWD/scripts/ci/profiles/unity.profile"]
conan.profile_host+=["$profiles/color/gcc.profile"]
conan.profile_host+=["$profiles/link/lto-auto.profile"]
conan.profile_host+=["$profiles/visibility/hidden.profile"]
conan.profile_host+=["$profiles/sccache/only-self.profile"]
conan.profile_host+=["$profiles/test/none.profile"]
conan.profile_host+=["$profiles/tools/ninja.profile"]
conan.args+=["-obatmat/*:with_openmp=True"]
conan.cmake.args+=["--fresh"]
conan.cmake.build_args+=["--verbose"]
conan.cmake.options.CYQLONE_WITH_PY_STUBS=true
EOF
if [ "$(uname -m)" = "x86_64" ]; then
    echo "conan.profile_host+=[\"$profiles/arch/linux/x86-64-v3.profile\"]" >> "$pbc_config"
fi

# Build the Python package (prefer uv)
if hash uv 2> /dev/null; then
    pbc_venv="$PWD/.venv-pbc"
    uv venv --clear "$pbc_venv"
    python_executable="$pbc_venv/bin/python"
    uv build --python "$pbc_venv/bin/python" \
        "$pkg_dir" --wheel --out-dir "$out_dir" --config-setting local="$pbc_config"
elif python3 -m pip --version > /dev/null 2>&1; then
    python3 -m pip install -U build
    python3 -m build -w "$pkg_dir" -o "$out_dir" -C local="$pbc_config"
else
    echo "No suitable build tool found (uv or pip)"
    exit 1
fi

# Install the Python stubs
if [ -n "$install_stubs_dir" ]; then
    if hash uv 2> /dev/null; then
        uv pip install --python "$python_executable" \
            'py-build-cmake~=0.6.0a2' 'numpy<3'
        pbc=( "$python_executable" -m py_build_cmake.cli -C "$pkg_dir" --local="$pbc_config" )
    else
        python_executable="$(which python3)"
        "$python_executable" -m pip install 'py-build-cmake~=0.6.0a2' 'numpy<3'
        pbc=( "$python_executable" -m py_build_cmake.cli -C "$pkg_dir" --local="$pbc_config" )
    fi
    # Determine Conan's build directory
    build_config="$("${pbc[@]}" build-config-name)"
    build_dir="$pkg_dir/.py-build-cmake_cache/build/$build_config/Release"
    # Activate the Conan build environment (ensures that CMake is in PATH)
    set +x; source "$build_dir/generators/conanbuild.sh"; set -x
    # Re-run CMake to change Python executable (old one is in a temporary venv)
    cmake "$build_dir" \
        -D "Python_EXECUTABLE=$python_executable" \
        -D "Python3_EXECUTABLE=$python_executable"
    # Install the binary modules into the source tree
    cmake --install "$build_dir" --prefix "$install_stubs_dir" \
        --component python_modules
    cmake --install "$build_dir" --prefix "$install_stubs_dir" \
        --component python_nanobind
    # Generate the stubs (using a complete tree including the binary modules)
    cmake --install "$build_dir" --prefix "$install_stubs_dir" \
        --component python_stubs
    # Then we remove the binary modules again (sdist is source only)
    while IFS= read -r f || [ -n "$f" ]; do rm -f "$f"
    done < "$build_dir/install_manifest_python_modules.txt"
    while IFS= read -r f || [ -n "$f" ]; do rm -f "$f"
    done < "$build_dir/install_manifest_python_nanobind.txt"
fi
