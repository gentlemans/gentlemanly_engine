#Tutorial 02: Actors

The  [`actor`](https://gentlemans.github.com/gentlemanly_engine/classge_1_1actor.html) class is a generic class, that is placable in the world. All actors have a positition, rotation, scale, and can have a parent or children. 

##Actor Parenting
Parenting actors is effectively attaching them. All child actors will rotate around the parent, move with it, and scale with it.  

> TODO: find image

##Spawning actors
You cannot just use `operator new` to spawn an actor, but it's almost as easy. Just use the `actor::factory` function template with the first argument being the parent actor, and the rest being arguments that are [perfect forwarded](//TODO) to the `actor::initialize` function. For example, to spawn a [`mesh_actor`](https://gentlemans.github.com/gentlemanly_engine/structge_1_1mesh__actor.html):
```C++
std::shared_ptr<ge::mesh_actor> my_actor = ge::actor::factory<ge::mesh_actor>(
	root_actor,        // the parent actor
	my_mesh_settings   // arguments to be passed to mesh_actor::initialize
) 
```
> The second argument is a mesh settings. This is known because it is the argument to [`mesh_actor::initialize`](https://gentlemans.github.com/gentlemanly_engine/structge_1_1mesh__actor.html#af608c07d6da1222b1baec23df6953802). 

You may be thinking: well if I always need a parent `actor`, how do I create the first `actor`? Don't worry, just use `actor::root_factory`:
```C++
auto root = ge::actor::root_factory<myfancyactor>(runtime_object, [ args to myfancyactor::initialize ] )
```
> *NOTE:* You will usually only want one root actor, parent everything to it, and pass it to a rendering interface, such as [`sdl_subsystem`](https://gentlemans.github.com/gentlemanly_engine/structge_1_1sdl__subsystem.html) using [`sdl_subsystem::set_root_actor`](https://gentlemans.github.com/gentlemanly_engine/structge_1_1sdl__subsystem.html#a41d88e7b6566e9653ec1b94a424fb6f8). 

##Building your own actors
Building your own actors is pretty easy. First, define a class that derives from `actor`:

```C++
#include <ge/actor.hpp>
#include <ge/camera_actor.hpp>

class my_player : public actor  {	
```

Instead of using constructors, `actor`s use an `initialize` function. Do not define a constructor unless you know what you are doing.
```C++
camera_actor* cam; 

public:
	void initialize(glm::vec2 location) {
		set_relative_location(position);

		cam = actor::factory<camera_actor>(this, 4.0 /* how many vertical units to be able to see */)
		m_runtime->get_subsystem<sdl_subsystem>()->set_camera(cam);
	}
``` 
See: [`sdl_subsystem::set_camera`](https://gentlemans.github.com/gentlemanly_engine/structge_1_1sdl__subsystem.html#ac2f47d1ec3621dab6401e571bd0b5f3b)

> *NOTE:* If you derive from a more complex actor, **make sure to call its initialize function in your initialize function.**. 

That's pretty much it for a basic actor. 

###[Next Tutorial: Input](tutorial03.md)