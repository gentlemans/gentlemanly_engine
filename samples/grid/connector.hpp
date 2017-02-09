//
// Created by Russell Greene on 1/23/17.
//

#ifndef GENTLEMANLY_ENGINE_CONNECTOR_HPP
#define GENTLEMANLY_ENGINE_CONNECTOR_HPP

#include <boost/signals2.hpp>

template <typename SignalT, typename FuncT>
boost::signals2::connection connect_track(
	SignalT& signal, FuncT&& function, std::weak_ptr<void> track)
{
	return signal.connect(
		typename SignalT::slot_type(std::forward<FuncT>(function)).track_foreign(std::move(track)));
};

#endif  // GENTLEMANLY_ENGINE_CONNECTOR_HPP
