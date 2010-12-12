uniform sampler2D oldTex;
uniform sampler2D newTex;
varying vec2 texture_coordinate0;
uniform  float progress;

   void main()
   {
		 vec2 uv = texture_coordinate0;
         uv.x = texture_coordinate0.x + 1.0 * progress;
         vec2 resultUV = clamp(uv,0.0,1.0) - uv;
         if(resultUV.x != 0.0 || resultUV.y != 0.0)
         {   
            uv = frac(uv);
            gl_FragColor = texture2D(newTex, uv);
         } else {
            gl_FragColor = texture2D(oldTex, uv);
         }

   }