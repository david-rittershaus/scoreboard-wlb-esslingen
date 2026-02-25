#pragma once

#include "ofMain.h"
#include "ofxSegmentDisplay.h"
#include "ofxGui.h"
#include "ofxPointilize.h"



class ofApp : public ofBaseApp {

public:
	void setup();
	void setupGui();
	void update();
	void draw();
	void drawGui(ofEventArgs & args);
	void flickering(int intens);
	void randomCharsHome();
	void randomCharsGuest();
	void frozenTime(bool & e);
	void jahreszahlen(bool & e);

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);



	ofxSegmentDisplay::UnitArray display_;



	ofParameterGroup parameters;
	ofParameter<int> homeplayers;
	ofParameter<int> guestplayers;
	ofParameter<bool> fullscr;
	ofParameter<bool> flickr;
	ofParameter<bool> flickr2;
	ofParameter<bool> randomize1;
	ofParameter<bool> randomize2;
	ofParameter<bool> randomize3;
	ofParameter<bool> freezeTime;
	ofParameter<bool> pause;


	ofParameter<bool> yearsOnOff;
	ofParameter<bool> yearOne;
	ofParameter<bool> yearTwo;
	ofParameter<bool> yearThree;
	ofParameter<bool> yearFour;
	ofParameter<bool> yearFive;
	ofParameter<bool> yearSix;
	ofParameter<bool> yearSeven;
	ofParameter<bool> yearEight;
	ofParameter<bool> yearNine;
	ofxPanel gui;

	ofTrueTypeFont	titles;

	ofFbo fbo;

	ofxPointilize pointilize;

	float flick;
	string home;
	string guest;
	bool interrupt;
	string hours;
	string minutes;
	string std;
	string min;
	bool yearsActive;

	unsigned long actualTime, sucessTimer1, sucessTimer2;
	unsigned int sucessTimeDelta1, sucessTimeDelta2;


};
