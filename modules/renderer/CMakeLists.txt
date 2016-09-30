
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

set(RENDERER_PUBLIC_FILES
	include/ge/gl.hpp
	include/ge/lodepng.h
	include/ge/material.hpp
	include/ge/material_asset.hpp
	include/ge/mesh.hpp
	include/ge/mesh_actor.hpp
	include/ge/mesh_asset.hpp
	include/ge/mesh_settings.hpp
	include/ge/mesh_settings_asset.hpp
	include/ge/ortho2d.hpp
	include/ge/sdl_subsystem.hpp
	include/ge/shader.hpp
	include/ge/shader_asset.hpp
	include/ge/sound_cue.hpp
	include/ge/texture.hpp
	include/ge/texture_asset.hpp
)

set(RENDERER_PRIVATE_FILES
	src/lodepng.cpp
	src/material.cpp
	src/material_asset.cpp
	src/mesh.cpp
	src/mesh_actor.cpp
	src/mesh_asset.cpp
	src/mesh_settings.cpp
	src/sdl_subsystem.cpp
	src/shader.cpp
	src/shader_asset.cpp
	src/texture.cpp
	src/texture_asset.cpp
)

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

if(WIN32)
    target_include_directories(gentlemanly_engine_renderer
    PRIVATE
        ../../deps/glew_win32/include
    )
	target_link_libraries(gentlemanly_engine_renderer
	PRIVATE 
		${CMAKE_CURRENT_SOURCE_DIR}/../../deps/glew_win32/lib/Release/x64/glew32.lib
	)
endif()



