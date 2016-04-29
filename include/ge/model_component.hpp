#pragma once

#include <anax/Component.hpp>

#include <memory>

namespace ge
{
class mesh;
class material;

class model_component : public anax::Component
{
public:
	std::shared_ptr<mesh> m_mesh;
	std::shared_ptr<material> m_material;

	model_component(std::shared_ptr<mesh> mesh,
		std::shared_ptr<material> material)
		:m_mesh{std::move(mesh)},
		m_material{std::move(material)}
	{
	}

	void render(const glm::mat3& view_projection_matrix);
};
}
