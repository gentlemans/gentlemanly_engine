set(GE_ROCKET_PUBLIC_FILES
	include/ge/rocket_document_asset.hpp
	include/ge/rocket_font_asset.hpp
	include/ge/rocket_input_consumer.hpp
	include/ge/rocket_render_interface.hpp
	include/ge/rocket_subsystem.hpp
	include/ge/rocket_system_interface.hpp
)

set(GE_ROCKET_PRIVATE_FILES
	src/rocket_document_asset.cpp
	src/rocket_input_consumer.cpp
	src/rocket_render_interface.cpp
	src/rocket_subsystem.cpp
)

add_library(gentlemanly_engine_rocket_subsystem ${GE_ROCKET_PUBLIC_FILES} ${GE_ROCKET_PRIVATE_FILES})


target_link_libraries(gentlemanly_engine_rocket_subsystem 
PUBLIC
	RocketCore
	RocketDebugger
	RocketControls
	gentlemanly_engine
	gentlemanly_engine_renderer
)

target_include_directories(gentlemanly_engine_rocket_subsystem
PUBLIC
	../../deps/libRocket/Include/
	include
)

if(EMSCRIPTEN)
	set_target_properties(gentlemanly_engine_rocket_subsystem PROPERTIES COMPILE_FLAGS "-s USE_FREETYPE=1")
endif()
