#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        int easeInQuad(int t);

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
    
        int width;
        int height;
        string appname;
    
        float tick;
    
        bool showGUI;
        bool saveSVG;
    
        ofxIntSlider margin;
        ofxIntSlider numRows;
        ofxIntSlider elGutter;
        ofxFloatSlider maxRand;
        ofxIntSlider numEls;
        ofxFloatSlider maxDrift;
        ofxFloatSlider noiseZoom;
        ofxPanel gui;
    
        ofImage img;
		
};
