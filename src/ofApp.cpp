#include "ofApp.h"
#include "luvSC.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	
	ofxEditor::loadFont("fonts/iosevka-bold.ttf", 150);
	editor.setup(this);

	editor.resize(ofGetWidth(), ofGetHeight()-ofxEditor::getCharHeight());

	editor.setAutoFocus(true);
	editor.setLineWrapping(false);
	editor.setFlashEvalSelection(true);

	editor.getSettings().setCursorColor(ofColor(251,73,52));
	editor.getSettings().setTextColor(ofColor(235,219,178));
	editor.getSettings().setSelectionColor(ofColor(251,73,52,200));
	editor.getSettings().setFlashColor(ofColor(251,73,52));
	editor.getSettings().setTextShadowColor(ofColor(0, 0, 0, 0));
	
	sclang.init();

	ofToggleFullscreen();
	ofBackground(ofColor::fromHex(COLOR_BG));
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	ofSetColor(ofColor(0, 0, 0, 75));
	editor.drawString(ofToString(sclang.result), 0, ofGetWidth()/5);	

	editor.draw();
	
	if(!editor.isHidden() && editor.getCurrentEditor() > 0) {
	
		int bottom = ofGetHeight()-ofxEditor::getCharHeight();
		int right = ofGetWidth()-ofxEditor::getCharWidth()*7;
		
		ofSetColor(ofColor(235,219,178));
		editor.drawString(ofToString(editor.getCurrentLine()+1)+","+
		                  ofToString(editor.getCurrentLinePos()),
		                  right, bottom);				
																								
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	bool modifier = ofGetKeyPressed(ofxEditor::getSuperAsModifier() ? OF_KEY_SUPER : OF_KEY_CONTROL);
	if(modifier) {
		switch(key) {
			case 'f': case 6:
				ofToggleFullscreen();
				return;
			case 'l': case 12:
				editor.setLineWrapping(!editor.getLineWrapping());
				return;
			case 'n': case 14:
				editor.setLineNumbers(!editor.getLineNumbers());
				return;
			case 'k': case 26:
				editor.setAutoFocus(!editor.getAutoFocus());
				return;
		}
	}
	editor.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
	editor.resize(w, h-ofxEditor::getCharHeight());
}

//--------------------------------------------------------------
void ofApp::openFileEvent(int &whichEditor) {
	//ofLogNotice() << "received open event for editor " << whichEditor
	//	<< " with filename " << editor.getEditorFilename(whichEditor);
}

//--------------------------------------------------------------
void ofApp::saveFileEvent(int &whichEditor) {
	//ofLogNotice() << "received save event for editor " << whichEditor
	//	<< " with filename " << editor.getEditorFilename(whichEditor);
}

//--------------------------------------------------------------
void ofApp::executeScriptEvent(int &whichEditor) {
	string txt = editor.getText(whichEditor);
	sclang.result = "";
	sclang.evaluate(txt);
}

//--------------------------------------------------------------
void ofApp::evalReplEvent(const string &text) {
}
