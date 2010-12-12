#ifndef _TEXTURELOADER
#define _TEXTURELOADER

#include "ofMain.h"
//#define OF_ADDON_USING_OFXDIRLIST
//#define OF_ADDON_USING_OFXTHREAD
#include "ofxDirList.h"
#include "ofxThread.h"

class imgLoader : public ofxThread {
    public:
        imgLoader();
        ~imgLoader();

        void    start(string pathToImages);
        void    stop();
        void    threadedFunction();

        void    fetchTextureNames(string path);
        void    loadNextTexture();
        ofImage * getNextTexture();
        void    goForIt();
		void    releaseCurrentTexture();

    private:
        ofxDirList  dirList;
        string*     textures;
        int         numTextures;
        int         textureIndex;
        bool        go;

        //ARTURO
        ofImage * currTexture;
        ofImage * nextTexture;
		ofImage * to_delete_img;
        bool imgLoaded;

};

#endif