uniform sampler2D oldTex;
uniform sampler2D newTex;
varying vec2 texture_coordinate0;
uniform  float progress;
const float PI = 3.14159265358979323846264;
const float twistAmount = PI * 4.0;

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
         
   float cellcount = 10.0;
   float cellsize = 1.0 / cellcount;
   
   vec2 cell = floor(texture_coordinate0 * cellcount);
   vec2 oddeven = fmod(cell, 2.0);
   float cellTwistAmount = twistAmount;
   if (oddeven.x < 1.0)
   {
      cellTwistAmount *= -1.0;
   }
   if (oddeven.y < 1.0)
   {
      cellTwistAmount *= -1.0;
   }
      
   vec2 newUV = fract(texture_coordinate0 * cellcount);
   
   vec2 center = vec2(0.5,0.5);
   vec2 toUV = newUV - center;
   float distanceFromCenter = length(toUV);
   vec2 normToUV = toUV / distanceFromCenter;
   float angle = atan2(normToUV.y, normToUV.x);
   
   angle += distanceFromCenter * distanceFromCenter * cellTwistAmount * progress;
   vec2 newUV2;
   sincos(angle, newUV2.y, newUV2.x);
   newUV2 *= distanceFromCenter;
   newUV2 += center;
   
   newUV2 *= cellsize;
   newUV2 += cell * cellsize;
   
   vec4 c1 = texture2D(oldTex, newUV2);
   vec4 c2 = texture2D(newTex, texture_coordinate0);

    gl_FragColor = lerp(c1,c2, progress);

   }