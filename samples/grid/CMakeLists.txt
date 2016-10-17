
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

add_executable(grid main.cpp grid.cpp grid.hpp zombie.hpp base.hpp piece.hpp gridtick_interface.hpp )

target_link_libraries(grid
	gentlemanly_engine
	gentlemanly_engine_renderer
	gentlemanly_engine_rocket_subsystem
)

GEEmscriptenTarget(grid TRUE ${CMAKE_CURRENT_SOURCE_DIR}/../data@/data)
