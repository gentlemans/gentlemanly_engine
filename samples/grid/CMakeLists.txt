ge_create_exe(grid "ticktimer.hpp;connector.hpp;wall.cpp;grid_rocket_element.hpp;wall.hpp;turret.hpp;spike.hpp;zombiespawner.hpp;turret.cpp;main.cpp;grid.cpp;grid.hpp;zombie.hpp;zombie.cpp;base.hpp;piece.hpp;piece.cpp;gridtick_interface.hpp;" "${CMAKE_CURRENT_SOURCE_DIR}/../data@/data")

target_link_libraries(grid
	gentlemanly_engine
	gentlemanly_engine_renderer
	gentlemanly_engine_rocket_subsystem
)
