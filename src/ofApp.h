#pragma once

#include "ofMain.h"
#include "ofxGLEditor.h"
#include "luvSC.h"

#define COLOR_BG 		 0x282828
#define COLOR_YELLOW 0xfabd2f

class ofApp : public ofBaseApp, public ofxGLEditorListener {

	public:
		void setup();
		void draw();

		void keyPressed(int key);
		void windowResized(int w, int h);
	
		void saveFileEvent(int &whichEditor);
		void openFileEvent(int &whichEditor);
		void executeScriptEvent(int &whichEditor);
		void evalReplEvent(const string &text);
		void setColorScheme();
		
		ofxGLEditor editor;
		ofxEditorColorScheme colorScheme;
		ofxEditorSyntax supercolliderSyntax;
		
		luvSC sclang;
		string currentPath;
};
