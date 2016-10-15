set(RENDERER_PUBLIC_FILES
	include/ge/gl.hpp
	include/ge/lodepng.h
	include/ge/material_asset.hpp
	include/ge/material.hpp
	include/ge/mesh_actor.hpp
	include/ge/mesh_asset.hpp
	include/ge/mesh.hpp
	include/ge/mesh_settings_asset.hpp
	include/ge/mesh_settings.hpp
	include/ge/ortho2d.hpp
	include/ge/renderable.hpp
	include/ge/sdl_subsystem.hpp
	include/ge/shader_asset.hpp
	include/ge/shader.hpp
	include/ge/sound_cue.hpp
	include/ge/texture_asset.hpp
	include/ge/texture.hpp
    include/ge/animation_actor.hpp
)

set(RENDERER_PRIVATE_FILES
	src/lodepng.cpp
	src/material_asset.cpp
	src/material.cpp
	src/mesh_actor.cpp
	src/mesh_asset.cpp
	src/mesh.cpp
	src/mesh_settings.cpp
	src/sdl_subsystem.cpp
	src/shader_asset.cpp
	src/shader.cpp
	src/texture_asset.cpp
    src/texture.cpp
    src/tiny_obj_loader.cc
)

if(WIN32)
	set(RENDERER_PRIVATE_FILES ${RENDERER_PRIVATE_FILES} src/glad.c)
endif()

add_library(gentlemanly_engine_renderer ${RENDERER_PUBLIC_FILES} ${RENDERER_PRIVATE_FILES})

target_include_directories(gentlemanly_engine_renderer
PUBLIC
	include
)

target_link_libraries(gentlemanly_engine_renderer
PRIVATE
	gentlemanly_engine
)

if(NOT EMSCRIPTEN)

	find_package(OpenGL REQUIRED)
	find_package(SDL2 REQUIRED)
	
	target_link_libraries(gentlemanly_engine_renderer
	PRIVATE
		${SDL2_LIBRARY}
	PUBLIC
		${OPENGL_LIBRARIES}
	)
	target_include_directories(gentlemanly_engine_renderer
	PRIVATE
		${SDL2_INCLUDE_DIR}
		${OPENGL_INCLUDE_DIR}
	)
endif()

if(EMSCRIPTEN)
	set_target_properties(gentlemanly_engine_renderer PROPERTIES COMPILE_FLAGS "-s USE_SDL=2")
endif()

if(UNIX AND NOT APPLE AND NOT EMSCRIPTEN)
	target_link_libraries(gentlemanly_engine_renderer
	PUBLIC
		wayland-client
	)
endif()

