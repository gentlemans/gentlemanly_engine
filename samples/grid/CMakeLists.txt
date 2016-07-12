
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

add_executable(grid main.cpp grid.cpp)

target_link_libraries(grid
	gentlemanly_engine
)




