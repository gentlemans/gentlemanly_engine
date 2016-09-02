#include <ge/runtime.hpp>
#include <ge/sdl_subsystem.hpp>

#include <glm/glm.hpp>

#include <memory>

#include "grid.hpp"
#include "toweractor.hpp"
#include "zombie.hpp"

using namespace ge;

int main(int argc, char** argv)
{
	runtime r;

	r.add_subsystem<sdl_subsystem>(sdl_subsystem::config{"Hello", {}, {1024, 720}});
    
	
    while(r.tick());
}
