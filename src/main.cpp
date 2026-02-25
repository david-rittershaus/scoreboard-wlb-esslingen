#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {

	ShowWindow(GetConsoleWindow(), SW_HIDE);

	ofGLFWWindowSettings settings;
	settings.width = 600;
	settings.height = 600;
	settings.setPosition(ofVec2f(500, 50));
	settings.resizable = true;


	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	settings.width = 400;
	settings.height = 500;
	settings.setPosition(ofVec2f(0, 50));
	settings.resizable = true;

	settings.shareContextWith = mainWindow;
	shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
	guiWindow->setVerticalSync(false);

	shared_ptr<ofApp> mainApp(new ofApp);
	mainApp->setupGui();
	ofAddListener(guiWindow->events().draw, mainApp.get(), &ofApp::drawGui);

	ofRunApp(mainWindow, mainApp);
	ofRunMainLoop();

}
