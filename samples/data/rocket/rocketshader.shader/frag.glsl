#version 100
precision highp float;

uniform sampler2D tex;

uniform int use_texture;

varying vec2 tex_coords;
varying vec4 vert_colors;

void main()
{
	vec4 tcolor = (float(use_texture) * texture2D(tex, tex_coords)) + (float(1 - use_texture) * vec4(0, 0, 0, 0));
	vec3 combinedcolor = (tcolor.rgb) + (vert_colors.rgb);
	gl_FragColor = vec4(combinedcolor, 1.0);

	if(gl_FragColor.a < 0.1) discard;

}
