#pragma once

#include "ofMain.h"
#include "ofxGui.h"

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
    
        vector < ofPath > deformPaths(vector < ofPath > paths, int deformAmount);
        ofPolyline deformPolyLine(ofPolyline line, int deformAmount);
    
        bool haveNextNextGaussian = false;
        float nextNextGaussian;
        float ofxGaussian();
        
        int width;
        int height;
    
        float time;
    
        bool showGUI;
        ofxIntSlider bgOpacity;
        ofxIntSlider startingDeform;
        ofxIntSlider deformPasses;
        ofxIntSlider resampledSpacing;
        ofxIntSlider deformAmountPerPass;
        ofxPanel gui;
    
        vector < ofPath > paths;
    
        ofImage img;
        ofImage oldImg;
    
        ofTrueTypeFont font;
        ofEasyCam cam;
		
};
