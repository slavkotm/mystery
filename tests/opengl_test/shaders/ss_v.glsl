#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{	
	vec3 res_position = position;
//	res_position.x = 0.5f;
//	res_position.x = 100.0;
    gl_Position = vec4(res_position, 1.0f);
    ourColor = color;
    TexCoord = texCoord;
}
