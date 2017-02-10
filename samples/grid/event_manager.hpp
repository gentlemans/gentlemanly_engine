#pragma once

#ifndef GRID_EVENT_MANAGER_HPP
#define GRID_EVENT_MANAGER_HPP

#include <functional>

#include <Rocket/Core.h>

void initialze_event_manager();
void register_event(const char* name, std::function<void(Rocket::Core::Event& ev)> event);


#endif // GRID_EVENT_MANAGER_HPP
