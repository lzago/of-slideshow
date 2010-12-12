uniform sampler2D oldTex;
uniform sampler2D newTex;
varying vec2 texture_coordinate0;
uniform  float progress;

   
   void main()
   {
      if(frac(texture_coordinate0.y * 5.0) < progress) {
         gl_FragColor = texture2D(newTex, texture_coordinate0);
       } else {
         gl_FragColor = texture2D(oldTex, texture_coordinate0);
      }
   }