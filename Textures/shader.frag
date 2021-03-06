#version 330 core

in vec3 ourColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	// FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
	// FragColor = mix(texture(texture1, texCoord), texture(texture2, vec2(1.0f-texCoord.x, texCoord.y)), 0.2);
	FragColor = mix(texture(texture1, texCoord), texture(texture2, vec2(1.0f-texCoord.x, texCoord.y)), 0.2) * vec4(ourColor, 1.0f);
	// FragColor = texture(ourTexture, texCoord) * vec4(ourColor, 1.0f);
}