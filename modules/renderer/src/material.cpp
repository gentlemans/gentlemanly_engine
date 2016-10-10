#include "ge/material.hpp"
#include "ge/shader.hpp"

namespace ge
{
material::material(const std::shared_ptr<const shader>& arg_shader) : m_shader{arg_shader}
{
}

material::~material() = default;
}
