#version 330 core

in vec2 o_texCoord;
in vec3 o_color;
out vec4 outputColor;

uniform sampler2D text;

void main (void)
{
	//gl_FragColor = texture(text, o_texCoord);
	// outputColor = texture(text, o_texCoord);
	
	vec4 texColor = texture(text, o_texCoord);
	if(texColor.a < 0.1)
        discard;
        
    outputColor = texColor;
}