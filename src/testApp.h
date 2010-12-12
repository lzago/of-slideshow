#ifndef _TEST_APP
#define _TEST_APP

// Slideshow
// An oF app that loads media files from a local directory and then displays up them in a slideshow style using
// a set of shaders to customize the transition logic.
// System design and assembly by Luca Zago, 

// slideshow logic based upon work by prisonerjohn, memo akten, theo watson, zachary lieberman, otherside, arturo
// http://www.openframeworks.cc/forum/viewtopic.php?t=816

//the main contibute for the code was by charli_e and AlexandreRangel
// http://www.openframeworks.cc/forum/viewtopic.php?t=1408

// all thanks to openFrameworks
// http://www.openFrameworks.cc
// and especially Zachary Lieberman and Theo Watson


#define OF_ADDON_USING_OFXOPENCV
#define OF_ADDON_USING_OFXOBJLOADER
#define OF_ADDON_USING_OFXDIRLIST
#define OF_ADDON_USING_OFXVECTORMATH
#define OF_ADDON_USING_OFXNETWORK
#define OF_ADDON_USING_OFXVECTORGRAPHICS
#define OF_ADDON_USING_OFXOSC
#define OF_ADDON_USING_OFXTHREAD
#define OF_ADDON_USING_OFXXMLSETTINGS


#include "ofMain.h"
#include "imgLoader.h"
#include "ofxShader.h"
#include "ParamsLoader.h"

class testApp : public ofSimpleApp {

   public:
      void setup();
      void update();
      void draw();

      void keyPressed  (int key);
      void mouseMoved(int x, int y );
      void mouseDragged(int x, int y, int button);
      void mousePressed(int x, int y, int button);
      void mouseReleased();
	  ofImage * loadImage(string filePath);
	  //void crossFadeTransition(ofImage* currImg,ofImage* nextImg);
	  void fadeInfadeOut(ofImage* currImg,ofImage* nextImg);
	  void shaderTransition(ofImage* currImg,ofImage* nextImg);
	  //ofVideoPlayer * loadVideo(string filePath);
	  //ofTexture* buildSlideTexture(ofImage* im);
		

		//ofVideoPlayer  textureMovie;
	    ParamsLoader loaderConfig;
        ofImage * currImage;
		ofImage * nextImg;
        ofTexture temp_cur_texture;
		ofxShader transitionShader;
		ofTexture temp_next_texture;

        imgLoader   loader;
        bool        loadNextImg;
		bool transitionEnded;
		bool transitionStarted;

		float		step;
		float		progress;

private:
	int getCenteredCoordinate(ofImage* image);
};

#endif

