if(WIN32)
	set(Boost_USE_STATIC_LIBS ON)
endif()
find_package(Threads REQUIRED)

set(GE_PRIVATE_SOURCES
	src/actor.cpp
)

set(GE_PUBLIC_SOURCES
	include/ge/actor.hpp
	include/ge/actor_ticker_subsystem.hpp
	include/ge/asset_manager.hpp
	include/ge/camera_actor.hpp
	include/ge/concept/asset.hpp
	include/ge/tickable.hpp
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
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(gentlemanly_engine
PUBLIC 
	Threads::Threads
	boost_filesystem
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
