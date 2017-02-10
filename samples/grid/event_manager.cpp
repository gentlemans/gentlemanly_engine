#include "event_manager.hpp"

#include <unordered_map>

namespace  {
std::unordered_map<std::string, std::function<void (Rocket::Core::Event &)>> handlers;

class EventListener : public Rocket::Core::EventListener {
public:
	std::function<void (Rocket::Core::Event &)> m_func;
	
	EventListener(std::function<void (Rocket::Core::Event &)> func) : m_func{std::move(func)} {}
	
	/// Sends the event value through to Invader's event processing system.
	virtual void ProcessEvent(Rocket::Core::Event& event) {
		m_func(event);
	}

};

class EventInstancer : public Rocket::Core::EventListenerInstancer {
	/// Instances a new event handle for Invaders.
	Rocket::Core::EventListener* InstanceEventListener(const Rocket::Core::String& value, Rocket::Core::Element* element) override{
		Rocket::Core::StringList commands;
		Rocket::Core::StringUtilities::ExpandString(commands, value, ';');
		
		for (const auto& command : commands) {
			
			auto iter = handlers.find(command.CString());
			if (iter != handlers.end()) {
				return new EventListener(iter->second);
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


void register_event(const char* name, std::function<void (Rocket::Core::Event &)> event)
{
	
	handlers[name] = std::move(event);
}
