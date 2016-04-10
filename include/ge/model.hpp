#pragma once

#include "ge/actor.hpp"

#include <memory>

namespace ge {

class mesh;
class material;

class model : public actor
{
	model(actor* parent, std::shared_ptr<mesh> mesh, std::shared_ptr<material> mat);
	
};

}
