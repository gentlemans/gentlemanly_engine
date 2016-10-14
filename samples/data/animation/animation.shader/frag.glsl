#version 330 core

in vec2 tex_coords;

out vec4 frag_color;

uniform int dimx;
uniform int dimy;

uniform int current_frame;

uniform sampler2D tex;

void main() {
	int currentx = current_frame % dimx;
	int currenty = current_frame / dimx;

	frag_color = texture(tex, vec2(
		(currentx + tex_coords.x) / float(dimx),
		(currenty + tex_coords.y) / float(dimy)
	));
	
	if(frag_color.a < 0.1) discard;
	
}
