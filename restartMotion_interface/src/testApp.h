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
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void guiEvent(ofxUIEventArgs &e);
    void loadingImageObjectData();
    void loadDataAuto();
    void drawImages(ofVec2f currPathPoint);
    void drawImages(vector<ofVec2f> currentPath);
    void drawRect();
    void drawPath(int r, int g, int b);
    void drawAnimatedPoints(int r, int g, int b, int a);
    void generatePattern();
    void loadImgsFromDir();
    void drawImageTiles();
    void highlightSelectedImg(int selectedImg);
    void poster();
    
    void writeJSON();
    ofImage bg;
    ObjectData closestImageToPoint(ofVec2f pathPoint);
    vector <ObjectData> closestImageToPoint(vector<ofVec2f> pathPoints);
    void exit();
    
	ofxUICanvas * gui;
    ofxUIDropDownList *ddl;
    ofxUIDropDownList *ddmode;
    ofxUIToggleMatrix *toggle;
//    ofxUIWidget *toggle;
    ofxUIRadio *myRadio;
    
    ofTrueTypeFont myfont;
    ofTrueTypeFont myfontS;
    ofTrueTypeFont myfontB;
    ofTrueTypeFont myfontSB;
    
    ofxUICanvas * gui2;
    ofxUICanvas * gui3;
    
    int mouseOffSetX;
    int mouseOffSetY;
    int frameWidth;
    int frameHeight;
    int frameRate;
    int closestImageIndex;
    int previousImage;
    bool mouseOverMode;
    
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
    float row;
    float col;
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
    
    ofVec2f mouseOverPath;
    vector<ofVec2f> currPath;
    ofVec2f currPathPoint;
    ofVec2f currPoint;
    
    ofPolyline line;
    vector<ofVec2f> verts;
    ofPath drawing;
    ofPolyline path;
    
    
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
