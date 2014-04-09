#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxUI.h"
#include "ObjectData.h"
#include <fstream>
#include <iostream>

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
    void drawRect();
    void drawPath(int r, int g, int b);
    void drawAnimatedPoints(int r, int g, int b);
    void generatePattern();
    void loadImgsFromDir();
    void drawImageTiles(int selectedImg);
    void drawCurrImage(int currIndex);
    
    void writeJSON();
    
    ObjectData closestImageToPoint(ofVec2f pathPoint);
    vector <ObjectData> closestImageToPoint(vector<ofVec2f> pathPoints);
    void exit();

	ofxUICanvas * gui;
    ofxUIDropDownList *ddl;
    
    int mouseOffSetX;
    int mouseOffSetY;
    int frameWidth;
    int frameHeight;
    
    int closestImageIndex;
    
    ofxCv::ContourFinder contourFinder;
    float threshold;
    float minAreaValue, maxAreaValue;
	ofxCv::TrackingColorMode trackingColorMode;
	ofColor targetColor;
    ofColor colorRed;
    ofColor tileColor;

    ofImage sampleColor;
    ofImage myImage;
    ofImage thresholdImage;
    string myImageName;
    
    ofImage tile;
    int row;
    int col;
    int index;
    float gridWidth;
    float gridHeight;
    

    
    vector<ofImage> mImages;
    vector<ofImage> mOriginalImages;
    int currentImage;
    
    ObjectData oData;
    ObjectData oDataOrig;
    vector<ObjectData> imageObjects;
    vector<ObjectData> originalImageObjects;
    vector <ObjectData> imageObjectsSet;
    vector <ObjectData> closestImages;
    
    ofVec2f currPathPoint;
    ofVec2f currPoint;
    vector<ofVec2f> currPath;
    
    int mode;
    float contourW;
    float contourH;
    float contourR;
    
    int animationIndex;
    
    string dirNameEdit;
    string dirNameOrig;
    ofDirectory myDirEdit;
    ofDirectory myDirOrig;
};
