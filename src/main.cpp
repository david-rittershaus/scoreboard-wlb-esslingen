#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {

#ifdef TARGET_WIN32
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

#ifdef TARGET_OSX
	// Data-Pfad explizit setzen (OF-Standard kann fehlschlagen; Fallback für Projekt-data)
	std::string dataPath = ofFilePath::join(ofFilePath::getCurrentExeDir(), "../../../data");
	std::string fontCheck = ofFilePath::join(dataPath, "verdana.ttf");
	if (!ofFile::doesFileExist(fontCheck, false)) {
		// Fallback: Projekt-data (exe in bin/xxx.app/Contents/MacOS -> ../../../../ = Projekt)
		std::string altPath = ofFilePath::join(ofFilePath::getCurrentExeDir(), "../../../../data");
		if (ofFile::doesFileExist(ofFilePath::join(altPath, "verdana.ttf"), false)) {
			dataPath = altPath;
		}
	}
	ofSetDataPathRoot(ofFilePath::addTrailingSlash(dataPath));
#endif

	// Hauptfenster: 16:9, großzügige Standardgröße
	ofGLFWWindowSettings settings;
	settings.width = 1536;
	settings.height = 864;
	settings.setPosition(ofVec2f(100, 50));
	settings.resizable = true;


	shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);

	// Control-UI: größer lesbar (ursprünglich 400x500 für Windows)
	settings.width = 520;
	settings.height = 680;
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
