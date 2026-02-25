#include "ofApp.h"

//Written by David Rittershaus (david.rittershaus@gmail.com) for WLB Esslingen

namespace {
	float unit_interval_;
	ofxSegmentDisplay::UnitArray::Align align_;
	ofVec2f pos_;
	float number_;
	ofColor color_;
	ofColor blank_color_;
	bool is_combine_dot = true;
	bool all_char = true;
}
//--------------------------------------------------------------
void ofApp::setup() {

	//ofSetDataPathRoot("../Resources/data/");

	ofSetFrameRate(60);

	// 16:9 Auflösung für Scoreboard-Render (ursprünglich 1366x748)
	const int fboW = 1920;
	const int fboH = 1080;
	float scale = (float)fboH / 748.0f;
	fbo.allocate(fboW, fboH);
	pointilize.setup(fboW, fboH);


	sucessTimer1 = ofGetElapsedTimeMillis();
	sucessTimer2 = ofGetElapsedTimeMillis();

	pointilize.setRenderType(1);
	pointilize.setDynamicSizeMode(1);
	pointilize.setScaleMode(0);
	pointilize.setBorderSize(0.1);
	pointilize.setRadius(0.56);


	ofTrueTypeFont::setGlobalDpi(72);

	titles.load("verdana.ttf", (int)(170 * scale), true, true);
	titles.setLineHeight(34.0f * scale);
	titles.setLetterSpacing(1.035);


	ofxSegmentDisplay::Unit::Style& style = display_.getUnitStyleRef();

	style.width = 115 * scale;
	style.height = 320 * scale;
	style.padding = ofVec2f(14.2857f * scale, 57.1429f * scale);
	style.segment_margin = 0;
	style.segment_width = 13.9f * scale;
	
	(int&)align_ = 0;
	(int&)style.type = 0;
	unit_interval_ = 160 * scale;
	all_char = true;
	number_ = 49.5;
	color_ = ofColor(255, 0, 0);
	blank_color_ = ofColor(22, 22, 22);
	style.skew = 0;

	style.updated = true;

	yearsActive = false;

}

//--------------------------------------------------------------

void ofApp::setupGui() {

	// Control-UI Elemente vergrößern (Standard: 200×18 ist winzig)
	ofxGuiSetDefaultWidth(320);
	ofxGuiSetDefaultHeight(28);
	ofxGuiSetTextPadding(8);
	ofxGuiSetFont("verdana.ttf", 16, true, true);

	parameters.setName("Scoreboard Steuerung");
	parameters.add(fullscr.set("Vollbild", false));
	parameters.add(homeplayers.set("Heim", 0, 0, 99));
	parameters.add(guestplayers.set("Gast", 0, 0, 99));
	parameters.add(flickr.set("Flackern", false));
	parameters.add(flickr2.set("Flackern inteniv", false));
	parameters.add(randomize1.set("Chaos1", false));
	parameters.add(randomize2.set("Chaos2", false));
	parameters.add(randomize3.set("Chaos3 - schneller", false));
	parameters.add(freezeTime.set("Zeit einfrieren", false));
	parameters.add(pause.set("Chaos einfrieren", false));
	parameters.add(yearsOnOff.set("Jahreszahlen ON/OFF", false));
	parameters.add(yearOne.set("1848", false));
	parameters.add(yearTwo.set("1871", false));
	parameters.add(yearThree.set("1933", false));
	parameters.add(yearFour.set("1945", false));
	parameters.add(yearFive.set("1954", false));
	parameters.add(yearSix.set("1961", false));
	parameters.add(yearSeven.set("1989", false));
	parameters.add(yearEight.set("2006", false)); 
	parameters.add(yearNine.set("2017", false));

	freezeTime.addListener(this, &ofApp::frozenTime);
	yearsOnOff.addListener(this, &ofApp::jahreszahlen);
	yearOne.addListener(this, &ofApp::jahreszahlen);
	yearTwo.addListener(this, &ofApp::jahreszahlen);
	yearThree.addListener(this, &ofApp::jahreszahlen);
	yearFour.addListener(this, &ofApp::jahreszahlen);
	yearFive.addListener(this, &ofApp::jahreszahlen);
	yearSix.addListener(this, &ofApp::jahreszahlen);
	yearSeven.addListener(this, &ofApp::jahreszahlen);
	yearEight.addListener(this, &ofApp::jahreszahlen);
	yearNine.addListener(this, &ofApp::jahreszahlen);


	gui.setup(parameters);


}

//--------------------------------------------------------------

void ofApp::update() {
	display_.setUnitInterval(unit_interval_);
	display_.setAlign(align_);

	pointilize.update();

	actualTime = ofGetElapsedTimeMillis();

	if (!pause) {
		if (flickr) {
			ofApp::flickering(180);

		}

		if (flickr2) {
			ofApp::flickering(100);

		}

		if (!flickr && !flickr2) {
			color_ = ofColor(255, 0, 0, 255);

		}

		if (!yearsOnOff) {
			if (randomize1) {

				ofApp::randomCharsHome();

			}

			else {
				home = ofToString(homeplayers);
			}

			if (randomize2) {
				ofApp::randomCharsGuest();
			}

			else {
				guest = ofToString(guestplayers);
			}
		}
	}

	if (pause) {
		color_ = ofColor(255, 0, 0, 255);
	}

	if (freezeTime) {

		std = hours;
		min = minutes;

	}

	else {
		std = ofGetTimestampString("%H");
		min = ofGetTimestampString("%M");
	

	}

	if (fullscr) {
		ofHideCursor();
		ofSetFullscreen(true);
	}
	else {
		ofShowCursor();
		ofSetWindowShape(1536, 864);
		ofSetFullscreen(false);

	}


}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackground(0);

	float line_width = display_.getUnitStyleRef().width;
	float line_padding = display_.getUnitStyleRef().padding.x;

	fbo.begin();

	ofClear(0);

	// FBO-Größe verwenden (nicht Fenstergröße) für korrektes Layout
	float w = fbo.getWidth();
	float h = fbo.getHeight();
	ofPushMatrix();
	ofTranslate(w / 2 - ((line_width - line_padding) * 4), -16);
	display_.draw((std + "-" + min), color_, blank_color_);
	ofPopMatrix();
	ofPushMatrix();
	ofTranslate(w / 4 - ((line_width - line_padding)*1.5), h / 2 + 33);
	display_.draw(ofToString(home, 2, 0), color_, blank_color_);
	ofTranslate(w / 2, 0);
	display_.draw(ofToString(guest, 2, 0), color_, blank_color_);
	ofPopMatrix();

	fbo.end();


	pointilize.loadTexture(fbo.getTexture());
	pointilize.draw(0, 0);

	
	/*

	Schrift HEIM, GAST durch Holzblende ersetzt
	
	ofPushMatrix();
	ofTranslate(ofGetScreenWidth() / 4 - ((line_width - line_padding) * 2), ofGetScreenHeight() / 1.6);
	titles.drawString("HEIM", -(line_width + line_padding) / 2, -30);
	ofTranslate(ofGetScreenWidth() / 2, 0);
	titles.drawString("GAST", -(line_width + line_padding) / 2, -30);
	ofPopMatrix();
	*/
}

//--------------------------------------------------------------

void ofApp::drawGui(ofEventArgs & args) {

	gui.draw();

}

//--------------------------------------------------------------
void ofApp::flickering(int intens) {

	flick = ofMap(ofNoise(ofGetElapsedTimef() * 10), 0, 1, intens, 255);
	color_ = ofColor(255, 0, 0, flick);
}

//--------------------------------------------------------------

void ofApp::randomCharsHome() {

	if (randomize3) {
		sucessTimeDelta1 = ofRandom(50, 800);
	}
	else {
		sucessTimeDelta1 = ofRandom(900, 2500);
	}

	if (actualTime - sucessTimer1 > sucessTimeDelta1) {
		char ch1 = 'A';
		char ch2 = 'G';
		ch1 = 'A' + rand() % 70;
		ch2 = 'G' + rand() % 50;
		home = ofToString(ch1) + ofToString(ch2);
		sucessTimer1 = ofGetElapsedTimeMillis();
	}

}

//--------------------------------------------------------------
void ofApp::randomCharsGuest() {

	if (randomize3) {
		sucessTimeDelta2 = ofRandom(50, 800);
	}
	else {
		sucessTimeDelta2 = ofRandom(900, 2500);
	}

	if (actualTime - sucessTimer2 > sucessTimeDelta2) {
		char ch1 = 'A';
		char ch2 = 'G';
		ch1 = 'C' + rand() % 70;
		ch2 = 'J' + rand() % 50;
		guest = ofToString(ch1) + ofToString(ch2);
		sucessTimer2 = ofGetElapsedTimeMillis();
	}

}

//--------------------------------------------------------------

void ofApp::frozenTime(bool & e) {

	if (e) {

		hours = ofGetTimestampString("%H");
		minutes = ofGetTimestampString("%M");

	}

}

void ofApp::jahreszahlen(bool & e) {
	
	if (yearsOnOff) {
		yearsActive = true;

		if (yearNine) {
			home = "20";
			guest = "17";
		}

		else if (yearEight) {
			home = "20";
			guest = "06";
		}

		else if (yearSeven) {
			home = "19";
			guest = "89";
		}

		else if (yearSix) {
			home = "19";
			guest = "61";
		}

		else if (yearFive) {
			home = "19";
			guest = "54";
		}
		else if (yearFour) {
			home = "19";
			guest = "45";
		}
		else if (yearThree) {
			home = "19";
			guest = "33";
		}
		else if (yearTwo) {
			home = "18";
			guest = "71";
		}
		else if (yearOne) {
			home = "18";
			guest = "48";
		}
		else {
			guest = ofToString(guestplayers);
			home = ofToString(homeplayers);
		}
	}

		else {
			yearsActive = false;
			guest = ofToString(guestplayers);
			home = ofToString(homeplayers);
		}
	

}

void ofApp::keyPressed(int key) {

}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {


}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
