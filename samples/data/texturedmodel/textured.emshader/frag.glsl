#version 100
precision mediump float;

varying vec2 tex_coords;

uniform sampler2D tex;

void main()
{

	gl_FragColor = texture2D(tex, tex_coords);

	if(gl_FragColor.a < 0.1) discard;
}
