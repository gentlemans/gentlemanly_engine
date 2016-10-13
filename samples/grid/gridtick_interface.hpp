#ifndef GE_GRIDTICK_INTERFACE_HPP
#define GE_GRIDTICK_INTERFACE_HPP

#pragma once

#include <functional>


struct gridtick_interface {

    struct interface_storage {
        interface_storage(const std::function<void()> call) : callback(call) {}
        std::function<void()> callback;
    };

    template<typename ActorType>
    static std::shared_ptr<interface_storage> gen_interface(ActorType* act) {
        return std::make_shared<interface_storage>([act]() {

            // If you get an error here, then you need to define the tick_grid function
            act->tick_grid();
        });
    }
};

#endif // GE_GRIDTICK_INTERFACE_HPP
