#pragma once

#include "ofMain.h"
#include "ofxSelectableObjects.hpp"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    ofxSelectableObjects menu;
    SelectableObjectBase tab_1;
    SelectableObjectBase tab_2;
    SelectableObjectBase tab_3;
    
    ofxSelectableObjects projectors;
    SelectableObjectBase pro_1;
    SelectableObjectBase pro_2;
    SelectableObjectBase pro_3;
		
};
