#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    tab_1.setup("Tab_1");
    tab_2.setup("Tab_2");
    tab_3.setup("Tab_3");
    
    menu.setup(0,0,300, 40, 5);
    menu.add(tab_1);
    menu.add(tab_2);
    menu.add(tab_3);
    
    pro_1.setup("pro_1");
    pro_2.setup("pro_2");
    pro_3.setup("pro_3");
    
    projectors.setup(0,40, 100, 200, 5, true);
    projectors.add(pro_1);
    projectors.add(pro_2);
    projectors.add(pro_3);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(50);
    menu.draw();
    
    if(tab_1.isActive()) projectors.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
