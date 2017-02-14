#include "event_manager.hpp"

#include <unordered_map>

namespace  {
std::unordered_map<std::string, event_handler_func> handlers;

class EventListener : public Rocket::Core::EventListener {
public:
	event_handler_func m_func;
	std::string m_args;
	
	EventListener(event_handler_func func, std::string args) : m_func{std::move(func)}, m_args{std::move(args)} {}
	
	
	virtual void ProcessEvent(Rocket::Core::Event& event) {
		m_func(event, m_args);
	}

};

class EventInstancer : public Rocket::Core::EventListenerInstancer {
	/// Instances a new event handle for Invaders.
	Rocket::Core::EventListener* InstanceEventListener(const Rocket::Core::String& value, Rocket::Core::Element* element) override{
		Rocket::Core::StringList commands;
		Rocket::Core::StringUtilities::ExpandString(commands, value, ';');
		
		for (const auto& commandRstring : commands) {
			
			auto command = std::string{commandRstring.CString()};
			
			auto commandName = command.substr(0, command.find(' '));
			auto commandArgs = command.substr(command.find(' ') + 1);
			
			auto iter = handlers.find(commandName);
			if (iter != handlers.end()) {
				return new EventListener(iter->second, commandArgs);
			}
			
		}
		return nullptr;
	}

	/// Destroys the instancer.
	void Release() override {
		
	}

};

}

void initialze_event_manager()
{
	Rocket::Core::Factory::RegisterEventListenerInstancer(new EventInstancer);
}


void register_event(const char* name, event_handler_func event)
{
	
	handlers[name] = std::move(event);
}
