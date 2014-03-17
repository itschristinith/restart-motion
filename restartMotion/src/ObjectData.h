//
//  ObjectData.h
//  ofApp
//
//  Created by Christina Carter on 3/7/14.
//
//

#pragma once

#include "ofMain.h"

class ObjectData {
public:
    
    //methods
//    void contours();
    
    ObjectData(){}
    ObjectData( ofImage img, std::string imgName);
//    ~ObjectData();
    
    float measureDistance(ofVec2f pathPoint);
    ofImage mImg;
    std::string mName;
    float mCWidth;
    float mCHeight;
    int mCx;
    int mCy;
    
    

};

/*
//this is from mike A
class ObjectData {
public:
    
    ObjectData(){}
    ObjectData( ofImage img, std::string imgName );
    ~ObjectData();
    
    std::string mName;
    ofImage mImg;
    
};
*/