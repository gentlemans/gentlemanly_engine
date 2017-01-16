if(EMSCRIPTEN)
	include(${GE_DIR}/cmake/emscripten.cmake)
endif()

if(ANDROID)
	message("Android!!!")
	include(${GE_DIR}/cmake/android.cmake)
endif()


macro(ge_create_exe name srcs package_paths)

	message("Configuring gentlemanly_engine executable ${name} with source files: ${srcs} and package paths: ${package_paths}")

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
  	set(ANDROID_BIN_ROOT ${CMAKE_BINARY_DIR}/android-project/${name})

		add_custom_target(android-install-${name} ${ANDROID_ANT} ${ANT_INSTALL_TARGET} WORKING_DIRECTORY ${ANDROID_BIN_ROOT})
	  add_custom_target(android-backtrace-${name} ${ANDROID_ADB} logcat WORKING_DIRECTORY ${ANDROID_BIN_ROOT})
	  add_custom_target(android-build-${name} ${ANDROID_ANT} ${ANT_FLAGS} ${ANT_TARGET} WORKING_DIRECTORY ${ANDROID_BIN_ROOT})
	  add_custom_target(android-start-${name} ${ANDROID_ADB} shell am start -n org.libsdl.app/org.libsdl.app.SDLActivity WORKING_DIRECTORY ${ANDROID_BIN_ROOT})

		add_library(${name} ${srcs} ${GE_DIR}/deps/sdl2/src/main/android/SDL_android_main.c)

		add_custom_command(TARGET ${name} PRE_BUILD
		COMMAND
			${CMAKE_COMMAND} -E copy_directory ${GE_DIR}/cmake/android-project ${ANDROID_BIN_ROOT})

		# copy asset paths
		foreach(datapath ${package_paths})
				# sepreate between @
				string(FIND ${datapath} "@" atpos)
				string(LENGTH ${datapath} strlen)
				string(SUBSTRING ${datapath} 0 ${atpos} first_part)
				string(SUBSTRING ${datapath} ${atpos} ${strlen} second_part)
				add_custom_command(TARGET ${name} PRE_BUILD
				COMMAND
					${CMAKE_COMMAND} -E copy_directory ${first_part} ${ANDROID_BIN_ROOT}/${second_part})
		endforeach()



	else()
		add_executable(${name} ${srcs})

		# TODO: package
	endif()

endmacro()
