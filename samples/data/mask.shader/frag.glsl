#version 100
precision highp float;

uniform sampler2D tex;
uniform vec4 oncolor;
uniform vec4 offcolor;

varying vec2 tex_coords;

void main()
{
	float alpha = texture2D(tex, tex_coords).a;

	gl_FragColor = alpha * oncolor + (1.0 - alpha) * offcolor;
}
