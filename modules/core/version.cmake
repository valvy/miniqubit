set(PACKAGE_VERSION "0.5.0")

# Check whether the requested PACKAGE_FIND_VERSION is compatible
if("" VERSION_LESS "")
  set(PACKAGE_VERSION_COMPATIBLE FALSE)
else()
  set(PACKAGE_VERSION_COMPATIBLE TRUE)
  if ("" VERSION_EQUAL "")
    set(PACKAGE_VERSION_EXACT TRUE)
  endif()
endif()
