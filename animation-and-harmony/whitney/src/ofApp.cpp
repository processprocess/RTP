#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    width = ofGetWidth();
    height = ofGetHeight();
    
    gui.setup();
    gui.add(bgOpacity.setup("bgOpacity", 10, 0, 255));
    gui.add(numEls.setup("numEls", 6, 1, 60));
    gui.add(radius.setup("radius", 7, 2, 100));
    gui.add(colorScale.setup("colorScale", .01, .01, 1));
    gui.add(frequency.setup("frequency", 1.1, 0, 10));
    gui.add(amplitude.setup("amplitude", 122, 0, 255));
    gui.add(phase.setup("phase", .75, 0, 1));
    gui.add(distnc.setup("distnc", 14, 0, width / 5));
    showGUI = true;
    
    ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
int ofApp::easeInQuad(int t){
    return t * t;
}
    
//--------------------------------------------------------------    
void ofApp::draw(){
    float time = ofGetElapsedTimef();
    
    ofSetColor(0, 0, 0, bgOpacity);
    ofDrawRectangle(0, 0, width, height);
    
    ofPushView();
    ofTranslate(width / 2, height / 2);
    
    float angleSlice = 360 / numEls;
    
    float x = ofMap(sin(time * frequency), -1, 1, -amplitude, amplitude);
    float y = ofMap(sin(time * frequency * .5), -1, 1, -amplitude, amplitude);
    
    for (int i = 0; i < numEls; i++) {
        ofRotateDeg(angleSlice);
        ofPushView();
        ofTranslate(0, distnc);
        ofSetColor(0, 0, 255);
        ofTranslate(0, ofMap(sin(time),-1, 1,-amplitude * phase, amplitude * phase));
        ofDrawCircle(x, y, radius);
        for(int v = 0; v < 20; v++) {
            ofTranslate(0, v * radius);
            ofRotateDeg(angleSlice);
            ofDrawCircle(x, y, radius);
        }
        ofPopView();
    }

    ofPopView();

    if(showGUI) {
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'x'){
        img.grabScreen(0, 0 , ofGetWidth(), ofGetHeight());
        img.save("screenshot.png");
    }
    if(key == 'g'){
        showGUI = !showGUI;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
