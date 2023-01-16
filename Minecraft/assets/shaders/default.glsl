#shader vertex
#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aUV;

out vec3 oUV;

uniform mat4 uPV;

void main()
{
	oUV = aUV;
	gl_Position = uPV * vec4(aPos.xyz, 1.0);
}

#shader fragment
#version 330 core

in vec3 oUV;
out vec4 fragColor;
uniform sampler2D uTexture;

void main()
{
	fragColor = vec4(1.0, 0.0, 0.0, 1.0);
}