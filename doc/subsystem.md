#Subsystems
Subsystems are the main modular component of gentlemanly_engine, making it easy to add new components to the engine. Subsystems are designed to be objects holding some game-wide state that does a certain function, and possibly needs a callback each frame. For example, the [`rocket_subsystem`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1rocket__subsystem.html) holds the `Rocket::Core::Context` object and provides that object for anyone who needs it, along with rendering  the UI every frame.

##Adding subsystems
Adding a subsystem is as easy as getting a [`runtime`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1runtime.html) and calling the `add_subsystem`function and passing the subsystem config object to it:
```C++
runtime.add_subsystem<my_subsystem>(my_subsystem::config{...});
```
for example, to initialize the [`input_subsystem`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1input__subsystem.html), run
```C++
runtime.add_subsystem<ge::input_subsystem>({});
```
because the config object is empty.

##Getting existing subsystems
Existing subsystems can be fetched by using the `get_subsystem` function:
```C++
auto subsystemptr = m_runtime.get_subsystem<my_subsystem>();
```
and if the subsystem doesn't exist, then it will return `nullptr`. 