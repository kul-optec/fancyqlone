import os

from conan import ConanFile
from conan.tools.build import check_min_cppstd
from conan.tools.cmake import CMake, CMakeDeps, CMakeToolchain, cmake_layout
from conan.tools.files import apply_conandata_patches, copy, export_conandata_patches, get


class TreeqpRecipe(ConanFile):
    name = "treeqp"
    package_type = "library"
    license = "LGPL-3.0-or-later"
    homepage = "https://github.com/dkouzoup/treeQP"
    url = "https://github.com/tttapa/conan-recipes"
    description = "A toolbox of tree-sparse quadratic programming solvers."
    topics = "optimization", "quadratic-programming", "optimal-control"
    settings = "os", "arch", "compiler", "build_type"
    options = {
        "shared": [True, False],
        "fPIC": [True, False],
        "with_openmp": [True, False],
    }
    default_options = {"shared": False, "fPIC": True, "with_openmp": False}
    exports_sources = "CMakeLists.txt", "treeqp-config.cmake.in"

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def validate(self):
        if self.settings.compiler.get_safe("cppstd"):
            check_min_cppstd(self, "11")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def export_sources(self):
        export_conandata_patches(self)

    def source(self):
        get(self, **self.conan_data["sources"][self.version], strip_root=True)
        apply_conandata_patches(self)
        copy(self, "CMakeLists.txt", self.export_sources_folder, self.source_folder)
        copy(self, "treeqp-config.cmake.in", self.export_sources_folder, self.source_folder)

    def requirements(self):
        self.requires("blasfeo/tttapa.20260119", transitive_headers=True, transitive_libs=True)
        self.requires("hpipm/tttapa.20251105", transitive_headers=True, transitive_libs=True)
        self.requires("qpoases-e/tttapa.20250918", transitive_headers=True, transitive_libs=True)
        if self.options.get_safe("with_openmp") and self.settings.compiler == "clang":
            self.requires(
                f"llvm-openmp/[~{self.settings.compiler.version}]",
                transitive_libs=True,
            )

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.24 <5]")

    def generate(self):
        CMakeDeps(self).generate()
        tc = CMakeToolchain(self)
        tc.variables["TREEQP_WITH_OPENMP"] = bool(self.options.get_safe("with_openmp"))
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE*", self.source_folder,
             os.path.join(self.package_folder, "licenses"))
        CMake(self).install()

    def package_info(self):
        self.cpp_info.set_property("cmake_find_mode", "none")
        self.cpp_info.builddirs = [os.path.join("lib", "cmake", "treeqp")]
        self.cpp_info.defines = ["PROFILE=0"]
        self.cpp_info.libs = ["treeqp_cpp_interface", "treeqp"]
        if self.settings.os in ["Linux", "FreeBSD"]:
            self.cpp_info.system_libs = ["m"]
        if self.options.get_safe("with_openmp") and self.settings.compiler == "gcc":
            self.cpp_info.system_libs.append("gomp")
