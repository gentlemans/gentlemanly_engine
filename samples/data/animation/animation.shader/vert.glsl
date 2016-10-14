#version 100

attribute vec2 loc;
attribute vec2 uvs;

uniform mat3 mvp_matrix;

varying vec2 tex_coords;

void main() {
	gl_Position.xyw = mvp_matrix * vec3(loc, 1.0);
	gl_Position.z = 0.0;
	
	tex_coords = uvs;
}
