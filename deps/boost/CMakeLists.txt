
add_library(boost_system system/error_code.cpp)

target_include_directories(boost_system
PUBLIC
	./
)

set(BOOST_FILESYSTEM_SRCS
    filesystem/codecvt_error_category.cpp
    filesystem/operations.cpp
    filesystem/path.cpp
    filesystem/path_traits.cpp
    filesystem/portability.cpp
    filesystem/unique_path.cpp
    filesystem/utf8_codecvt_facet.cpp
)

if(WIN32)
    set(BOOST_FILESYSTEM_SRCS ${BOOST_FILESYSTEM_SRCS} filesystem/windows_file_codecvt.cpp)
endif()

add_library(boost_filesystem ${BOOST_FILESYSTEM_SRCS})

target_link_libraries(boost_filesystem PUBLIC boost_system)

target_compile_definitions(boost_filesystem
PUBLIC 
	BOOST_ALL_NO_LIB
)

install(TARGETS boost_filesystem boost_system 
	RUNTIME DESTINATION bin 
	LIBRARY DESTINATION lib 
	ARCHIVE DESTINATION lib
)

install(DIRECTORY boost DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
