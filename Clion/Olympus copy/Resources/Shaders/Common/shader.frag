#version 330 core
out vec4 FragColor;

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
/*
 
 #version 330 core
 in vec2 TexCoords;
 out vec4 color;

 uniform sampler2D image;
 uniform vec3 spriteColor;

 void main()
 {
     color = vec4(spriteColor, 1.0) * texture(image, TexCoords);
 }
 */
