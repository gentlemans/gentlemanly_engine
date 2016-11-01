ge_create_exe(grid "turret.hpp;main.cpp;grid.cpp;grid.hpp;zombie.hpp;zombie.cpp;base.hpp;piece.hpp;piece.cpp;gridtick_interface.hpp;damagable.hpp" "${CMAKE_CURRENT_SOURCE_DIR}/../data@/data")

target_link_libraries(grid
	gentlemanly_engine
	gentlemanly_engine_renderer
	gentlemanly_engine_rocket_subsystem
)
