#include "ge/window_backend/sdl.hpp"

#include <iostream>

namespace ge {
namespace window_backend {

void sdl::execute()
{
	while(running)
	{
		app.update();
	}
}


} // namespace ge
} // namespace window_backend
