#pragma once

#ifndef GRID_EVENT_MANAGER_HPP
#define GRID_EVENT_MANAGER_HPP

#include <functional>

#include <Rocket/Core.h>

using event_handler_func = std::function<void (Rocket::Core::Event &, const std::string& args)>;

void initialze_event_manager();
void register_event(const char* name, event_handler_func event);


#endif // GRID_EVENT_MANAGER_HPP
