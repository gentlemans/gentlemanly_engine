#pragma once

#include <memory>

#include <glm/glm.hpp>

namespace ge
{
class shader;

class material
{
public:
	std::shared_ptr<shader> m_shader;

	material(const std::shared_ptr<shader>& shader);

	~material();
};
}
