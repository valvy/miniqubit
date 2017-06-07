from distutils.core import setup, Extension
import os

module = Extension(
      'MiniQbtNative', 
      language="c++",
      sources=[os.path.abspath('${PyMiniQbt_SOURCE_FILES}')],
 #     extra_compile_args = ['-fPIC','-O3','-std=c++14'],
      include_dirs = [
		os.path.abspath('${EIGEN3_INCLUDE_DIRS}'),
		os.path.abspath('${MiniQbt_SOURCE_DIR}/include/'),
		os.path.abspath('${MiniQbt_BINARY_DIR}/include/')],
	  libraries = ['MiniQbt','python36'],
	  library_dirs = [
	  os.path.abspath('${PyMiniQbt_LIB}'),'C:\\Program Files\\Python36\\libs'
	  ]
	 # extra_link_args= []
      #extra_link_args= ['-L/usr/local/lib', '-lMiniQbt']
)


setup(
      name='MiniQbt',
      license="MIT",
      version='${PACKAGE_VERSION}',
      ext_modules = [module],

      package_dir={ '': os.path.abspath("${CMAKE_CURRENT_SOURCE_DIR}") },
      packages=['MiniQbt']

)
