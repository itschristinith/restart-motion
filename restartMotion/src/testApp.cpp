#include "testApp.h"

using namespace ofxCv;
using namespace cv;


void testApp::setup() {

	trackingColorMode = TRACK_COLOR_HSV;
    
    threshold = 100;
    minAreaValue = 0;
    maxAreaValue =100;
    
    mode = 0;
    
    mouseOffSetX = 0;
    mouseOffSetY = ofGetHeight()*0.7;
    rectWidth = 320;
    rectHeight = 120;

    
//    string imageNames[] = {"redb01.jpg", "redb02.jpg", "redb03.jpg", "redb04.jpg", "redb05.jpg", "redb06.jpg", "redb07.jpg", "redb08.jpg", "redb09.jpg", "redb10.jpg", "redb11.jpg", "redb12.jpg", "redb13.jpg", "redb14.jpg", "redb15.jpg", "redb16.jpg", "redb17.jpg", "redb18 copy.jpg", "redb19 copy.jpg", "redb20 copy.jpg", "redb21 copy.jpg", "redb22 copy.jpg", "redb23.jpg", "redb24.jpg", "redb25 copy.jpg", "redb26 copy.jpg", "redb27 copy.jpg", "redb28 copy.jpg", "redb29 copy.jpg", "redb30 copy.jpg", "redb31 copy.jpg", "redb32 copy.jpg", "red06.jpg", "red07.jpg", "red08.jpg", "red09.jpg", "red01.jpg", "red02.jpg", "red03.jpg", "red04.jpg", "red05.jpg"};

    string imageNames[] = {"red01_copy.jpg", "red02_copy.jpg", "red03_copy.jpg", "red04_copy.jpg", "red05_copy.jpg", "red06_copy.jpg", "red07_copy.jpg", "red08_copy.jpg", "red09_copy.jpg", "red10_copy.jpg", "redb01 copy.jpg", "redb02 copy.jpg", "redb03 copy.jpg", "redb04 copy.jpg", "redb05 copy.jpg", "redb06 copy.jpg", "redb07 copy.jpg", "redb08 copy.jpg", "redb09 copy.jpg", "redb10 copy.jpg", "redb11 copy.jpg", "redb12 copy.jpg", "redb13 copy.jpg", "redb14 copy.jpg", "redb15 copy.jpg", "redb16 copy.jpg", "redb17 copy.jpg", "redb18 copy.jpg", "redb19 copy.jpg", "redb20 copy.jpg", "redb21 copy.jpg", "redb22 copy.jpg", "redb25 copy.jpg", "redb26 copy.jpg", "redb27 copy.jpg", "redb28 copy.jpg", "redb29 copy.jpg", "redb30 copy.jpg", "redb31 copy.jpg", "redb32 copy.jpg"};

    int size = sizeof(imageNames)/sizeof(imageNames[0]);
    cout << "size of array: " << size << endl;
    
    for( int i = 0; i < size; i++ ) {
        ofImage image;
        image.loadImage( imageNames[i] );
        image.resize(320, 240);
        mImages.push_back( image );
    }
   
    for(int i = 0; i < mImages.size(); i++) {
        oData = ObjectData( mImages[i], imageNames[i]);
        imageObjects.push_back(oData);
    }
    cout << "size of imageObjects: " << imageObjects.size() << endl;
    gui = new ofxUICanvas(0 , 0, ofGetWidth() *0.3, ofGetHeight() * 0.2);
    gui->addSlider("CONT THRESHOLD", 0, 255, &threshold);
    gui->addMinimalSlider("MIN AREA", 0.0, 100.0, &minAreaValue);
    gui->addMinimalSlider("MAX AREA", 0.0, 100.0, &maxAreaValue);
    gui->addSpacer();
    
//    gui->addImage("SAMPLE COLOUR", &sampleColor, 10, 10);
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
 }

void testApp::update() {
    if(mode == 0){
    myImage = imageObjects[currentImage].mImg;
    myImageName = imageObjects[currentImage].mName;
    myImage.update();
    
    ofxCv::threshold(myImage, thresholdImage, threshold);
    sampleColor.setColor(targetColor);
    contourFinder.setTargetColor(targetColor);
    contourFinder.setThreshold(threshold);
    contourFinder.setMinAreaRadius(minAreaValue);
    contourFinder.setMaxAreaRadius(maxAreaValue);
    contourFinder.findContours(myImage);
    thresholdImage.resize(320, 240);
    thresholdImage.update();
    
    }
}

void testApp::draw() {
    if(mode == 0){
        loadingImageObjectData();
    }
    else if(mode == 1){
        drawImages(currPathPoint);
    }
    
    // draw rect to visualize the currPathPoint
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(mouseOffSetX, mouseOffSetY);
    ofFill();
    ofSetColor(255);
    ofRect(0, 0, 320, 240);
    ofPopStyle();
    ofPopMatrix();
}

ObjectData testApp:: closestImageToPoint(ofVec2f pathPoint){
    float minDist = 10000;
    int closestImageIndex = 0;
    
    for (int i =0; i<imageObjects.size(); i++) {
        float d = imageObjects[i].measureDistance(pathPoint);
        
        if(d < minDist){
            minDist = d;
            closestImageIndex = i;
        }
    }
    
    return imageObjects[closestImageIndex];
}

void testApp::drawImages(ofVec2f currPathPoint){
    
    ObjectData closestImage = closestImageToPoint(currPathPoint);
    
    ofPushMatrix();
    ofTranslate((ofGetWidth()*0.5 - myImage.getWidth()), mouseOffSetY);
    closestImage.mImg.draw(0, 0, closestImage.mImg.getWidth(), closestImage.mImg.getHeight());
    ofPopMatrix();

}

void testApp:: loadingImageObjectData(){
    //translate to 0.3 of the width, draw the image
    ofPushMatrix();
    ofTranslate(ofGetWidth()*0.3, 0);
    myImage.draw(0,0, myImage.getWidth(), myImage.getHeight());
    // draw the thresholdImage to see what it's doing
    thresholdImage.draw(myImage.getWidth() + 10,0, thresholdImage.getWidth(), thresholdImage.getHeight());
	// draw the contours
    contourFinder.draw();
    ofPopMatrix();
    
    // draw rectangle with selected sample color
    ofPushMatrix();
    ofPushStyle();
	ofTranslate(8, 75);
	ofFill();
	ofSetColor(0);
	ofRect(-3, -3, 64+6, 64+6);
	ofSetColor(targetColor);
	ofRect(0, 0, 64, 64);
    ofPopStyle();
    ofPopMatrix();
    
    // draw the subsections of the image from the contour bounding boxes below the original image
    for (int i = 0;  i<contourFinder.getBoundingRects().size(); i ++) {
        contourW = contourFinder.getBoundingRects()[i].width;
        contourH = contourFinder.getBoundingRects()[i].height;
        contourR = contourW / contourH;
//        cout << "contourWidth i: " << contourW << endl;
//        cout << "contourHeight i: " << contourH << endl;
        
        // store the x, y, height and width of the contour into the image object
        imageObjects[currentImage].mCWidth = contourFinder.getBoundingRects()[i].width;
//        cout << "mCWidth: " << imageObjects[currentImage].mCWidth << endl;
        imageObjects[currentImage].mCHeight = contourFinder.getBoundingRects()[i].height;
//        cout << "mCHeight: " << imageObjects[currentImage].mCHeight << endl;
        
        imageObjects[currentImage].mCx = contourFinder.getBoundingRects()[i].x;
//        cout << "mCx: " << imageObjects[currentImage].mCx << endl;
        imageObjects[currentImage].mCy = contourFinder.getBoundingRects()[i].y;
//        cout << "mCy: " << imageObjects[currentImage].mCy << endl;
        
        
        // draw subsections with the contours
        ofPushMatrix();
        ofTranslate(ofGetWidth()*0.3, 5 + myImage.getHeight());
        myImage.drawSubsection(contourFinder.getBoundingRects()[i].x, contourFinder.getBoundingRects()[i].y, contourW, contourH, contourFinder.getBoundingRects()[i].x, contourFinder.getBoundingRects()[i].y);
    }
    ofPopMatrix();
}

void testApp::mousePressed(int x, int y, int button) {
    if (mode == 0) {
        // set color by selecting pixel, but only if it's within the width/height of the image
        if(x > ofGetWidth()*0.3 && x < ofGetWidth()*0.3 + myImage.getWidth()
           && y< myImage.getHeight()){
            targetColor = myImage.getPixelsRef().getColor(x - ofGetWidth()*0.3, y);
            contourFinder.setTargetColor(targetColor, trackingColorMode);
        }
    }
    
    if (mode == 1){
        if(x >= mouseOffSetX && x <= mouseOffSetX + rectWidth && y>= mouseOffSetY && y <= mouseOffSetY + rectHeight){
            // click to make path points
            currPathPoint = ofVec2f(x - mouseOffSetX, y - mouseOffSetY);
            cout << "currentPathPoint: " << currPathPoint << endl;
        }
    }
}

void testApp::keyPressed(int key) {
    if(key == '0') {
		mode = 0;
	}
    if(key == '1') {
		mode = 1;
	}
	if(key == 'h') {
		trackingColorMode = TRACK_COLOR_H;
	}
	if(key == 'r') {
		trackingColorMode = TRACK_COLOR_RGB;
	}
    if(key == 'f') {
        ofToggleFullscreen();
	}
    
    // cycle through the imageObjects
    if(key == 'k'){
        //go back but check for 0
        //myImageIndex--;
        if (currentImage>0){
            currentImage--;
        }
    }
    if(key == 'l'){
        //go ++ and  check for Size -1
        //myImageIndex++;
        if (currentImage<imageObjects.size()-1){
            currentImage++;
        }
    }

//contourFinder.setTargetColor(targetColor, trackingColorMode);
}

void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();
	
//	if(name == "RED")
//	{
//		ofxUISlider *slider = (ofxUISlider *) e.widget;
//		red = slider->getScaledValue();
//        cout << "value: " << slider->getScaledValue() << endl;
//	}
//	else if(name == "GREEN")
//	{
//		ofxUIMinimalSlider *slider = (ofxUIMinimalSlider *) e.widget;
//		green = slider->getScaledValue();
//        cout << "value: " << slider->getScaledValue() << endl;
//	}
//	else if(name == "BLUE")
//	{
//		ofxUIBiLabelSlider *slider = (ofxUIBiLabelSlider *) e.widget;
//		blue = slider->getScaledValue();
//        cout << "value: " << slider->getScaledValue() << endl;
//	}
//    else if(name == "RSLIDER")
//    {
//        ofxUIRangeSlider *rslider = (ofxUIRangeSlider *) e.widget;
//        cout << "valuelow: " << rslider->getScaledValueLow() << endl;
//        cout << "valuehigh: " << rslider->getScaledValueHigh() << endl;
//    }
//    else if(name == "PAD")
//    {
//        ofxUI2DPad *pad = (ofxUI2DPad *) e.widget;
//        cout << "value x: " << pad->getScaledValue().x << endl;
//        cout << "value y: " << pad->getScaledValue().y << endl;
//    }
//    else if(name == "CSLIDER" || name == "CSLIDER 2")
//    {
//        ofxUIRotarySlider *rotslider = (ofxUIRotarySlider *) e.widget;
//        cout << "value: " << rotslider->getScaledValue() << endl;
//    }
}
//--------------------------------------------------------------
void testApp::exit()
{
    delete gui;
}