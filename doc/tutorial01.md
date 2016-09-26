#Tutorial 01: Runtime and subsystems

Welcome to gentlemanly_engine! You're in the right place! You're about to start a journey of easy, intuitive, cross-platform, modern, and fun game design. This is meant to be read once you have a working build of ge, for that look [here](setup.md). 

##Setting up the buildsystem
[CMake](https://cmake.org)  is used as a buildsystem for ge. Just clone ge into some subdirectory of your project and use `add_subdirectory(...)` to build ge and its dependencies:

```Cmake
cmake_version_required(VERSION 3.0)

add_subdirectory(/path/to/ge/)

add_executable(my_favorite_game main.cpp)

target_link_libraries(my_favorite_game gentelmanly_engine)
```
And that's it, it'll build. 

##The [`runtime`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1runtime.html) class
The [`runtime`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1runtime.html) is the class that orgnaizes and owns all the [`subsystems`](subsystem..md) and stores the [`asset_manager`](https://gentlemans.github.io/gentlemanly_engine/classge_1_1asset__manager.html). This is the first class you will need to instance when creating a game with ge:

```C++
#include <ge/runtime.hpp>

// We'll need these later
#include <ge/input_subsystem.hpp>
#include <ge/sdl_subsystem.hpp>

int main() {

	ge::runtime r;
```
Next, you are going to want to enable the engine features that you need. This is done through [subsystems](subsystem.md). Chances are you will want the [`input_subsystem`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1input__subsystem.html) to process input events and [`sdl_subsystem`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1sdl__subsystem.html) to open a window at the very least:

```C++
	r.add_subsystem<ge::input_subsystem>({});
	r.add_subsystem<ge::sdl_subsystem>({
		"hello ge!",    // title of the window 
		{},             // location on the screen, {} for OS defined (it's a boost::optional<glm::uvec2>)
		false,          // fullscreen or not
		true            // if the window should be decorated (border etc).
	});
```

##Running the engine!
All you run the engine at this point is just call [`runtime::tick`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1sdl__subsystem.html/structge_1_1runtime.html#a46baa37c970f01af28da0596142aceac) whenever you want a frame:

```C++
	while(r.tick());
}
```

That's all you need to get started. The full source listing for this example is at [samples/tutorial01](https://github.com/gentlemans/gentlemanly_engine/tree/master/samples/tutorial01). 

###[Next Tutorial: Actors](tutorial02.md)