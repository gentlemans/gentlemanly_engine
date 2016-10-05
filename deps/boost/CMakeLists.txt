
add_library(boost_system system/error_code.cpp)

target_include_directories(boost_system
PUBLIC
	./
)

add_library(boost_filesystem 
	filesystem/codecvt_error_category.cpp
	filesystem/operations.cpp
	filesystem/path.cpp
	filesystem/path_traits.cpp
	filesystem/portability.cpp
	filesystem/unique_path.cpp
	filesystem/utf8_codecvt_facet.cpp
	filesystem/windows_file_codecvt.cpp
)

target_link_libraries(boost_filesystem PUBLIC boost_system)
