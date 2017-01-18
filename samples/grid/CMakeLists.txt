<<<<<<< HEAD
ge_create_exe(grid "ticktimer.hpp;turret.hpp;spike.hpp;zombiespawner.hpp;main.cpp;grid.cpp;grid.hpp;zombie.hpp;zombie.cpp;base.hpp;piece.hpp;piece.cpp;gridtick_interface.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/../data@/data")
=======
ge_create_exe(grid "ticktimer.hpp;grid_rocket_element.hpp;turret.hpp;spike.hpp;zombiespawner.hpp;main.cpp;grid.cpp;grid.hpp;zombie.hpp;zombie.cpp;base.hpp;piece.hpp;piece.cpp;gridtick_interface.hpp;damagable.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/../data@/data")
>>>>>>> origin/master

target_link_libraries(grid
	gentlemanly_engine
	gentlemanly_engine_renderer
	gentlemanly_engine_rocket_subsystem
)
