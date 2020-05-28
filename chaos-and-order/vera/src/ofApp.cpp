#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    width = ofGetWidth();
    height = ofGetHeight();
    
    gui.setup();
    gui.add(margin.setup("margin", 200, 10, 200));
    gui.add(numRows.setup("numRows", 6, 2, 100));
    gui.add(elGutter.setup("elGutter", 24, 0, 40));
    gui.add(maxRand.setup("maxRand", .08, 0, 1));
    gui.add(numEls.setup("numEls", 21, 1, 60));
    gui.add(maxDrift.setup("maxDrift", .33, 0, 1));
    showGUI = true;
    
    saveSVG = false;
    
    ofBackground(255, 255, 255);
    
    colors = new ofColor[3];
    colors[0] = ofColor(181, 98, 48);
    colors[1] = ofColor(75,100,150);
    colors[2] = ofColor(150,93,145);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSeedRandom(0);
}

//--------------------------------------------------------------
float ofApp::easeInQuad(float t){
    return t * t;
}
    
//--------------------------------------------------------------
void ofApp::draw(){
    
//    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    if(saveSVG) {
        ofBeginSaveScreenAsSVG("screenshot.svg");
    }
    
    float elSize = (width - margin * 2) / numRows;
    float halfGutter = elGutter / 2;
    
    for(int x = 0; x < numRows; x++) {
        for(int y = 0; y < numRows; y++) {

            float posX = ofMap(x, 0, numRows, margin, width - margin);
            float posY = ofMap(y, 0, numRows, margin, height - margin);
            float rand = easeInQuad(ofNormalize(x, 0, numRows) * (maxRand * elSize));

            ofSetColor(colors[(int)ofRandom(0,3)]);

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
