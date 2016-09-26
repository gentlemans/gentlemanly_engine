#Tutorial 03: Handling input

In any game, input is an important part of defining how it works. Hanlding input is made easy in ge. 

##The [`input_subsystem`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1input__subsystem.html)
The input subsystem is very simple: it takes events passed in through [`input_subsystem::add_event`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1input__subsystem.html#afdf06c55b866a2b2f19440b0a3494988) and then it passes it to the correct [`input_consumer`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1input__consumer.html). 

##Creating your own  [`input_consumer`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1input__consumer.html)

It is incredibly easy to create input consumers, any class can be one. Just make your class derive from `input_consumer<derived>`, along with the classes you derived from before:
```C++
#include <ge/input_subsystem.hpp>

class player : public actor, public input_consumer<player> {
```

Then define a `handle_input(const input_event& event)` function:
```C++
	void handle_input(const input_event& event) {
		// do whatever you want with it, input_event is a boost::variant.
	}
}
```
See: [input_event.hpp](https://gentlemans.github.io/gentlemanly_engine/input__event_8hpp_source.html)

###Stealing input
Only one input consumer can recieve input at a time. In order to choose which one that is, use the protected function [`input_consumer::steal_input`](https://gentlemans.github.io/gentlemanly_engine/structge_1_1input__consumer.html#aea7b9328ba76c84a4728d6c3237f3491) in your input consumer. 