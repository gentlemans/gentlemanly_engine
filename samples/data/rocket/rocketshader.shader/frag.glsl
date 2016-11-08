#version 100
precision highp float;

uniform sampler2D tex;

uniform int use_texture;

varying vec2 tex_coords;
varying vec4 vert_colors;

void main()
{
	gl_FragColor = float(use_texture) * texture2D(tex, tex_coords)
		+ float(1 - use_texture) * vert_colors;

	if(gl_FragColor.a < 0.1) discard;

}
