#version 100
precision highp float;

varying vec2 tex_coords;

uniform int dimx;
uniform int dimy;

uniform int current_frame;

uniform sampler2D tex;

void main() {
	float currentx = mod(float(current_frame), float(dimx));
	float currenty = float(current_frame / dimx);

	gl_FragColor = texture2D(tex, vec2(
		(currentx + tex_coords.x) / float(dimx),
		(currenty + tex_coords.y) / float(dimy)
	));
	
	if(gl_FragColor.a < 0.1) discard;
	
}
