varying vec2 texture_coordinate0;


void main(void)
{
   // Transforming The Vertex
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

   // Passing The Texture Coordinate Of Texture Unit 0 To The Fragment Shader
   texture_coordinate0 = vec2(gl_MultiTexCoord0);
}