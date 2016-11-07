if(EMSCRIPTEN)
	include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/emscripten.cmake)
endif()

if(ANDROID)
	include(android.cmake)
endif()

macro(ge_create_exe name srcs package_paths)
	
	message("Configureing gentlemanly_engine executable ${name} with source files: ${srcs} and package paths: ${package_paths}")
	
	if(EMSCRIPTEN)
		add_executable(${name} ${srcs})
		
		set(CPL_FLAGS "")
		foreach(datapath ${package_paths})
			set(CPL_FLAGS "${CPL_FLAGS} --preload-file ${datapath}")
		endforeach()
		
		set_target_properties(${name} PROPERTIES 
		COMPILE_FLAGS 
			"-s USE_SDL=2 -s USE_FREETYPE=1 -s USE_OGG=1 -s USE_VORBIS=1 ${CPL_FLAGS}"
		LINK_FLAGS 
			"-s USE_SDL=2 -s USE_FREETYPE=1 -s USE_OGG=1 -s USE_VORBIS=1 ${CPL_FLAGS}"
		)
		set_target_properties(${name} PROPERTIES SUFFIX ".html")
		
	elseif(ANDROID)
		
	else()
		add_executable(${name} ${srcs})
		
		# TODO: package
	endif()

endmacro()
