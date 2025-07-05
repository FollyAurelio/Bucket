#version 330 core
in vec3 ourColour;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D tex;
void main()
{
	FragColor = texture(tex, TexCoord) * vec4(ourColour,0.5f);
}
