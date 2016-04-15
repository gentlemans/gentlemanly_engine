#pragma once

#include "ge/actor.hpp"

#include <memory>

namespace ge
{
class mesh;
class material;

class model : public actor
{
	std::shared_ptr<mesh> mesh_for_model;
	std::shared_ptr<material> material_for_model;

public:
	model(actor* parent, const std::shared_ptr<mesh>& mesh,
		  const std::shared_ptr<material>& material);

	virtual void render(const glm::mat3& view_projection_matrix) override;
};
}
