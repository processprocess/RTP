#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    width = ofGetWidth();
    height = ofGetHeight();
    
    gui.setup();
//    gui.add(bgOpacity.setup("bgOpacity", 10, 0, 255));
    gui.add(startingDeform.setup("startingDeform", 2, 0, 20));
    gui.add(deformPasses.setup("deformPasses", 88, 0, 120));
    gui.add(resampledSpacing.setup("resampledSpacing", 10, 0, 50));
    gui.add(deformAmountPerPass.setup("deformAmountPerPass", 13, 0, 50));
    showGUI = true;
    
    font.load("framd.ttf", 270, true, true, true);
    
    ofBackground(255, 255, 255);
//    ofSetBackgroundAuto(false);
    
    haveNextNextGaussian = false;
    nextNextGaussian;
    
    paths = font.getStringAsPoints("5");
    
//    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
}

//--------------------------------------------------------------
void ofApp::update(){
    time = ofGetElapsedTimef();
}

float ofApp::ofxGaussian() {
    if (haveNextNextGaussian){
       haveNextNextGaussian = false;
       return nextNextGaussian;
    }
    else {
       float v1, v2, s;
       do {
           v1 = 2 * ofRandomf() - 1;
           v2 = 2 * ofRandomf() - 1;
           s = v1 * v1 + v2 * v2;
       }
       while (s >= 1 || s == 0);

       float multiplier = sqrt(-2 * log(s)/s);
       nextNextGaussian = v2 * multiplier;
       haveNextNextGaussian = true;

       return v1 * multiplier;
    }
}

ofPolyline ofApp::deformPolyLine(ofPolyline line, int deformAmount) {
    
    for (int k = 0; k < line.size(); k++){
        line[k].x += ofxGaussian() * deformAmount;
        line[k].y += ofxGaussian() * deformAmount;
    }
    return line;
}

vector < ofPath > ofApp::deformPaths(vector < ofPath > paths, int deformAmount) {
    vector < ofPath > newPaths = paths;
    
    for (int i = 0; i < newPaths.size(); i++) {
        ofPath newPath;

        newPaths[i].setPolyWindingMode(OF_POLY_WINDING_ODD);
        vector < ofPolyline > lines = newPaths[i].getOutline();

        for (int j = 0; j < lines.size(); j++){
            lines[j].setClosed(true);
            lines[j] = lines[j].getResampledBySpacing(resampledSpacing);
            lines[j] = deformPolyLine(lines[j], deformAmount);

            if (j!=0) newPath.newSubPath();
            for (int k = 0; k < lines[j].size(); k++){
                if (k == 0) newPath.moveTo(lines[j][k]);
                else newPath.lineTo(lines[j][k]);
            }
            newPath.setFilled(true);
            newPath.close();
        }
        newPaths[i] = newPath;
    }
    
    return newPaths;
}

//--------------------------------------------------------------    
void ofApp::draw() {
    ofSeedRandom(0);
    int spacing = 100;
    
    vector < ofPath > deformedPaths = deformPaths(paths, startingDeform);
    
    ofPushMatrix();
    
    ofColor redAlpha(255, 0, 0, 10);
    ofColor yellowAlpha(255, 255, 0, 10);
    ofColor blueAlpha(0, 0, 255, 10);
    
    ofTranslate(70, height / 2 + 120);
    for (int i = 0; i < deformPasses; i++) {
        vector < ofPath > newPaths = deformPaths(deformedPaths, deformAmountPerPass);
        for (int j = 0; j < newPaths.size(); j++){
            newPaths[j].setColor(redAlpha);
            newPaths[j].draw();
        }
    }
    
    ofTranslate(spacing, 0);
    for (int i = 0; i < deformPasses; i++) {
        vector < ofPath > newPaths = deformPaths(deformedPaths, deformAmountPerPass * 1.2);
        for (int j = 0; j < newPaths.size(); j++){
            newPaths[j].setColor(yellowAlpha);
            newPaths[j].draw();
        }
    }
    
    ofTranslate(spacing, 0);
    for (int i = 0; i < deformPasses; i++) {
        vector < ofPath > newPaths = deformPaths(deformedPaths, deformAmountPerPass * 1.4);
        for (int j = 0; j < newPaths.size(); j++){
            newPaths[j].setColor(blueAlpha);
            newPaths[j].draw();
        }
    }
    
    ofTranslate(spacing, 0);
    for (int i = 0; i < deformPasses; i++) {
        vector < ofPath > newPaths = deformPaths(deformedPaths, deformAmountPerPass * 1.6);
        for (int j = 0; j < newPaths.size(); j++){
            newPaths[j].setColor(redAlpha);
            newPaths[j].draw();
        }
    }
    
    ofTranslate(spacing, 0);
    for (int i = 0; i < deformPasses; i++) {
        vector < ofPath > newPaths = deformPaths(deformedPaths, deformAmountPerPass * 1.8);
        for (int j = 0; j < newPaths.size(); j++){
            newPaths[j].setColor(yellowAlpha);
            newPaths[j].draw();
        }
    }
    
    ofTranslate(spacing, 0);
    for (int i = 0; i < deformPasses; i++) {
        vector < ofPath > newPaths = deformPaths(deformedPaths, deformAmountPerPass * 2.0);
        for (int j = 0; j < newPaths.size(); j++){
            newPaths[j].setColor(blueAlpha);
            newPaths[j].draw();
        }
    }
    
    ofTranslate(spacing, 0);
    for (int i = 0; i < deformPasses; i++) {
        vector < ofPath > newPaths = deformPaths(deformedPaths, deformAmountPerPass * 2.2);
        for (int j = 0; j < newPaths.size(); j++){
            newPaths[j].setColor(redAlpha);
            newPaths[j].draw();
        }
    }
    
    ofPopMatrix();
    
    if(showGUI) {gui.draw();}
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
    //    ofPushMatrix();
    //    ofPopMatrix();
    //    ofDrawRectangle(0, 0, width, height);
    
    //    ofImage image;
    //    image.grabScreen(0,0,width,height);
    //    image.draw(cos(time), sin(time));
    
//    if(showGUI) {gui.draw();}
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
