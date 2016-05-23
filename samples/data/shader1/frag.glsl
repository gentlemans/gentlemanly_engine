#version 100

precision highp float;


uniform vec4 col;

void main()
{
	gl_FragColor = col;
}
