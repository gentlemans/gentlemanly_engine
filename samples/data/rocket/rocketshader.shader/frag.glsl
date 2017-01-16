#version 100
precision highp float;

uniform sampler2D tex;

uniform int use_texture;

varying vec2 tex_coords;
varying vec4 vert_colors;

void main()
{
	gl_FragColor = texture2D(tex, tex_coords) * vert_colors;

	if(gl_FragColor.a < .01) discard;
}
