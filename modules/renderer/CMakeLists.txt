
find_package(OpenGL REQUIRED)

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
)

if(WIN32)
	set(RENDERER_PRIVATE_FILES ${RENDERER_PRIVATE_FILES} src/glad.c)
endif()

add_library(gentlemanly_engine_renderer ${RENDERER_PUBLIC_FILES} ${RENDERER_PRIVATE_FILES})

target_include_directories(gentlemanly_engine_renderer
PRIVATE
	${SDL2_INCLUDE_DIR}
	../../deps/assimp/include
	${OPENGL_INCLUDE_DIR}
PUBLIC
	include
)

target_link_libraries(gentlemanly_engine_renderer
PRIVATE
	gentlemanly_engine
	${SDL2_LIBRARY}
	assimp
PUBLIC
    ${OPENGL_LIBRARIES}
)

if(UNIX AND NOT APPLE)
	target_link_libraries(gentlemanly_engine_renderer
	PUBLIC
		wayland-client
	)
endif()

