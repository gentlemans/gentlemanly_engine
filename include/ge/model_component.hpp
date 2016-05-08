#pragma once

#include <glm/glm.hpp>

namespace ge
{
class mesh;
class material;

struct model_component
{
	model_component(std::shared_ptr<mesh> arg_mesh) : m_mesh{std::move(arg_mesh)} {}
	std::shared_ptr<mesh> m_mesh;
};
}
