//
//  ObjectData.cpp
//  ofApp
//
//  Created by Christina Carter on 3/7/14.
//
//

#include "ObjectData.h"

ObjectData::ObjectData( ofImage img, std::string imgName){
    mImg = img;
    mName = imgName;
    mCWidth = -1;
    mCHeight = -1;
    mCx = -1;
    mCy = -1;
    center = ofVec2f(-1, -1);
//    center = ofPoint (-1);
 
}

float ObjectData:: measureDistance(ofVec2f pathPoint){
//    return pathPoint.distance(ofVec2f(mCx, mCy)); //getting the bounding rect
    return pathPoint.distance(ofVec2f(center.x, center.y)); //getting the center point
}

//void ObjectData::contours(){
//    for (int i = 0;  i<contourFinder.getBoundingRects().size(); i ++) {
//        mCWidth = contourFinder.getBoundingRects()[i].width;
//        mCHeight = contourFinder.getBoundingRects()[i].height;
//}