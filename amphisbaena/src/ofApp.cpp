#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //Setup Spacebreww connection and subscribers
    string host = "spacebrew.icts.sbg.ac.at";
    string name = "of-Seat";
    string description = "Generates parameters for servos";
    spacebrew.addSubscribe("carHeading", "String");
    spacebrew.addSubscribe("carPositionX", "String");
    spacebrew.addSubscribe("carPositionY", "String");
    spacebrew.addSubscribe("carPositionZ", "String");
    spacebrew.addSubscribe("trafficHeading", "String");
    spacebrew.addSubscribe("trafficPositionX", "String");
    spacebrew.addSubscribe("trafficPositionY", "String");
    spacebrew.addSubscribe("trafficPositionZ", "String");
    
    //    ofSetLogLevel(OF_LOG_VERBOSE);
    spacebrew.connect( host, 9000, name, description );
    
    Spacebrew::addListener(this, spacebrew);
    
    ofSetVerticalSync(true);
    ofBackground(20, 70, 60);
    ofEnableSmoothing();
    ofEnableDepthTest();
    
    // user + seat camera
    camEasyCam.setDistance(20);
    camEasyCam.setFarClip(200);
    camEasyCam.setNearClip(0);
    viewMain.x = 0;
    viewMain.y = 0;
    viewMain.width = ofGetWidth();
    viewMain.height = ofGetHeight();
    
    viewSeat.x = 0;
    viewSeat.y = 0;
    viewSeat.width = ofGetWidth()/4;
    viewSeat.height = ofGetHeight()/4;


//    camSeat.scale = 20;
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    camEasyCam.begin(viewMain);
    //--
    // Draw Traffic
    ofPushStyle();
    light.enable();
    //	light.setPosition(particles[0].position);
    
    ofSetColor(255,0,0);
    
    for (int i = 0; i < traffic.size(); i++) {
        
        ofPushMatrix();
        ofRotateY(driver.heading - traffic[i].heading);
        ofTranslate(driver.position - traffic[i].position);
        ofDrawBox(0,0,0, 1.5,1.1,3);
        ofPopMatrix();
    }
    light.disable();
    ofDisableLighting();
    
    //
    //--
    
    ofPopStyle();
    camEasyCam.end();
}


void ofApp::onMessage( Spacebrew::Message & msg ){
    
    if ( msg.name.find("traffic") == 0){
        vector<float> values;
        float value;
        stringstream input(msg.value);
        while (input >> value) {
            values.push_back(value);
            if (input.peek() == ',') input.ignore();
        }
        
        while (traffic.size() < values.size()) {
            vehicle car;
            car.heading = 0;
            car.position.set(0,0,0);
            traffic.push_back(car);
        }
        
        if (msg.name == "trafficHeading") {
            for (int i = 0; i < values.size(); i++) {
                traffic[i].heading = ofToFloat(msg.value);
            }
        }
        else if (msg.name == "trafficPositionX") {
            for (int i = 0; i < values.size(); i++) {
                traffic[i].position.x = ofToFloat(msg.value);
            }
        }
        else if (msg.name == "trafficPositionY") {
            for (int i = 0; i < values.size(); i++) {
                traffic[i].position.y = ofToFloat(msg.value);
            }
        }
        else if (msg.name == "trafficPositionZ") {
            for (int i = 0; i < values.size(); i++) {
                traffic[i].position.z = ofToFloat(msg.value);
            }
        }
        
    }
    else {
        if (msg.name == "carHeading") {
            driver.heading = ofToFloat(msg.value);
        }
        else if (msg.name == "carPositionX") {
            driver.position.x = ofToFloat(msg.value);
        }
        else if (msg.name == "carPositionY") {
            driver.position.y = ofToFloat(msg.value);
        }
        else if (msg.name == "carPositionZ") {
            driver.position.z = ofToFloat(msg.value);
        }
    }
    
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
