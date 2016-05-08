# Locate the EntityX library 
# Defines the variables:
#		ENTITYX_INCLUDE_DIRS
#		ENTITYX_LIBRARY
# and the imported library target:
#		EntityX

find_path(
	ENTITYX_INCLUDE_DIRS
NAMES
	entityx/entityx.h
HINTS
	$ENV{ENTITYXDIR}
	PATH_SUFFIXES include
	PATHS ${ENTITYX_SEARCH_PATHS}
)

find_library(
	ENTITYX_LIBRARY
NAMES
	entityx
HINTS
	$ENV{ENTITYXDIR}
	PATH_SUFFIXES lib lib64
	PATHS ${ENTITYX_SEARCH_PATHS}
)

add_library(EntityX IMPORTED SHARED)
set_property(TARGET EntityX
PROPERTY 
	IMPORTED_LOCATION ${ENTITYX_LIBRARY}
)
set_property(TARGET EntityX
PROPERTY
	INTERFACE_INCLUDE_DIRECTORIES ${ENTITYX_INCLUDE_DIRS}
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(EntityX REQUIRED_VARS ENTITYX_LIBRARY ENTITYX_INCLUDE_DIRS)


