from distutils.core import setup, Extension

module = Extension(
      'MiniQbtNative', 
      sources=['${PyMiniQbt_SOURCE_FILES}'],
      extra_compile_args = ['-O3','-std=c++11'],
      include_dirs = ['${PyMiniQbt_INCLUDE_LIB}', '${PyMiniQbt_EIGEN_INCLUDE_LIB}']
      )

setup(name='MiniQbt',
      version='${PACKAGE_VERSION}',
      ext_modules = [module],
      package_dir={ '': '${CMAKE_CURRENT_SOURCE_DIR}' },
      packages=['MiniQbt'])