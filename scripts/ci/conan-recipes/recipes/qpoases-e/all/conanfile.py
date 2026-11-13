import os

from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout
from conan.tools.files import apply_conandata_patches, copy, export_conandata_patches, get


class QpoasesEmbeddedRecipe(ConanFile):
    name = "qpoases-e"
    package_type = "library"
    package_id_non_embed_mode = "full_mode"
    package_id_unknown_mode = "full_mode"
    license = "LGPL-2.1-or-later"
    homepage = "https://github.com/acados/qpOASES"
    url = "https://github.com/tttapa/conan-recipes"
    description = "The embedded C variant of the qpOASES active-set QP solver."
    topics = "optimization", "quadratic-programming"
    settings = "os", "arch", "compiler", "build_type"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    exports_sources = "CMakeLists.txt"

    def config_options(self):
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):
        self.settings.rm_safe("compiler.cppstd")
        self.settings.rm_safe("compiler.libcxx")
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):
        cmake_layout(self, src_folder="src")

    def source(self):
        get(self, **self.conan_data["sources"][self.version], strip_root=True)
        apply_conandata_patches(self)
        copy(self, "CMakeLists.txt", self.export_sources_folder, self.source_folder)

    def export_sources(self):
        export_conandata_patches(self)

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.24 <5]")

    def generate(self):
        CMakeToolchain(self).generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(self, "LICENSE.txt", self.source_folder,
             os.path.join(self.package_folder, "licenses"))
        CMake(self).install()

    def package_info(self):
        self.cpp_info.libs = ["qpOASES_e"]
        self.cpp_info.defines = ["__NO_STATIC__"]
        if self.settings.os in ["Linux", "FreeBSD"]:
            self.cpp_info.system_libs = ["m"]
