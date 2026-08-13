import os
import shutil
import subprocess
from conan import ConanFile
from conan.errors import ConanInvalidConfiguration
from conan.tools.build import build_jobs
from conan.tools.env import VirtualBuildEnv
from conan.tools.files import copy, load, save
from conan.tools.scm import Git


class TreeqpConan(ConanFile):
    name = "treeqp"
    version = "0.3.1"

    package_type = "static-library"

    license = "LGPL-3.0-or-later"
    url = "https://github.com/Matisse-Teuwen/treeQP"
    homepage = "https://github.com/Matisse-Teuwen/treeQP"
    description = "Tree-Sparse Quadratic Programming solver"

    topics = (
        "quadratic-programming",
        "optimization",
        "tree-sparse",
        "solver",
    )

    settings = (
        "os",
        "compiler",
        "build_type",
        "arch",
    )

    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "with_openmp": [True, False],
        "target": [
            "auto",
            "X64_AVX2",
            "X64_AVX",
            "X64_SSE3",
            "generic",
        ],
    }

    default_options = {
        "shared": False,
        "fPIC": True,
        "with_openmp": True,
        "target": "auto",
    }

    def build_requirements(self):
        self.tool_requires("make/[>=4.4 <5]")

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            raise ConanInvalidConfiguration(
                "TreeQP 0.3.1 only supports static libraries in this recipe. "
                "Use shared=False."
            )

        if self.settings.os == "Windows":
            raise ConanInvalidConfiguration(
                "This recipe uses TreeQP's Unix Make build and does not "
                "currently support Windows."
            )

        compiler = str(self.settings.compiler)

        if compiler not in (
            "gcc",
            "clang",
            "apple-clang",
        ):
            raise ConanInvalidConfiguration(
                "TreeQP's bundled HPMPC, HPIPM and BLASFEO projects are "
                "expected to be built with GCC or Clang."
            )



    # def _namespace_qpoases_linalg(self):
    #     makefile = os.path.join(
    #         self.source_folder,
    #         "external",
    #         "qpoases",
    #         "make_linux.mk",
    #     )

    #     if not os.path.isfile(makefile):
    #         raise RuntimeError(
    #             "qpOASES make_linux.mk was not found: {}".format(
    #                 makefile
    #             )
    #         )

    #     marker = "# Conan: namespace qpOASES_e linear algebra replacements"

    #     content = load(self, makefile)

    #     if marker in content:
    #         self.output.info(
    #             "qpOASES linear-algebra symbols are already patched"
    #         )
    #         return

    #     patch = textwrap.dedent(
    #         r"""

    #         # Conan: namespace qpOASES_e linear algebra replacements
    #         CFLAGS += \
    #             -Ddgemm_=qpoases_e_dgemm_ \
    #             -Dsgemm_=qpoases_e_sgemm_ \
    #             -Ddpotrf_=qpoases_e_dpotrf_ \
    #             -Dspotrf_=qpoases_e_spotrf_ \
    #             -Ddsyr_=qpoases_e_dsyr_ \
    #             -Dssyr_=qpoases_e_ssyr_ \
    #             -Ddsyr2_=qpoases_e_dsyr2_ \
    #             -Dssyr2_=qpoases_e_ssyr2_
    #         """
    #     )

    #     save(
    #         self,
    #         makefile,
    #         content + patch,
    #     )

    #     self.output.info(
    #         "Patched qpOASES linear-algebra symbols in {}".format(
    #             makefile
    #         )
    #     )
    def _namespace_qpoases_archive(self):
        archive = os.path.join(
            self.source_folder,
            "lib",
            "libqpoases.a",
        )

        if not os.path.isfile(archive):
            raise RuntimeError(
                "qpOASES archive was not created: {}".format(archive)
            )

        objcopy = (
            shutil.which("x86_64-bionic-linux-gnu-objcopy")
            or shutil.which("objcopy")
        )

        if objcopy is None:
            raise RuntimeError(
                "objcopy was not found. Add binutils to the build "
                "environment or expose the toolchain's objcopy in PATH."
            )

        command = [
            objcopy,
            "--redefine-sym",
            "dgemm_=qpoases_e_dgemm_",
            "--redefine-sym",
            "sgemm_=qpoases_e_sgemm_",
            "--redefine-sym",
            "dpotrf_=qpoases_e_dpotrf_",
            "--redefine-sym",
            "spotrf_=qpoases_e_spotrf_",
            archive,
        ]

        self.output.info(
            "Namespacing qpOASES BLAS/LAPACK symbols"
        )
        self.output.info(" ".join(command))

        subprocess.run(
            command,
            check=True,
        )

    def layout(self):
        self.folders.source = "src"
        self.folders.build = "build"
        self.folders.generators = "build/generators"

    def source(self):
        git = Git(self)

        git.clone(
            url="https://github.com/Matisse-Teuwen/treeQP.git",
            target=".",
        )

        # git.checkout(str(self.version))

        # Important: these revisions are pinned by TreeQP and therefore
        # compatible with each other.
        git.run("submodule update --init --recursive")

    def generate(self):
        VirtualBuildEnv(self).generate()

    def _append_additive_flags(self, makefile_path):
        """
        Add Conan compiler flags without replacing the target-specific
        compiler flags selected by the upstream project.
        """
        if not os.path.isfile(makefile_path):
            raise ConanInvalidConfiguration(
                "Required Makefile configuration was not found: {}".format(
                    makefile_path
                )
            )

        marker = "# Conan additive compiler flags"
        content = load(self, makefile_path)

        if marker in content:
            return

        content += (
            "\n"
            "{}\n"
            "override CFLAGS += $(CONAN_CFLAGS)\n"
            "override CXXFLAGS += $(CONAN_CXXFLAGS)\n"
        ).format(marker)

        save(self, makefile_path, content)

    def _patch_makefiles(self):
        """
        Apply additive flags to TreeQP and all bundled projects built by
        the top-level Makefile.
        """
        candidates = [
            os.path.join(
                self.source_folder,
                "Makefile.rule",
            ),
            os.path.join(
                self.source_folder,
                "external",
                "hpmpc",
                "Makefile.rule",
            ),
            os.path.join(
                self.source_folder,
                "external",
                "hpipm",
                "Makefile.rule",
            ),
            os.path.join(
                self.source_folder,
                "external",
                "blasfeo",
                "Makefile.rule",
            ),
        ]

        for candidate in candidates:
            if os.path.isfile(candidate):
                self._append_additive_flags(candidate)

    def _hpmpc_target(self):
        selected = str(self.options.target)

        if selected != "auto":
            if selected == "generic":
                return "C99_4X4"

            return selected

        arch = str(self.settings.arch)

        if arch == "x86_64":
            return "X64_AVX"

        if arch == "x86":
            return "X64_SSE3"

        return "C99_4X4"

    def _hpipm_target(self):
        selected = str(self.options.target)

        if selected != "auto":
            if selected == "generic":
                return "GENERIC"

            return selected

        arch = str(self.settings.arch)

        if arch == "x86_64":
            return "X64_AVX"

        if arch == "x86":
            return "X64_SSE3"

        return "GENERIC"

    def _blasfeo_target(self):
        selected = str(self.options.target)

        if selected != "auto":
            if selected == "generic":
                return "GENERIC"

            if selected == "X64_AVX2":
                # Older BLASFEO revisions commonly identify AVX2/FMA
                # x86-64 CPUs with this target.
                return "X64_INTEL_HASWELL"

            if selected == "X64_AVX":
                return "X64_INTEL_SANDY_BRIDGE"

            if selected == "X64_SSE3":
                return "X64_GENERIC"

        arch = str(self.settings.arch)

        if arch == "x86_64":
            return "X64_INTEL_SANDY_BRIDGE"

        return "GENERIC"

    def _make_arguments(self):
        bundled_blasfeo = os.path.join(
            self.source_folder,
            "external",
            "blasfeo",
        ).replace("\\", "/")

        arguments = [
            "OPENMP={}".format(
                "ON" if self.options.with_openmp else "OFF"
            ),

            # Build the bundled, revision-compatible BLASFEO.
            "SKIP_BLASFEO_COMPILATION=OFF",

            "BLASFEO_PATH='{}'".format(
                bundled_blasfeo
            ),

            "BLASFEO_TARGET={}".format(
                self._blasfeo_target()
            ),

            "HPMPC_TARGET={}".format(
                self._hpmpc_target()
            ),

            "HPIPM_TARGET={}".format(
                self._hpipm_target()
            ),
        ]

        if self.options.get_safe("fPIC"):
            arguments.extend([
                "CONAN_CFLAGS='-fPIC'",
                "CONAN_CXXFLAGS='-fPIC'",
            ])
        else:
            arguments.extend([
                "CONAN_CFLAGS=''",
                "CONAN_CXXFLAGS=''",
            ])

        return arguments

    def build(self):
        self._patch_makefiles()
        # self._namespace_qpoases_linalg()

        arguments = self._make_arguments()

        self.run(
            "make -j{} treeqp_cpp_interface {}".format(
                build_jobs(self),
                " ".join(arguments),
            ),
            cwd=self.source_folder,
        )
        self._namespace_qpoases_archive()

    def package(self):
        copy(
            self,
            "LICENSE*",
            src=self.source_folder,
            dst=os.path.join(
                self.package_folder,
                "licenses",
            ),
            keep_path=False,
        )

        # TreeQP headers.
        copy(
            self,
            "*.h",
            src=os.path.join(
                self.source_folder,
                "treeqp",
            ),
            dst=os.path.join(
                self.package_folder,
                "include",
                "treeqp",
            ),
            keep_path=True,
        )

        # Bundled HPMPC headers used by TreeQP's public API.
        copy(
            self,
            "*.h",
            src=os.path.join(
                self.source_folder,
                "external",
                "hpmpc",
                "include",
            ),
            dst=os.path.join(
                self.package_folder,
                "include",
                "hpmpc",
            ),
            keep_path=False,
        )

        # Bundled HPIPM headers used by TreeQP's public API.
        copy(
            self,
            "*.h",
            src=os.path.join(
                self.source_folder,
                "external",
                "hpipm",
                "include",
            ),
            dst=os.path.join(
                self.package_folder,
                "include",
                "hpipm",
            ),
            keep_path=False,
        )

        # Bundled BLASFEO headers matching HPIPM/HPMPC.
        copy(
            self,
            "*.h",
            src=os.path.join(
                self.source_folder,
                "external",
                "blasfeo",
                "include",
            ),
            dst=os.path.join(
                self.package_folder,
                "include",
                "blasfeo",
            ),
            keep_path=False,
        )

        # qpOASES headers.
        copy(
            self,
            "*.hpp",
            src=os.path.join(
                self.source_folder,
                "external",
                "qpoases",
                "include",
            ),
            dst=os.path.join(
                self.package_folder,
                "include",
                "qpoases",
            ),
            keep_path=True,
        )

        copy(
            self,
            "*.h",
            src=os.path.join(
                self.source_folder,
                "external",
                "qpoases",
                "include",
            ),
            dst=os.path.join(
                self.package_folder,
                "include",
                "qpoases",
            ),
            keep_path=True,
        )

        # Optional TreeQP C++ interface.
        cpp_interface = os.path.join(
            self.source_folder,
            "interfaces",
            "treeqp_cpp",
        )

        if os.path.isdir(cpp_interface):
            copy(
                self,
                "*.h",
                src=cpp_interface,
                dst=os.path.join(
                    self.package_folder,
                    "include",
                    "treeqp_cpp_interface",
                ),
                keep_path=True,
            )

            copy(
                self,
                "*.hpp",
                src=cpp_interface,
                dst=os.path.join(
                    self.package_folder,
                    "include",
                    "treeqp_cpp_interface",
                ),
                keep_path=True,
            )

        # The top-level Makefile places the archives here:
        #
        #   libtreeqp.a
        #   libhpmpc.a
        #   libhpipm.a
        #   libqpoases.a
        #   libblasfeo.a
        copy(
            self,
            "*.a",
            src=os.path.join(
                self.source_folder,
                "lib",
            ),
            dst=os.path.join(
                self.package_folder,
                "lib",
            ),
            keep_path=False,
        )

    def package_info(self):
        self.cpp_info.set_property(
            "cmake_file_name",
            "treeqp",
        )

        self.cpp_info.set_property(
            "cmake_target_name",
            "treeqp::treeqp",
        )

        self.cpp_info.includedirs = [
            "include",
            os.path.join("include", "blasfeo"),
            os.path.join("include", "hpipm"),
            os.path.join("include", "hpmpc"),
        ]

  
        # Static link order: consumers first, providers afterwards.
        self.cpp_info.libs = [
            "treeqp_cpp_interface",
            "treeqp",
            "hpmpc",
            "hpipm",
            "qpoases",
            "blasfeo",
        ]

        if self.options.with_openmp:
            compiler = str(self.settings.compiler)

            if compiler == "gcc":
                self.cpp_info.system_libs.append("gomp")
            elif compiler in (
                "clang",
                "apple-clang",
            ):
                self.cpp_info.system_libs.append("omp")

        if self.settings.os in (
            "Linux",
            "FreeBSD",
        ):
            self.cpp_info.system_libs.append("m")