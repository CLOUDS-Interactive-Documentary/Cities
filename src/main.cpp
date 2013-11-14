#include "testApp.h"
#include "ofAppGlutWindow.h"

//--------------------------------------------------------------
int main(){
	ofAppGlutWindow window; // create a window
							// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
    window.setGlutDisplayString("rgba double samples>=4 depth");
    window.setGlutDisplayString("rgba double samples>=4 depth alpha");
	
//	window.setGlutDisplayString("rgba double depth samples>=4");
//	window.setGlutDisplayString("rgba double depth alpha samples>=4");

	ofSetupOpenGL(&window, 1224, 768, OF_WINDOW);
	ofRunApp(new testApp()); // start the app
}
