#pragma once

#ifndef GENTLEMANLY_ENGINE_GRID_ROCKET_ELEMENT_HPP
#define GENTLEMANLY_ENGINE_GRID_ROCKET_ELEMENT_HPP

#include <Rocket/Core.h>

#include <glm/glm.hpp>

#include <iostream>

#include "grid.hpp"

class grid_rocket_element : public Rocket::Core::Element {
public:
    grid_rocket_element(glm::vec2 startPx, glm::vec2 sizePx, glm::uvec2 id) : Rocket::Core::Element("grid_rocket_element"), m_id{id} {

        SetProperty("position", "absolute");
        SetProperty("left", std::to_string(startPx.x).c_str());
        SetProperty("top", std::to_string(startPx.y).c_str());
        SetProperty("width", std::to_string(sizePx.x).c_str());
        SetProperty("height", std::to_string(sizePx.y).c_str());

        //SetProperty("background-color", ("rgb(0%, " + std::to_string(rand() % 256)+ "%, " + std::to_string(rand() % 256) + "%)").c_str());

    }


    void ProcessEvent(Rocket::Core::Event& ev) override  {
        if(ev.GetType() == "mousedown") {
            std::cout << m_id.x << ", " << m_id.y << ", " << std::endl;
        }
    }

    glm::uvec2 m_id;

};


class grid_rocket_instancer : public Rocket::Core::ElementInstancer {
public:
    Rocket::Core::Element* InstanceElement(Rocket::Core::Element* parent,
                                           const Rocket::Core::String& tag,
                                           const Rocket::Core::XMLAttributes& attributes) override {
        glm::uvec2 id = {attributes.Get("idx")->Get<int>(), attributes.Get("idy")->Get<int>()};
        glm::vec2 start = {attributes.Get("start")->Get<Rocket::Core::Vector2f>().x, attributes.Get("start")->Get<Rocket::Core::Vector2f>().y};
        glm::vec2 size = {attributes.Get("size")->Get<Rocket::Core::Vector2f>().x, attributes.Get("size")->Get<Rocket::Core::Vector2f>().y};


        return new grid_rocket_element(start, size, id);
    }

    void ReleaseElement(Rocket::Core::Element* el) override {
        delete el;
    }

    void Release() override {}


    static void registerInstancer() {
        Rocket::Core::ElementInstancer* custom_instancer = new grid_rocket_instancer();
        Rocket::Core::Factory::RegisterElementInstancer("grid_rocket", custom_instancer);
        custom_instancer->RemoveReference();

    }

};

#endif //GENTLEMANLY_ENGINE_GRID_ROCKET_ELEMENT_HPP
