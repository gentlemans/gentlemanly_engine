# gentlemanly_engine
A super standard C++ game engine

#Abstract
The gentlemanly_engine is meant to provide a easy to learn, standard, well documented, extensible object-oriented 2D game engine written purely in C++ with possible python bindings later.

##High-level to low-level control
Want to just get started quickly and get some `actor`s on the screen? No problem, gentlemanly_engine is for you. Want physics? No problem, just add a `physics` object to the actors you want to have physics. But what if you want to write custom shaders, dig under the hood? No problem, make an actor an override the `render` method. 

##Modern C++
Written entirely in modern C++, we use modern strategies like `std::shared_ptr`, `auto`, move semantics, etc to make the developing experience better.

##Multiple windowing backends
SDL is a very popular window backend for games, but it can be a real pain when trying to make an editor, where a GUI toolkit like Qt will fit your needs much better. There is no `window` class, just a concept that you can use. We have supplied window backends for Qt and SDL. Example:
```C++
// SDL window example
#include <ge/appliction.hpp>
#include <ge/window_backend/sdl.hpp>

int main(int argc, char** argv)
{
	ge::application<ge::window_backend::sdl> app{argc, argv};

	auto window = app.window_backend.make_window(
		"Hello",     // title
		{},          // starting position
		{1280, 720}, // size
		false,       // fullscreen
		true         // decorated
	);

	app.execute();
}
``` 

That's all there is to it to open a window. Want a Qt window instead? Just use `ge::window_backend::qt` instead of `ge::window_backend::sdl`. That `window` object you have received will be subclassed off `QMainWindow`, so start building the widgets off that. 


##Extensible powerful asset system
It is totally impractical to load all you assets (textures, models, animations, etc) 
