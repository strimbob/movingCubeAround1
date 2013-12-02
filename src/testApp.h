#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    ofMesh makeTorusZ(float diameter,float fatness,float rotationSpeed);
    ofMesh makeTorusY(float diameter,float fatness,float rotationSpeed);
    ofMesh makeTorusX(float diameter,float fatness,float rotationSpeed);
//    ofMesh makeTorusX(float diameter,float fatness , float res,ofVec3f rotation );
    bool    inside(float _x, float _y,float _radius,float lineWidth  );
    void findCursor();
    ofBoxPrimitive camera;
    ofEasyCam cam;
    ofVec3f xyz;
    bool highlight;
    
    
private:
  bool  move;
  bool  rotation;
  bool  scale;
    ofQuaternion cameraRot;
    ofQuaternion startQuat;
    float angle;
    float sine;
    float cosine;
    float tangent;
    float rotationSpeed;
    ofPoint point;
    ofPoint center;
    int radius;

    float oldAngle;
    
    bool highlightZ;
    bool highLightY;
    bool highLightX;
    float zDepth;
    ofVec3f mouseP;
    ofMesh meshZ;
    ofMesh meshY;
    ofMesh meshX;
    bool mouseEvent;
    void selectMesh(ofMesh mesh,bool &highLight,bool &tempHigh);
    bool tempHigh ;
    
    ofEasyCam posCam;
    
    ofRectangle posRect;
    ofRectangle camRect;
    void drawScreen();
    bool moveCam;
};
