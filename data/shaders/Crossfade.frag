uniform sampler2D oldTex;
uniform sampler2D newTex;
varying vec2 texture_coordinate0;
uniform  float progress;

   
   void main()
   {
       vec4 c1 = texture2D(oldTex, texture_coordinate0);
       vec4 c2 = texture2D(newTex, texture_coordinate0);
       gl_FragColor = lerp(c1,c2, progress);
   }