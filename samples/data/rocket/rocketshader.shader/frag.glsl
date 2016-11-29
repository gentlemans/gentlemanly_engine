#version 100
precision highp float;

uniform sampler2D tex;

uniform int use_texture;

varying vec2 tex_coords;
varying vec4 vert_colors;

void main()
{
	if(use_texture) {
		gl_FragColor = texture2D(tex, tex_coords);
		gl_FragColor += vert_colors * (1 - gl_FragColor.a);
	} else {
		gl_FragData = vert_colors;
	}
	
	if(gl_FragColor.a < 0.1) discard;

}
