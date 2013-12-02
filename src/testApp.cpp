#include "testApp.h"
int radius =100;
int x = x;
int y = y;
bool test;
float angleZOld;
//--------------------------------------------------------------
void testApp::setup(){
    camera.set(100, 100, 100, 10, 10, 10);
    ofSetCircleResolution(50);
    angle=0;
	cosine=0;
	sine=0;
	tangent=0;
	rotationSpeed=.1f;
	radius = 100;
    center.set(ofGetWidth()*0.3f, ofGetHeight()*0.6f, 0);
    rotation = true;
    zDepth = 0.965f;
    ofEnableDepthTest();
    
    
    float diameter = 100;
    float res = 0.05;
    float fatness = 8;
    meshZ =  makeTorusZ(diameter,fatness,res);
    

    meshY =  makeTorusY(diameter+10,fatness,res);
    meshX =  makeTorusX(diameter+20,fatness,res);
    ofMesh meshX;
    
    
    posRect.x = 0;
	posRect.y = 0;
	posRect.width = ofGetWidth()/2;
	posRect.height = ofGetHeight();
    
    camRect.x =  ofGetWidth()/2;
	camRect.y = 0;
	camRect.width = ofGetWidth()/2+ofGetWidth();
	camRect.height = ofGetHeight();
    

}

//--------------------------------------------------------------
void testApp::update(){
    
    
    cosine=cos(angle);
	sine=sin(angle);
	tangent=tan(angle);
    
    posCam.setGlobalPosition(camera.getGlobalPosition());
    posCam.setGlobalOrientation(camera.getGlobalOrientation());
    
            point.set(cosine * radius, sine * radius, 0);//here we set the cyan circle
    
}
bool testApp::inside(float _x, float _y,float _radius,float lineWidth ){
    bool online = false;
    online = (ofVec2f(_x, _y).distance(ofVec2f(xyz.x, xyz.y)) <_radius+lineWidth );
    if(online){
        if( ofVec2f(_x, _y).distance(ofVec2f(xyz.x, xyz.y)) <_radius-lineWidth){
            online = false;
        }
        
    }
    return online;
}
//--------------------------------------------------------------
void testApp::draw(){
    
    cam.begin();
    
    if(!highlight){
        cam.enableMouseInput();
        ofSetColor(200, 100, 0);
    }
    else{
        cam.disableMouseInput();
        ofSetColor(100, 200, 10);
    }
   
    if(move){
      cam.disableMouseInput();
    }
    camera.draw();

    ofNoFill();
     //       cam.enableMouseInput();
    if(rotation){
    if(highlightZ){
         cam.disableMouseInput();
        ofSetColor(255, 255, 0);
        ofCircle(point, 10);
        meshZ.draw();
        ofCircle(0, 0, 100);
        
    }
    else{
       // cam.enableMouseInput();
        ofSetColor(255, 0, 0);
                meshZ.draw();
        ofCircle(0, 0, 100);
        
    }
    
    
    if(highLightY){
        cam.disableMouseInput();

        ofCircle(point, 10);
         ofSetColor(255, 255, 0);
        
//        if(test){
//        ofPushMatrix();
//            ofRotateZ(ofRadToDeg(angle));
//            angleZOld = angle;
//        }
//        else{
//            ofPushMatrix();
//            ofRotateZ(ofRadToDeg(angleZOld));
//        }
    meshY.draw();

    
//        ofPopMatrix();
        
    
    }else{
//        if(test){
//            ofPushMatrix();
//            ofRotateZ(ofRadToDeg(angle));
//            angleZOld = angle;
//      //    cam.enableMouseInput();
//        }
//        else{
//            ofPushMatrix();
//            ofRotateZ(ofRadToDeg(angleZOld));
//        }
//        
        ofSetColor(0, 255, 0);
      meshY.draw();
     //   if(test){
   //         ofPopMatrix();
     //   }
    }
    
        if(highLightX){
            cam.disableMouseInput();
 
            ofCircle(point, 10);
               ofSetColor(255, 255, 0);
    meshX.draw();
        }else{
      //        cam.enableMouseInput();
             ofSetColor(0,0, 255);
            meshX.draw();
        }
    }


    ofDrawAxis(20);
    
    
    
    
    ofRect(posCam.getPosition(),20,20);
    ofPushStyle();
    ofPushMatrix();
  // view port
//    ofRectangle boundsToUse;
//    boundsToUse = camRect;
//    ofMatrix4x4 inverseCameraMatrix;
//    inverseCameraMatrix.makeInvertOf(cam.getModelViewProjectionMatrix(boundsToUse));
    
    //
    //ofRectangle boundsToUse;
    //boundsToUse = camRect;
    ofMatrix4x4 inverseCameraMatrix;
    inverseCameraMatrix.makeInvertOf(posCam.getModelViewProjectionMatrix());
    ofMultMatrix( inverseCameraMatrix );
    //ofRect(ofRandom(100),ofRandom(100),ofRandom(100),ofRandom(100),ofRandom(100));
    ofNoFill();
    ofDrawBox(0, 0, 0, 2.0f);
    ofPopStyle();
    ofPopMatrix();
    
       ofRect(100, 300, 300, 300);
    
    cam.end();
    tempHigh = false;
    if(rotation){
    selectMesh(meshX,highLightX,tempHigh);
    selectMesh(meshY,highLightY,tempHigh);
    selectMesh(meshZ,highlightZ,tempHigh);
    }

   // posCam.disableMouseInput();
    posCam.begin();
ofDrawAxis(20);
    ofRect(100, 300, 300, 300);
    
    posCam.end();
    

}

void testApp::selectMesh(ofMesh mesh,bool &highLight, bool &tempHigh){
    
    int n = mesh.getNumVertices();
	float nearestDistance = 0;
	ofVec3f nearestVertex;
	int nearestIndex = 0;
	ofVec3f mouse(mouseX, mouseY,mouseP.z);
	for(int i = 0; i < n; i++) {
		ofVec3f cur = cam.worldToScreen(mesh.getVertex(i));
		float distance = cur.distance(mouse);
		if(i == 0 || distance < nearestDistance) {
            nearestDistance = distance;
            nearestIndex = i;
            nearestVertex = cur;
            if( cur.distance(mouse) < 10){
                if((! mouseEvent)&&(!tempHigh)){
                    highLight = true;
                    tempHigh = true;
                }
            }
            else{
                if(! mouseEvent){
                    highLight = false;
                }
            }
		}
	}
    
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    
    
    move = false;
    rotation = false;
    scale = false;
    
    if(key == 'q'){
        move = true;
    }
    if(key == 'w'){
        rotation = true;
    }
    if(key == 'e'){
        scale = true;
    }
    
    if(key == ' '){

        test = !test;
//        ds.
//        meshZ.
      //  meshZ.
     // meshZ.s=  camera.getOrientationQuat();
    }


}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

void testApp::findCursor() {

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

    
    mouseP.x = ofGetMouseX();
	mouseP.y = ofGetMouseY();
	
  	glReadPixels(mouseP.x, ofGetHeight()-1-mouseP.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &mouseP.z);


    // ofVec2f mousePos= cam.worldToCamera(cam.screenToWorld(ofVec2f(x,y)));
    
    //camera.setGlobalPosition(mousePos);
    
 //   ofVec3f tempMouse = cam.screenToWorld(ofVec3f(x,y,zDepth));

 //   xyz = ;
    
//    cout <<cam.worldToScreen(camera.getPosition()) << " " << tempMouse << endl;
//    if(inside(tempMouse.x, tempMouse.y, 50,5)){
//        highlightZ = true;
//    }else{
//       highlightZ = false;
//    }
    
    
    if (inside(x, y,10,1)) {
        highlight = true;
     //   cout << " got " << endl;
    }else{
         highlight = false;
     //   cout << "not" << endl;
    }
  //  cout << x << " '" << y << " " << xyz << endl;
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
    
//    float dx = (args.x - mouseP.x) / ofGetViewportWidth();
//	float dy = (args.y - mouseP.y) / ofGetViewportHeight();
    /// from grabcam
    
    glReadPixels(mouseP.x, ofGetHeight()-1-mouseP.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &mouseP.z);
    ofVec2f mousePos=cam.worldToCamera(cam.screenToWorld(ofVec3f(x,y,mouseP.z)));
   
    angle = -mousePos.angleRad(ofVec2f(radius,0));
    
    if(highlightZ){
       camera.rotate(ofRadToDeg(angle-oldAngle), ofVec3f( 0,0,1));
       }
    
    if(highLightX){
        camera.rotate(ofRadToDeg(angle-oldAngle), ofVec3f( 0,-1,0));
    }
    if(highLightY){
        camera.rotate(ofRadToDeg(angle-oldAngle), ofVec3f( 1,0,0));
    }
           oldAngle = angle;
    if(move){
        ofVec3f tempPos = cam.screenToWorld(ofVec3f(x,y,0));
       // camera.getGlobalPosition().x+x,
        camera.setGlobalPosition(camera.getGlobalPosition()+cam.worldToCamera(cam.screenToWorld(tempPos)));
     //   camera.setPosition(tempPos);
    }
    if(highlight){
    


        if(rotation){
            

        }
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    glReadPixels(mouseP.x, ofGetHeight()-1-mouseP.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &mouseP.z);
    ofVec2f mousePos= cam.worldToCamera(cam.screenToWorld(ofVec3f(x,y,mouseP.z)));
        angle = -mousePos.angleRad(ofVec2f(radius,0));
    test = false;
    mouseEvent = true;
         oldAngle = angle;
    

//
//    ofVec2f mousePos= cam.screenToWorld(ofVec3f(x,y,xyz.z));
//	//if (mousePos.length()<radius ) {
//    //     cout << "jhg"<< endl;
//    angle = -mousePos.angleRad(ofVec2f(radius,0));
//    cout << angle << endl;
//    
//    
//    cameraRot = camera.getOrientationQuat();
//    float angleA;
//    float xa;
//    float ya;
//    float za;
//    cameraRot.getRotate(angleA, xa,ya,za);
//    
//    startQuat.makeRotate(angle,xa,ya,za);
//    cout << xa << " " << ya << " " << za <<endl;
//    camera.rotate(angle*360, ofVec3f( xa,ya,za));
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    test= true;
    mouseEvent = false;
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 


}


ofMesh testApp::makeTorusZ(float diameter,float fatness , float res){
    ofMesh cir;
    cir.clear();
    cir.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    ofVec3f firstX;
    ofVec3f firstY;
    for(float x=0;x<TWO_PI;x+=res){
        
        cosine=cos(x);
        sine=sin(x);
        tangent=0;
        
        float xOuter = ((diameter+fatness)*cosine);
        float xInter = (diameter*cosine);
        float yOuter = ((diameter+fatness)*sine);
        float yInter = (diameter*sine);
        cir.addVertex(ofVec3f(xOuter,yOuter,tangent));
        cir.addVertex(ofVec3f(xInter,yInter ,tangent));
        if(x == 0){
            firstX =ofVec3f(xOuter,yOuter,tangent);
            firstY = ofVec3f(xInter,yInter ,tangent);
        }
        
    }
    cir.addVertex(firstX);
    cir.addVertex(firstY);
    return cir;
}


ofMesh testApp::makeTorusY(float diameter,float fatness , float res){
    ofMesh cir;
    cir.clear();
    cir.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    ofVec3f firstX;
    ofVec3f firstY;
    for(float x=0;x<TWO_PI;x+=res){
        
        cosine=cos(x);
        sine=sin(x);
        tangent=0;
        
        float xOuter = ((diameter+fatness)*cosine);
        float xInter = (diameter*cosine);
        float yOuter = ((diameter+fatness)*sine);
        float yInter = (diameter*sine);
        cir.addVertex(ofVec3f(tangent,xOuter,yOuter));
        cir.addVertex(ofVec3f(tangent,xInter,yInter ));
        if(x == 0){
            firstX =ofVec3f(tangent,xOuter,yOuter);
            firstY = ofVec3f(tangent,xInter,yInter );
        }
        
    }
    cir.addVertex(firstX);
    cir.addVertex(firstY);
    return cir;
}
ofMesh testApp::makeTorusX(float diameter,float fatness , float res){
    ofMesh cir;
    cir.clear();
    cir.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    ofVec3f firstX;
    ofVec3f firstY;
    for(float x=0;x<TWO_PI;x+=res){
        
        cosine=cos(x);
        sine=sin(x);
        tangent=0;
        
        float xOuter = ((diameter+fatness)*cosine);
        float xInter = (diameter*cosine);
        float yOuter = ((diameter+fatness)*sine);
        float yInter = (diameter*sine);
        cir.addVertex(ofVec3f(yOuter,tangent,xOuter));
        cir.addVertex(ofVec3f(yInter, tangent,xInter ));
        if(x == 0){
            firstX =ofVec3f(yOuter,tangent,xOuter);
            firstY = ofVec3f(yInter,tangent,xInter);
        }
        
    }
    cir.addVertex(firstX);
    cir.addVertex(firstY);
     return cir;
}

//ofMesh testApp::makeTorusX(float diameter,float fatness , float res,ofVec3f rotation){
//    ofMesh cir;
//    cir.clear();
//    cir.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
//    ofVec3f firstX;
//    ofVec3f firstY;
//    
//
//    
//    
//    for(float x=0;x<TWO_PI;x+=res){
//        
//        cosine=cos(x);
//        sine=sin(x);
//        tangent=0;
//        
//        float xOuter = ((diameter+fatness)*cosine);
//        float xInter = (diameter*cosine);
//        float yOuter = ((diameter+fatness)*sine);
//        float yInter = (diameter*sine);
//        cir.addVertex(ofVec3f(yOuter,tangent,xOuter));
//        cir.addVertex(ofVec3f(yInter, tangent,xInter ));
//        if(x == 0){
//            firstX =ofVec3f(yOuter,tangent,xOuter);
//            firstY = ofVec3f(yInter,tangent,xInter);
//        }
//        
//    }
//    cir.addVertex(firstX);
//    cir.addVertex(firstY);
//    return cir;
//}

