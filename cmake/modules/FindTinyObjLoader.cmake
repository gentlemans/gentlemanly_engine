
# locate files for TinyObjLoader
# sets 	TINYOBJLOADER_INCLUDE_DIR
# and	TINYOBJLOADER_LIBRARY
# and the imported library target TinyObjLoader

find_path(
	TINYOBJLOADER_INCLUDE_DIR
NAMES
	tiny_obj_loader.h
HINTS 
	$ENV{TINYOBJDIR}
	PATH_SUFFIXES include
	PATHS ${TINYOBJ_SEARCH_PATHS}
)

find_library(
	TINYOBJLOADER_LIBRARY
NAMES 
	tinyobjloader
HINTS
	$ENV{TINYOBJDIR}
	PATH_SUFFIXES lib64 lib
	PATHS ${TINYOBJ_SEARCH_PATHS}
)

add_library(TinyObjLoader SHARED IMPORTED)
set_property(TARGET TinyObjLoader 
PROPERTY
	IMPORTED_LOCATION ${TINYOBJLOADER_LIBRARY}
)

set_property(TARGET TinyObjLoader
PROPERTY
	INTERFACE_INCLUDE_DIRECTORIES ${TINYOBJ_INCLUDE_DIR}
)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(TinyObjLoader REQUIRED_VARS TINYOBJLOADER_LIBRARY TINYOBJLOADER_INCLUDE_DIR)
