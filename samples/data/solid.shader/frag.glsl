#version 100
precision highp float;

uniform vec4 color;

void main()
{
	gl_FragColor = color;

	if(gl_FragColor.a < 0.1) discard;

}
