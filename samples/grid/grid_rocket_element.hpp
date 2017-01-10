#pragma once

#ifndef GENTLEMANLY_ENGINE_GRID_ROCKET_ELEMENT_HPP
#define GENTLEMANLY_ENGINE_GRID_ROCKET_ELEMENT_HPP

#include <Rocket/Core.h>

#include <glm/glm.hpp>

#include <iostream>

class grid_rocket_instancer : public Rocket::Core::ElementInstancer {
    Rocket::Core::Element* InstanceElement(Rocket::Core::Element* parent,
    const Rocket::Core::String& tag,
    const Rocket::Core::XMLAttributes& attributes) override {
        attributes.Get("start")->Get<glm::uvec3>();
    }

};

class grid_rocket_element : public Rocket::Core::Element {
    grid_rocket_element(glm::vec2 startPx, glm::vec2 sizePx, glm::uvec3 id) : Rocket::Core::Element("grid_rocket_element"), m_id{id} {
        Rocket::Core::Box b;
        b.SetOffset({startPx.x, startPx.y});
        b.SetContent({sizePx.x, sizePx.y});

        SetBox(b);
    }

    static void registerInstancer() {
        Rocket::Core::ElementInstancer* custom_instancer = new Rocket::Core::ElementInstancerGeneric< grid_rocket_element >();
        Rocket::Core::Factory::RegisterElementInstancer("grid_piece", custom_instancer);

    }

    void ProcessEvent(Rocket::Core::Event& ev) override  {
        if(ev.GetType() == "mouse") {
            std::cout << m_id.x << ", " << m_id.y << ", " << m_id.z << std::endl;
        }
    }

    glm::uvec3 m_id;

};

#endif //GENTLEMANLY_ENGINE_GRID_ROCKET_ELEMENT_HPP
