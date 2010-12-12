varying vec2 texture_coordinate0;


void main(void)
{
    // Passing The Texture Coordinate Of Texture Unit 0 To The Fragment Shader
   texture_coordinate0 = gl_MultiTexCoord0.st;
   // Transforming The Vertex
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}