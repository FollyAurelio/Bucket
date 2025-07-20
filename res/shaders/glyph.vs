#version 330

layout (location = 0) in vec4 vertices;
out vec2 texCoords;

void main()
{
	gl_Position = vec4(vertices.x, vertices.y, 0.0, 1.0);
	texCoords = vertices.zw;
}

