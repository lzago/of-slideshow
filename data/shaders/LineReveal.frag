uniform sampler2D oldTex;
uniform sampler2D newTex;
varying vec2 texture_coordinate0;
uniform  float progress;
const vec2 lineOrigin = vec2(-0.2, -0.2);
const vec2 lineOffset = vec2(1.0,0.0);
const vec2 lineNormal = vec2(1.4, 0.0);
const float fuzzyAmount = 0.2;

   void main()
   {
         
   vec2 currentLineOrigin = lerp(lineOrigin, lineOffset, progress);
   vec2 normLineNormal = normalize(lineNormal);
   vec4 c1 = texture2D(oldTex, texture_coordinate0);
   vec4 c2 = texture2D(newTex, texture_coordinate0);
   float distFromLine = dot(normLineNormal, texture_coordinate0-currentLineOrigin);
   float p = saturate((distFromLine + fuzzyAmount) / (2.0 * fuzzyAmount));
   gl_FragColor = lerp(c2, c1, p);

   }