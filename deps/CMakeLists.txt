

add_subdirectory(boost)
#
# # All of these are in ports
 if(NOT EMSCRIPTEN)
#
 	set( SDL_STATIC ON CACHE BOOL "Build the static SDL library" )
   set( SDL_SHARED OFF CACHE BOOL "Build the shared SDL library" )
   set( PTHREADS OFF CACHE BOOL "Pthread support" )

 		add_subdirectory(sdl2)


 	set(SDL2_LIBRARY SDL2-static CACHE STRING "")
 	set(SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sdl2/include CACHE PATH "")

 	add_subdirectory(ogg)
 	set(OGG_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/ogg CACHE PATH "")
 	set(OGG_LIBRARIES ogg CACHE STRING "")
 	set(OGG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/ogg/include CACHE PATH "")

 	add_subdirectory(vorbis)
 	add_dependencies(vorbis ogg)


	set(BUILD_SHARED_LIBS OFF)
 	add_subdirectory(freetype2)
 	set(FREETYPE_LIBRARY freetype CACHE STRING "")
 	set(FREETYPE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/freetype2/include)
 else()
 	set(FREETYPE_LIBRARY "freetype")
 	set(FREETYPE_INCLUDE_DIRS "./")
 endif()

 # LIBROCKET

 set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
 set(BUILD_SAMPLES OFF CACHE BOOL "")
 add_subdirectory(libRocket/Build)

 if(EMSCRIPTEN)
 	set_target_properties(RocketCore PROPERTIES COMPILE_FLAGS "-s USE_FREETYPE=1")
 endif()

 if(NOT EMSCRIPTEN)
 	set(ALSOFT_UTILS OFF CACHE BOOL "")
 	set(ALSOFT_EXAMPLES OFF CACHE BOOL "")
 	set(ALSOFT_TESTS OFF CACHE BOOL "")
 	set(ALSOFT_NO_CONFIG_UTIL ON CACHE BOOL "")

 	add_subdirectory(openal-soft)

 	if(WIN32)
 		set(OPENAL_LIBRARY OpenAL32)
 	else()
 		set(OPENAL_LIBRARY openal)
 	endif()

 	set(OPENAL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/openal-soft/include)
 endif()
