import os

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get


class PiqpConan(ConanFile):
    name = "piqp"
    version = "0.7.0"
    license = "BSD-2-Clause"
    url = "https://github.com/PREDICT-EPFL/piqp"
    homepage = "https://predict-epfl.github.io/piqp"
    description = "Proximal interior-point quadratic programming solver"
    settings = "os", "compiler", "build_type", "arch"
    package_type = "library"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "with_blasfeo": [True, False],
        "with_openmp": [True, False],
    }
    default_options = {
        "shared": False,
        "fPIC": True,
        "with_blasfeo": True,
        "with_openmp": True,
    }

    def requirements(self):
        self.requires("eigen/[>=3.4.0 <6]", transitive_headers=True)
        if self.options.with_blasfeo:
            self.requires("blasfeo/tttapa.20260119", transitive_headers=True)

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)

    def source(self):
        # v0.7.0: dfb7881f850b0e39e4b40db9257399dcfdb81efc
        get(
            self,
            url=f"https://github.com/PREDICT-EPFL/piqp/archive/refs/tags/v{self.version}.tar.gz",
            sha256="6c6665372de6c43b5e42025f47cbe4b89639238c9d5c9b0f520a18a96ec50f6f",
            strip_root=True,
        )

    def generate(self):
        CMakeDeps(self).generate()
        tc = CMakeToolchain(self)
        tc.variables.update({
            "BUILD_WITH_TEMPLATE_INSTANTIATION": True,
            "BUILD_WITH_BLASFEO": bool(self.options.with_blasfeo),
            "BUILD_WITH_OPENMP": bool(self.options.with_openmp),
            "BUILD_SHARED_LIBS": bool(self.options.shared),
            "BUILD_C_INTERFACE": False,
            "BUILD_PYTHON_INTERFACE": False,
            "BUILD_MATLAB_INTERFACE": False,
            "BUILD_OCTAVE_INTERFACE": False,
            "BUILD_TESTS": False,
            "BUILD_EXAMPLES": False,
            "BUILD_BENCHMARKS": False,
            "BUILD_MAROS_MESZAROS_TESTS": False,
            "BUILD_NETLIB_TESTS": False,
            "ENABLE_INSTALL": True,
        })
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        CMake(self).install()
        copy(self, "LICENSE", src=self.source_folder,
             dst=os.path.join(self.package_folder, "licenses"))

    def package_info(self):
        # Upstream exports the instantiated library, ABI definitions, BLASFEO,
        # and OpenMP link requirements. Keep those usage requirements together.
        self.cpp_info.set_property("cmake_find_mode", "none")
        self.cpp_info.builddirs = [os.path.join("lib", "cmake", "piqp")]
