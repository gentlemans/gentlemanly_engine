#version 100
precision highp float;

uniform sampler2D tex;
uniform vec3 discoloration;

varying vec2 tex_coords;

void main()
{
	gl_FragColor = texture2D(tex, tex_coords);
	gl_FragColor.rgb *= discoloration;

	if(gl_FragColor.a < 0.1) discard;

}
