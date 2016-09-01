
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

add_executable(grid main.cpp grid.cpp grid.hpp zombie.hpp base.hpp toweractor.hpp )

target_link_libraries(grid
	gentlemanly_engine
)




