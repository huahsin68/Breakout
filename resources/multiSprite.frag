#version 330 core


uniform sampler2D text;
in vec2 o_texCoord;

void main (void)
{
	gl_FragColor = texture(text, o_texCoord);
}