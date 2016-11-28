#ifndef TICKTIMER_SUBSYSTEM_HPP
#define TICKTIMER_SUBSYSTEM_HPP

#include <ge/subsystem.hpp>
#include <ge/actor.hpp>

#include "gridtick_interface.hpp"

#include <boost/signals2.hpp>

struct ticktimer : public ge::actor {

    void initialize() {
        add_interface<ticktimer, gridtick_interface>();
    }

    std::deque<boost::signals2::signal<void()>> callbacks;

    void tick_grid() {
        // run the callbakcs
        callbacks[0]();

        callbacks.pop_front();
    }

    boost::signals2::connection addTimer(int nTicks, std::function<void()> call) {
        return callbacks[nTicks].connect(call);
    }


};

#endif // TICKTIMER_SUBSYSTEM_HPP
