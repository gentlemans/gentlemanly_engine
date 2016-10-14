macro(GEEmscriptenTarget target genhtml datapaths)
	
	if(EMSCRIPTEN)
		
		set(CPL_FLAGS "")
		foreach(datapath ${datapaths})
			set(CPL_FLAGS "${CPL_FLAGS} --preload-file ${datapath}")
		endforeach()
		
		message("Setting emscripten flags for ${target}")
		set_target_properties(${target} PROPERTIES 
		COMPILE_FLAGS 
			"-s USE_SDL=2 -s USE_FREETYPE=1 -s USE_OGG=1 -s USE_VORBIS=1 ${CPL_FLAGS}"
		LINK_FLAGS 
			"-s USE_SDL=2 -s USE_FREETYPE=1 -s USE_OGG=1 -s USE_VORBIS=1 ${CPL_FLAGS}"
		)
		if(${genhtml}) 
			message("Generating HTML for ${target}")
			set_target_properties(${target} PROPERTIES SUFFIX ".html")
		endif()
		
	endif()
	
endmacro(GEEmscriptenTarget)
