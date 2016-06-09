#version 330 core


uniform vec4 col;

out vec4 frag_color;

void main()
{
	frag_color = col;
}
