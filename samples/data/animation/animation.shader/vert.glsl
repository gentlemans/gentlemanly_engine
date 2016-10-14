#version 330 core

layout(location = 0) in vec2 loc;
layout(location = 1) in vec2 uvs;

uniform mat3 mvp_matrix;

out vec2 tex_coords;

void main() {
	gl_Position.xyw = mvp_matrix * vec3(loc, 1.0);
	gl_Position.z = 0.0;
	
	tex_coords = uvs;
}
