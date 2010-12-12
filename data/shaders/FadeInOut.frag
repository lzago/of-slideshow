uniform sampler2D oldTex;
uniform sampler2D newTex;
varying vec2 texture_coordinate0;
uniform  float progress;
varying float step;

   
   void main()
   {
       vec4 c1 = texture2D(oldTex, texture_coordinate0);
       vec4 c2 = texture2D(newTex, texture_coordinate0);
       vec4 black = vec4(0.0,0.0,0.0,1.0);
       if (progress < 0.5) {
		  step = progress * 2;
          gl_FragColor = lerp(c1,black,step); 
       } else {
		  step = (progress - 0.5) * 2;
          gl_FragColor = lerp(black,c2, step);
       }
   }