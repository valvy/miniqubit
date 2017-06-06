from distutils.core import setup, Extension
module = Extension(
      'MiniQbtNative', 
      language="c++",
      sources=['${PyMiniQbt_SOURCE_FILES}'],
      extra_compile_args = ['-fPIC','-O3','-std=c++14'],
      include_dirs = ['${PyMiniQbt_EIGEN_INCLUDE_LIB}'],
      extra_link_args= ['-L/usr/local/lib', '-lMiniQbt']
)


setup(
      name='MiniQbt',
      license="MIT",
      version='${PACKAGE_VERSION}',
      ext_modules = [module],

      package_dir={ '': '${CMAKE_CURRENT_SOURCE_DIR}' },
      packages=['MiniQbt']

)
