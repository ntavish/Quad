#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"
#include <cstdlib>

//========================================================================
int main( ){

    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1024,600, OF_GAME_MODE);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}
