
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

add_executable(grid main.cpp grid.cpp grid.hpp zombie.hpp base.hpp toweractor.hpp )

target_link_libraries(grid
	gentlemanly_engine
	gentlemanly_engine_renderer
	gentlemanly_engine_rocket_subsystem
)


if(EMSCRIPTEN)
	set_target_properties(grid PROPERTIES  LINK_FLAGS "-s DISABLE_EXCEPTION_CATCHING=0 -s USE_SDL=2 -s FULL_ES3=1 --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/..@/ -s" SUFFIX ".html" COMPILE_FLAGS "-g3 --minify 0")
endif()




