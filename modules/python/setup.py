from distutils.core import setup, Extension
import os
import platform

def getCompileArguments():
      if(platform.system() == 'windows'):
            return []
      else:
            return ['-fPIC','-O3','-std=c++14']
      

module = Extension(
      'MiniQbtNative', 
      language="c++",
      sources=[os.path.abspath('${PyMiniQbt_SOURCE_FILES}')],
      extra_compile_args = getCompileArguments(),
      include_dirs = [
		os.path.abspath('${EIGEN3_INCLUDE_DIRS}'),
		os.path.abspath('${MiniQbt_SOURCE_DIR}/include/'),
		os.path.abspath('${MiniQbt_BINARY_DIR}/include/')],
	  libraries = ['MiniQbt'],
	  library_dirs = [
	  os.path.abspath('${PyMiniQbt_LIB}')
	  ]

)


setup(
      name='MiniQbt',
      license="MIT",
      version='${PACKAGE_VERSION}',
      ext_modules = [module],

      package_dir={ '': os.path.abspath("${CMAKE_CURRENT_SOURCE_DIR}") },
      packages=['MiniQbt']

)
