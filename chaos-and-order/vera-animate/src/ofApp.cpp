#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    width = ofGetWidth();
    height = ofGetHeight();
    
    gui.setup();
    gui.add(margin.setup("margin", 130, 10, 200));
    gui.add(numRows.setup("numRows", 35, 2, 100));
    gui.add(elGutter.setup("elGutter", 13, 0, 40));
    gui.add(maxRand.setup("maxRand", .33, 0, 1));
    gui.add(numEls.setup("numEls", 1, 1, 60));
    gui.add(maxDrift.setup("maxDrift", .33, 0, 1));
    gui.add(noiseZoom.setup("noiseZoom", .1, 0.001, 1));
    showGUI = true;
    
    ofBackground(0, 0, 0);
    
    tick = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSeedRandom(0);
    tick += .1;
}
    
//--------------------------------------------------------------
void ofApp::draw(){
    
    float elSize = (width - margin * 2) / numRows;
    float halfGutter = elGutter / 2;
    
    ofSetColor(ofColor(255,255,255));
    
    if(saveSVG) {
        ofBeginSaveScreenAsSVG("screenshot.svg");
    }
    
    for(int x = 0; x < numRows; x++) {
        for(int y = 0; y < numRows; y++) {

            float posX = ofMap(x, 0, numRows, margin, width - margin);
            float posY = ofMap(y, 0, numRows, margin, height - margin);
            float randT = ofNormalize(x, 0, numRows) * (maxRand * elSize);
            float rand = randT * randT * (ofNoise((x + tick) * noiseZoom, (y + tick) * noiseZoom));

            for(int s = 0; s <= numEls; s++) {
                float t = ofNormalize(s, 0, numEls) * ofNormalize(s, 0, numEls);
                float drift = ofNormalize(t * x, 0, numRows) * (maxDrift * elSize);
                
                ofNoFill();
                ofPushMatrix();
                ofTranslate(drift, 0);
                ofBeginShape();
                ofVertex(ofRandom(-rand, rand) + posX + halfGutter, ofRandom(-rand, rand) + posY + halfGutter);
                ofVertex(ofRandom(-rand, rand) + posX + elSize - halfGutter, ofRandom(-rand, rand) + posY + halfGutter);
                ofVertex(ofRandom(-rand, rand) + posX + elSize - halfGutter, ofRandom(-rand, rand) + posY + elSize - halfGutter);
                ofVertex(ofRandom(-rand, rand) + posX + halfGutter, ofRandom(-rand, rand) + posY + elSize - halfGutter);
                ofEndShape(true);
                ofPopMatrix();
            }
        }
    }

    if(saveSVG) {
        ofEndSaveScreenAsSVG();
        saveSVG = false;
    }
    
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
    if(key == 's'){
        saveSVG = true;
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
