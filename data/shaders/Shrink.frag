uniform sampler2D oldTex;
uniform sampler2D newTex;
varying vec2 texture_coordinate0;
uniform  float progress;

vec4 SampleWithBorder(vec4 border, sampler2D tex, vec2 uv)
{
   vec2 result = saturate(uv) - uv; 
   if (result.x != 0.0 || result.y != 0.0)
   {
      return border;
   }
   else
   {
      return texture2D(tex, uv);
   }
}


   void main()
   {
      float speed = 200.0;
      vec2 center = vec2(0.5,0.5);
      vec2 toUV = texture_coordinate0 - center;
      float distanceFromCenter = length(toUV);
      vec2 normToUV = toUV / distanceFromCenter;
   
      vec2 newUV = center + normToUV * (distanceFromCenter * (progress * speed + 1.0));
   
      vec4 c1 = SampleWithBorder(vec4(0.0,0.0,0.0,0.0), oldTex, newUV); 

      if(c1.a <= 0.0) {
         gl_FragColor = texture2D(newTex, texture_coordinate0);
      }
   
      gl_FragColor = c1;

   }