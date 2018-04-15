#version 330 core
out vec4 FragColor;

flat in vec3 myColor;
in vec2 texCoord;

uniform sampler2D ourTexture;
uniform int textureMode;

void main()
{ 
	/*
	if (textureMode != 0)
	{
		FragColor = texture(ourTexture, texCoord);
	}
	else
	{
		FragColor = vec4(myColor, 1.0);
	}
	*/
	FragColor = vec4(myColor, 1.0);
}
