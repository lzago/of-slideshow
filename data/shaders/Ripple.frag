uniform sampler2D oldTex;
uniform sampler2D newTex;
varying vec2 texture_coordinate0;
uniform  float progress;

   void main()
   {
         
   float frequency = 20.0;
   float speed = 10.0;
   float amplitude = 0.05;
   vec2 center = vec2(0.5,0.5);
   vec2 toUV = texture_coordinate0 - center;
   float distanceFromCenter = length(toUV);
   vec2 normToUV = toUV / distanceFromCenter;

   float wave = cos(frequency * distanceFromCenter - speed * progress);
   float offset1 = progress * wave * amplitude;
   float offset2 = (1.0 - progress) * wave * amplitude;
   
   vec2 newUV1 = center + normToUV * (distanceFromCenter + offset1);
   vec2 newUV2 = center + normToUV * (distanceFromCenter + offset2);
   
   vec4 c1 = tex2D(oldTex, newUV1); 
   vec4 c2 = tex2D(newTex, newUV2);

   gl_FragColor = lerp(c1, c2, progress);

   }