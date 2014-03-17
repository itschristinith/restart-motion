#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxUI.h"
#include "ObjectData.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
    void mousePressed(int x, int y, int button);
	void keyPressed(int key);
    void guiEvent(ofxUIEventArgs &e);
    void loadingImageObjectData();
    void drawImages(ofVec2f currPathPoint);
    ObjectData closestImageToPoint(ofVec2f pathPoint);
    void exit();

	ofxUICanvas * gui;
    
    int mouseOffSetX;
    int mouseOffSetY;
    
    ofxCv::ContourFinder contourFinder;
    float threshold;
    float minAreaValue, maxAreaValue;
	ofxCv::TrackingColorMode trackingColorMode;
	ofColor targetColor;

    ofImage sampleColor;
    ofImage myImage;
    ofImage thresholdImage;
    string myImageName;
    
    ofImage thumbImage;
    
    vector<ofImage> mImages;
    int currentImage;
    
    ObjectData oData;
    vector<ObjectData> imageObjects;
    
    ofVec2f currPathPoint;
    int mode;
    float contourW;
    float contourH;
    float contourR;
};
