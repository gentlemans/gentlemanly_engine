#include "ge/input_consumer.hpp"

namespace ge {
	
	
	std::deque<std::pair<input_consumer_manager::consumer_func*, input_consumer_base*>> input_consumer_manager::consumers = {};
	
	size_t input_consumer_manager::active_consumer = ~0;
	
}
