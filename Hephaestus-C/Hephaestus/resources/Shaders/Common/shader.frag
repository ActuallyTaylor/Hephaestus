#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}

//#version 330 core
//out vec4 FragColor;
//
//in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)
//
//void main()
//{
//    FragColor = vertexColor;
//}
