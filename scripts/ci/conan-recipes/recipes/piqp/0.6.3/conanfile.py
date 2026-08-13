from conan import ConanFile
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import copy, get
import os


class PiqpConan(ConanFile):
    name = "piqp"
    version = "0.6.3"

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
        "with_openmp": [True, False],   # <-- add
    }

    default_options = {
        "shared": False,
        "fPIC": True,
        "with_blasfeo": True,
        "with_openmp": True,            # <-- add (or False if you prefer conservative default)
    }

    def requirements(self):
        self.requires("eigen/[>=3.4.0 <6]")

        if self.options.with_blasfeo:
            self.requires("blasfeo/tttapa.20260119")

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self)

    def source(self):
        get(
            self,
            url=(
                "https://github.com/PREDICT-EPFL/piqp/"
                "archive/refs/tags/v0.6.3.tar.gz"
            ),
            strip_root=True,
        )

    def generate(self):
        deps = CMakeDeps(self)
        deps.generate()

        tc = CMakeToolchain(self)

        # PIQP core build
        tc.variables["BUILD_WITH_TEMPLATE_INSTANTIATION"] = True
        tc.variables["BUILD_WITH_BLASFEO"] = bool(self.options.with_blasfeo)
        tc.variables["BUILD_WITH_OPENMP"] = bool(self.options.with_openmp)   # <-- add
        tc.variables["BUILD_SHARED_LIBS"] = bool(self.options.shared)

        # Disable unnecessary interfaces
        tc.variables["BUILD_C_INTERFACE"] = False
        tc.variables["BUILD_PYTHON_INTERFACE"] = False
        tc.variables["BUILD_MATLAB_INTERFACE"] = False
        tc.variables["BUILD_OCTAVE_INTERFACE"] = False

        # These are the actual PIQP option names
        tc.variables["BUILD_TESTS"] = False
        tc.variables["BUILD_EXAMPLES"] = False
        tc.variables["BUILD_BENCHMARKS"] = False
        tc.variables["BUILD_MAROS_MESZAROS_TESTS"] = False
        tc.variables["BUILD_NETLIB_TESTS"] = False

        # Required for cmake.install()
        tc.variables["ENABLE_INSTALL"] = True

        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

        copy(
            self,
            "LICENSE",
            src=self.source_folder,
            dst=os.path.join(self.package_folder, "licenses"),
        )

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "piqp")
        self.cpp_info.set_property("cmake_target_name", "piqp::piqp")
        if self.options.with_blasfeo:
            self.cpp_info.defines.append("PIQP_HAS_BLASFEO")
        if self.options.with_openmp:
            self.cpp_info.defines.append("PIQP_HAS_OPENMP")