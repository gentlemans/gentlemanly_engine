#pragma once

#include <ge/actor.hpp>
#include "grid.hpp"
#include "toweractor.hpp"
#include "gridtick_interface.hpp"

class zombie : public toweractor
{
    void initialize(glm::uvec3 location) {
        toweractor::initialize(location);

        add_interface<zombie, gridtick_interface>();

    }

    void gridtick() {

    }
};
