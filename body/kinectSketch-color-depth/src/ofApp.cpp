#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    kinect01.init();
    kinect01.open();
    
    threshold.allocate(kinect01.getWidth(), kinect01.getHeight(), OF_IMAGE_COLOR_ALPHA);
    ofSetBackgroundColor(0);
    
    ofSetBackgroundAuto(false);
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect01.update();
    
    float time = ofGetElapsedTimef();
    
    if (kinect01.isFrameNew()){
        for (int i = 0; i < kinect01.getWidth(); i++){
            for (int j = 0; j < kinect01.getHeight(); j++){
                float distance = kinect01.getDistanceAt(i, j);
                if(distance > 60 && distance < 1218) {
                    float r = ofMap(sin(time * 4 * .1), -1, 1, 0, 200) + distance * mouseX * .1;
                    float g = ofMap(sin(time * 4 * .2), -1, 1, 0, 200) + distance * mouseX * .1;
                    float b = ofMap(sin(time * 4 * .3), -1, 1, 0, 200) + distance * mouseX * .1;
                    threshold.setColor(i, j, ofColor(r, g, b));
                }
                else  {
                    threshold.setColor(i, j, ofColor(0, 0, 0, 0));
                }
            }
        }
    }
    threshold.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    float time = ofGetElapsedTimef();
    
    ofSetColor(255, 255, 255);
    threshold.draw(0, 0, ofGetWidth(), ofGetHeight());
    
    ofSetColor(255, 255, 255);
    ofImage image;
    image.grabScreen(0,0,ofGetWidth(),ofGetHeight());
    
    ofPushMatrix();
    float offset = ofMap(sin(time * .01), -1, 1, 4, 10);
    image.draw(-offset, -offset, ofGetWidth() + offset*2, ofGetHeight() + offset*2);
    ofPopMatrix();
}

void ofApp::exit(){
    kinect01.setCameraTiltAngle(0);
    kinect01.close();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case OF_KEY_UP:
            angle++;
            if(angle > 30) angle = 30;
            kinect01.setCameraTiltAngle(angle);
            break;
            
        case OF_KEY_DOWN:
            angle--;
            if(angle < -30) angle = -30;
            kinect01.setCameraTiltAngle(angle);
            break;
            
        default:
            break;
    }

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
//    cout << mouseX << endl;
//    cout << mouseY << endl;
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
