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
    void loadDataAuto();
    void drawImages(ofVec2f currPathPoint);
    void drawImages(vector<ofVec2f> currentPath);
    ObjectData closestImageToPoint(ofVec2f pathPoint);
    vector <ObjectData> closestImageToPoint(vector<ofVec2f> pathPoints);
    void exit();

	ofxUICanvas * gui;
    
    int mouseOffSetX;
    int mouseOffSetY;
    int rectWidth;
    int rectHeight;
    
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
    vector <ObjectData> imageObjectsSet;
    
    ofVec2f currPathPoint;
    vector<ofVec2f> currPath;
    
    int mode;
    float contourW;
    float contourH;
    float contourR;
};
