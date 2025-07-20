#version 330
in vec2 texCoords;
out vec4 color;
uniform sampler2D text;

void main()
{
	color = vec4(texture(text, texCoords).xyz, 1.0);
}
	
