# Locate the ANAX library 
# Defines the variables:
#		ANAX_INCLUDE_DIRS
#		ANAX_LIBRARY
# and the imported library target:
#		anax

find_path(
	ANAX_INCLUDE_DIRS
NAMES
	anax/anax.hpp
HINTS
	$ENV{ANAXDIR}
	PATH_SUFFIXES include
	PATHS ${ANAX_SEARCH_PATHS}
)

find_library(
	ANAX_LIBRARY
NAMES
	anax
HINTS
	$ENV{ANAXDIR}
	PATH_SUFFIXES lib lib64
	PATHS ${ANAX_SEARCH_PATHS}
)

add_library(anax IMPORTED SHARED)
set_property(TARGET anax 
PROPERTY 
	IMPORTED_LOCATION ${ANAX_LIBRARY}
)
set_property(TARGET anax 
PROPERTY
	INTERFACE_INCLUDE_DIRECTORIES ${ANAX_INCLUDE_DIRS}
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(anax REQUIRED_VARS ANAX_LIBRARY ANAX_INCLUDE_DIRS)


