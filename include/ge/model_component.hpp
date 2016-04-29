#pragma once

#include <anax/Component.hpp>

#include <memory>

#include <glm/glm.hpp>

namespace ge
{
class mesh;
class material;

class model_component : public anax::Component
{
public:
	std::shared_ptr<mesh> m_mesh;
	std::shared_ptr<material> m_material;
};
}
