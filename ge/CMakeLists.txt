find_package(Boost COMPONENTS filesystem system)
find_package(Threads REQUIRED)

set(GE_PRIVATE_SOURCES
	src/actor.cpp
)

set(GE_PUBLIC_SOURCES
	include/ge/actor.hpp
	include/ge/asset_manager.hpp
	include/ge/camera_actor.hpp
	include/ge/concept/asset.hpp
	include/ge/hash_typeindex.hpp
	include/ge/input_event.hpp
	include/ge/input_subsystem.hpp
	include/ge/json.hpp
	include/ge/json_helper.hpp
	include/ge/runtime.hpp
	include/ge/subsystem.hpp
	include/ge/timer_manager.hpp
	include/ge/transform.hpp
)

add_library(gentlemanly_engine ${GE_PUBLIC_SOURCES} ${GE_PRIVATE_SOURCES})

target_include_directories(gentlemanly_engine
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../deps/glm
	${Boost_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(gentlemanly_engine
PUBLIC 
	Threads::Threads
	debug ${Boost_FILESYSTEM_LIBRARY_DEBUG}
	optimized ${Boost_FILESYSTEM_LIBRARY_RELEASE}
	debug ${Boost_SYSTEM_LIBRARY_DEBUG}
	optimized ${Boost_SYSTEM_LIBRARY_RELEASE}
)

target_compile_definitions(gentlemanly_engine
PUBLIC
	BOOST_ALL_NO_LIB
)

target_compile_features(gentlemanly_engine
PUBLIC
	cxx_generic_lambdas
	cxx_variadic_templates
)
