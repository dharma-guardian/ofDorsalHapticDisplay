#pragma once

#include "ofMain.h"
#include "ofxSpacebrew.h"

class ofApp : public ofBaseApp{

public:
        struct vehicle {
            ofVec3f position;
            float heading;
        };
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void drawScene(bool);
    
        Spacebrew::Connection spacebrew;
        void onMessage( Spacebrew::Message & msg );
    
        //Cameras
        ofEasyCam camEasyCam;
        ofCamera camSeat;
    
        //Viewports
        ofRectangle viewMain;
        ofRectangle viewSeat;
    
        //FBO for readinf out values
        ofFbo scene;
    
        ofLight light;
        vehicle driver;
        vector<vehicle> traffic;
		
};
