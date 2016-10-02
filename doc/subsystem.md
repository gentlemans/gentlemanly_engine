#Subsystems
Subsystems provide the core modularity of the engine, they allow for systems to be entirely turned on or off based on your needs. For example, look at the [audio example](https://github.com/gentlemans/gentlemanly_engine/blob/master/samples/audio), which doesn't even have a window, just audio!

##The [`runtime` class](https://gentlemans.github.io/gentlemanly_engine/structge_1_1runtime.html)
The [`runtime`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1runtime.html) manages subsystems. You can add a subsystem to it using the [`runtime::add_subsystem` ](https://gentlemans.github.io/gentlemanly_engine/structge_1_1runtime.html#ac11722b96ceed4739ff4cb588226a44c) template function: 
```C++
r.add_subsystem<ge::input_subsystem>({});
```
The parameter is always the `new_subsystem::config` object, for this class it's empty, so for something like [`sdl_subsystem`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1sdl__subsystem.html) you would pass in a [`sdl_subsystem::config`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1sdl__subsystem_1_1config.html) object like this:
```C++
r.add_subsystem<ge::sdl_subsystem>({
	"hello", // title
	{}, // location on screen, {} for undefined
	{1280, 720} // window size
});
```

##Creating your own subsystems
Creating subsystems is easy! Start by creating your own `class`/`struct` derriving from `subsystem`:
```C++
#include <ge/subsystem.hpp>

struct randomprinter : subsystem {

```

Then you will need a `config` object. For many subsystems this is empty, but this subsystem will request a seed:
```C++
	struct config { size_t seed; };
```

Next is the initialization function, that takes in a `config` object and returns a bool for success:
```C++
	bool initialize(config conf) {
		if(conf.seed == 42) {
			m_subsystem->m_log->error("42 is my favorite number, and it can't be yours. Failing to initialize subsystem...");
			return false; // This will issue a warning from the runtime. 
		}
		srand(conf.seed);
		return true;
	}
```
> **NOTE:** initialize is *not* a virtual function. 

That's the only requried parts, but there are still two virtual functions in [`subsystem`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1subsystem.html) that can be overrided: [`subsystem::update`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1subsystem.html#accd6950ca80930e52cb8d7bd9cb363de) and [`subsystem::shutdown`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1subsystem.html#ac8b7d7ac13414dd3c7fdcb1386611871). 

###[`subsystem::update`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1subsystem.html#accd6950ca80930e52cb8d7bd9cb363de)
This is called every frame, no matter what, with a parameter of `std::chrono::duration<float>` which is the delta time and returs if the program should continue:
```C++
	virtual bool update(std::chrono::duration<float> delta) override {
		auto the_number = rand();
		m_runtime->m_log->info("Your number is " + std::to_string(the_number);
	
		if(the_number == 4200) {
			m_runtime->m_log->info("You got it! App exiting...");
			return false;
		}
		return true;
		
	}
```

###[`subsystem::shutdown`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1subsystem.html#ac8b7d7ac13414dd3c7fdcb1386611871)
This is called when the runtime is cleaning up and the subsystem should free it's resources. It returns another success bool:

```C++
	virtual bool shutdown() override { return true; }
```

