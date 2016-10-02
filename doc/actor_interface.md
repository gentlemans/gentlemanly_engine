#Actor Interfaces
Many game engines use tools like multiple inheretence to define interfaces. This leads to many problems if you have used that before, and frankly doesn't work that well. gentlemanly_engine has a very unique solution to this.

>**NOTE:** you should read the [actor documentation](tutorial02.md) first. 

##What is an actor interface
An actor interface is just an extension to an actor. It can add additional data memebers, additional functions, you name it. How? I'll show you. 

##How to use an actor interface

First take the actor interface [`tickable`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1tickable.html) as an example. [`tickable`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1tickable.html) just adds another function to [`actor`](https://gentlemans.github.io/gentlemanly_engine/classge_1_1actor.html)---tick that is called each frame. To use this interface, make your own actor class:
```C++
#include <ge/actor.hpp>
#include <ge/tickable.hpp>

struct my_actor : ge::actor {
```

then implement a tick function:

```C++
	void tick(std::chrono::duration<float> delta) { ... }
```

Then tell the actor that you are implementing the interface:

```C++
	void initialize() {
		add_interface<my_actor, ge::tickable>();
	}
```

All done! You will now get tick events every frame.


##Creating your own actor interface
Creating your own actor interface is easy. First just create your own struct/class:
```C++
struct helloer_interface {
```

Then define the data you want to store per actor in a struct named `interface_storage`:
```C++
	struct interface_storage {
		// Consturctor so it can be used with make_shared
		interface_storage(std::string msg) : hello_message(msg) {}
		std::string hello_message;
		// It's often helpful to use std::functions here too (that's what tickable does)
	};
```

Then just define how this interface storage object is generated in a function template named `gen_interface`:
```C++
	template<typename ActorType>
	std::shared_ptr<interface_storage> gen_interface(ActorType* act) {
		return make_shared<interface_storage>(act->hello_str);		
	}
};
```

That's it! Now to use that, just use `add_interface` and make sure to add a hello_str object:

```C++
struct english_man : ge::actor {
	std::string hello_str = "Hello";
	void initialize() {
		add_interface<english_man, helloer_interface>();
	}
};
struct spanish_man : ge::actor {
	std::string hello_str = "Hola";
	void initialize() {
		add_interface<spanish_man, helloer_interface>();
	}
};
```

Now both of these actors define that interface. 
