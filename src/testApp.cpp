#include "testApp.h"
#include <direct.h>

char **files= new char*[16];


void testApp::setup() {
    ofBackground(0,0,0);
	ofSetLogLevel(OF_LOG_VERBOSE);
	//Loading config file
	//_chdir("../Media");
	int *params= new int[16];
	for (int i=0;i<16;i++) files[i]=new char[255];
	bool ok = loaderConfig.ReadConfigFile("data/slideshow.config",files,params,2,1);
	ofLog(OF_LOG_VERBOSE,"Step: %d",params[0]);
	ofLog(OF_LOG_VERBOSE,"Directory: %s",files[0]);
	ofLog(OF_LOG_VERBOSE,"Transition: %s",files[1]);
	//Loading shader
	string shaderPath(files[1]);
	transitionShader.loadShader("shaders/" + shaderPath);
    loader.start(files[0]);
    ofSetVerticalSync(true);
	currImage=NULL;
	nextImg=NULL;
    loadNextImg=false;
	transitionStarted = false;
	transitionEnded = false;
	progress = 0;
	step = (float)params[0] / 100;
    temp_cur_texture.allocate(1024,1024,GL_RGB); // CHANGE FOR THE SIZE OF THE IMAGES ...
	temp_next_texture.allocate(1024,1024,GL_RGB);
	ofSetFrameRate(35);
}

void testApp::fadeInfadeOut(ofImage* currImg,ofImage* nextImg) {
				glEnable(GL_BLEND);
				glColor4f(1.0f, 1.0f, 1.0f,1 - (progress * 2));   
				glBlendFunc(GL_SRC_ALPHA, GL_ZERO);   // takes src brightness (ignore dest color)	
				temp_cur_texture.loadData(currImg->getPixels(),currImg->width,currImg->height,GL_RGB);
				temp_cur_texture.draw(getCenteredCoordinate(currImg),0,currImg->width,currImg->height); //
				//If the second image disappeared
				if (progress >=0.5) {
					//Blend della seconda immagine
					glColor4f(1.0f, 1.0f, 1.0f,(progress - 0.5) * 2);   
					glBlendFunc(GL_SRC_ALPHA, GL_ONE);   // takes src brightness (ignore dest color)	
					temp_cur_texture.loadData(nextImg->getPixels(),nextImg->width,nextImg->height,GL_RGB);
					temp_cur_texture.draw(getCenteredCoordinate(nextImg),0,nextImg->width,nextImg->height); //
					if (progress >= 1.0) transitionEnded = true;
				}
}

void testApp::shaderTransition(ofImage* currImg,ofImage* nextImg) {
				transitionShader.setShaderActive(true);
				ofEnableAlphaBlending();
				temp_cur_texture.loadData(currImg->getPixels(),currImg->width,currImg->height,GL_RGB);
				temp_next_texture.loadData(nextImg->getPixels(),nextImg->width,nextImg->height,GL_RGB);
				glActiveTexture(GL_TEXTURE1);
				temp_cur_texture.bind();
				glActiveTexture(GL_TEXTURE2);
				temp_next_texture.bind();
				temp_cur_texture.draw(getCenteredCoordinate(currImg),0,currImg->width,currImg->height);
				//Start shader code
				transitionShader.setUniformVariable1i("oldTex", 1);
				transitionShader.setUniformVariable1i("newTex", 2);
				transitionShader.setUniformVariable1f("progress", progress);
				//check the 0,0 position of the image
				temp_next_texture.draw(getCenteredCoordinate(nextImg),0,nextImg->width,nextImg->height);
				if (progress > 1.0)  {
					//transitionShader.setShaderActive(false);
					temp_cur_texture.unbind();
					temp_next_texture.unbind();
					glActiveTexture(GL_TEXTURE0);
					transitionEnded = true;
				};
				ofDisableAlphaBlending();
				//transitionShader.setShaderActive(false);
}

int testApp::getCenteredCoordinate(ofImage* image) {
	int x = 0;
	if (image->width != 1024) x = 512 - (image->width / 2);
	return x;
}

void testApp::update(){

    //if (ofGetFrameNum()%500 == 0) loadNextImg=true;
	ofSetWindowTitle(ofToString(ofGetFrameRate(), 2.0));
	//Center the image
	//check the 0,0 position of the image
	//if (currImage->width != 1024) centerX = 512 - (currImage->width / 2);
	if(currImage != NULL){
		if (loadNextImg) {
				ofImage* temp_nextImg = loader.getNextTexture();
				nextImg = temp_nextImg;  
				loadNextImg=false;
		}
		if(transitionStarted) {
			progress = progress + step;
				if(transitionEnded) {
					transitionStarted = false;
					ofLog(OF_LOG_VERBOSE,"Animation ended, swapping");
					currImage=nextImg;
					loader.releaseCurrentTexture();
					transitionEnded = false;
					progress = 0;
				}
		}
	} else {
		//first time i load a picture
		ofImage* temp_nextImg = loader.getNextTexture();
		currImage = temp_nextImg;  
	}
}


void testApp::draw(){

    if(currImage!=NULL)
    {
		if (transitionStarted && nextImg!=NULL){
			transitionEnded = false;
			//crossFadeTransition(currImage,nextImg);
			//fadeInfadeOut(currImage,nextImg);
			shaderTransition(currImage,nextImg);
		 } else {
			ofSetColor(0xffffff);
			temp_cur_texture.loadData(currImage->getPixels(),currImage->width,currImage->height,GL_RGB);
			temp_cur_texture.draw(getCenteredCoordinate(currImage),0,currImage->width,currImage->height); //
		}
    }

}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
    /*
    if (key == 'a'){
        TO.start();
    } else if (key == 's'){
        TO.stop();
    }
    */
	if (key == 'a'){
       loadNextImg=true;
	   transitionStarted = true;
    }
}



//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(){

}