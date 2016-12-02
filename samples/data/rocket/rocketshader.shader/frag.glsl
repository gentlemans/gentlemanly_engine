#version 100
precision highp float;

uniform sampler2D tex;

uniform int use_texture;

varying vec2 tex_coords;
varying vec4 vert_colors;

void main()
{
	vec4 tcolor = (float(use_texture) * texture2D(tex, tex_coords)) + (float(1 - use_texture) * vec4(0, 0, 0, 1));
	
	gl_FragColor = vec4(vert_colors.xyz * tcolor.a, tcolor.a);
	
	if(gl_FragColor.a < .01) discard;
}
