from distutils.core import setup, Extension
module = Extension(
      'MiniQbtNative', 
      sources=['${PyMiniQbt_SOURCE_FILES}'],
      extra_compile_args = ['-O3','-std=c++14'],
      include_dirs = ['${PyMiniQbt_EIGEN_INCLUDE_LIB}']
  #    libraries = ['MiniQbt']
)


setup(
      name='MiniQbt',
      license="MIT",
      version='${PACKAGE_VERSION}',
      ext_modules = [module],
      package_dir={ '': '${CMAKE_CURRENT_SOURCE_DIR}' },
      packages=['MiniQbt']

)