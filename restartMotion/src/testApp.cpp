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
    rectHeight = 240;
    
    string originalImageNames[] = {"red01.jpg", "red02.jpg", "red03.jpg", "red05.jpg", "red06.jpg", "red07.jpg", "red08.jpg", "red09.jpg", "red10.jpg", "redb01.jpg", "redb02.jpg", "redb03.jpg", "redb04.jpg", "redb05.jpg", "redb07.jpg", "redb08.jpg", "redb09.jpg", "redb10.jpg", "redb11.jpg", "redb12.jpg", "redb13.jpg", "redb14.jpg", "redb15.jpg", "redb16.jpg", "redb17.jpg", "redb18.jpg", "redb19.jpg", "redb20.jpg", "redb21.jpg", "redb22.jpg", "redb25.jpg", "redb26.jpg", "redb27.jpg", "redb28.jpg", "redb29.jpg", "redb30.jpg", "redb31.jpg", "redb32.jpg", "01.jpeg", "02.jpeg", "03.jpeg", "04.jpeg", "05.jpeg", "06.jpeg", "07.jpeg", "08.jpeg", "09.jpeg", "10.jpeg", "11.jpeg", "12.jpeg", "13.jpeg", "14.jpeg", "15.jpeg", "16.jpeg", "17.jpg", "18.jpeg", "19.jpeg", "20.jpeg", "21.jpeg", "22.jpeg", "23.jpeg", "24.jpeg", "25.jpeg", "26.jpeg", "27.jpeg", "28.jpeg", "29.jpeg", "30.jpeg", "31.jpeg", "32.jpeg", "33.jpeg", "34.jpeg", "35.jpeg", "36.jpeg", "37.jpeg", "38.jpeg", "39.jpeg", "40.jpeg", "41.jpeg", "42.jpeg", "43.jpeg", "44.jpeg", "45.jpeg", "46.jpeg", "47.jpeg", "48.jpeg", "49.jpeg", "50.jpeg", "51.jpeg", "52.jpeg", "53.jpeg", "54.jpeg", "60.jpg", "61.jpg", "62.jpg", "63.jpg", "64.jpg", "65.jpg", "66.jpg", "67.jpg", "68.jpg", "69.jpg", "70.jpg", "71.jpg", "72.jpg", "73.jpg", "74.jpg", "75.jpg", "76.jpg", "77 copy.jpg", "78.jpg", "79.jpg", "80.jpg", "81.jpg", "82.jpg", "83.jpg", "84.jpg"};
    int sizeOriginals = sizeof(originalImageNames)/sizeof(originalImageNames[0]);
    cout << "size of array: " << sizeOriginals << endl;


    string imageNames[] = {"red01_copy.jpg", "red02_copy.jpg", "red03_copy.jpg", "red05_copy.jpg", "red06_copy.jpg", "red07_copy.jpg", "red08_copy.jpg", "red09_copy.jpg", "red10_copy.jpg", "redb01 copy.jpg", "redb02 copy.jpg", "redb03 copy.jpg", "redb04 copy.jpg", "redb05 copy.jpg", "redb07 copy.jpg", "redb08 copy.jpg", "redb09 copy.jpg", "redb10 copy.jpg", "redb11 copy.jpg", "redb12 copy.jpg", "redb13 copy.jpg", "redb14 copy.jpg", "redb15 copy.jpg", "redb16 copy.jpg", "redb17 copy.jpg", "redb18 copy.jpg", "redb19 copy.jpg", "redb20 copy.jpg", "redb21 copy.jpg", "redb22 copy.jpg", "redb25 copy.jpg", "redb26 copy.jpg", "redb27 copy.jpg", "redb28 copy.jpg", "redb29 copy.jpg", "redb30 copy.jpg", "redb31 copy.jpg", "redb32 copy.jpg", "01 copy.jpg", "02 copy.jpg", "03 copy.jpg", "04 copy.jpg", "05 copy.jpg", "06 copy.jpg", "07 copy.jpg", "08 copy.jpg", "09 copy.jpg", "10 copy.jpg", "11 copy.jpg", "12 copy.jpg", "13 copy.jpg", "14 copy.jpg", "15 copy.jpg", "16 copy.jpg", "17 copy.jpg", "18 copy.jpg", "19 copy.jpg", "20 copy.jpg", "21 copy.jpg", "22 copy.jpg", "23 copy.jpg", "24 copy.jpg", "25 copy.jpg", "26 copy.jpg", "27 copy.jpg", "28 copy.jpg", "29 copy.jpg", "30 copy.jpg", "31 copy.jpg", "32 copy.jpg", "33 copy.jpg", "34 copy.jpg", "35 copy.jpg", "36 copy.jpg", "37 copy.jpg", "38 copy.jpg", "39 copy.jpg", "40 copy.jpg", "41 copy.jpg", "42 copy.jpg", "43 copy.jpg", "44 copy.jpg", "45 copy.jpg", "46 copy.jpg", "47 copy.jpg", "48 copy.jpg", "49 copy.jpg", "50 copy.jpg", "51 copy.jpg", "52 copy.jpg", "53 copy.jpg", "54 copy.jpg", "60 copy.jpg", "61 copy.jpg", "62 copy.jpg", "63 copy.jpg", "64 copy.jpg", "65 copy.jpg", "66 copy.jpg", "67 copy.jpg", "68 copy.jpg", "69 copy.jpg", "70 copy.jpg", "71 copy.jpg", "72 copy.jpg", "73 copy.jpg", "74 copy.jpg", "75 copy.jpg", "76 copy.jpg", "77 copy.jpg", "78 copy.jpg", "79 copy.jpg", "80 copy.jpg", "81 copy.jpg", "82 copy.jpg", "83 copy.jpg", "84 copy.jpg"};

    int size = sizeof(imageNames)/sizeof(imageNames[0]);
    cout << "size of array: " << size << endl;
    
    for( int i = 0; i < size; i++ ) {
        ofImage image;
        ofImage originalImage;
        
        image.loadImage( imageNames[i] ); //load images based on string of names
        image.resize(320, 240);
        mImages.push_back( image ); //push each image into array of ofImages
        
        originalImage.loadImage( originalImageNames[i] );
        originalImage.resize(320, 240);
        mOriginalImages.push_back( originalImage );
    }
   
    for(int i = 0; i < mImages.size(); i++) { //go through array of ofImages and push each into an ObjectData object with name and image, and then push entire object into a vector of ObjectData objects
        oData = ObjectData( mImages[i], imageNames[i]);
        imageObjects.push_back(oData);
    }
    
    for(int i = 0; i < mOriginalImages.size(); i++) {
        oDataOrig = ObjectData( mOriginalImages[i], originalImageNames[i]);
        originalImageObjects.push_back(oDataOrig);
    }
    
    
    cout << "size of imageObjects: " << imageObjects.size() << endl;
    gui = new ofxUICanvas(0 , 0, ofGetWidth() *0.3, ofGetHeight() * 0.2);
    gui->addSlider("CONT THRESHOLD", 0, 255, &threshold);
    gui->addMinimalSlider("MIN AREA", 0.0, 100.0, &minAreaValue);
    gui->addMinimalSlider("MAX AREA", 0.0, 100.0, &maxAreaValue);
    gui->addSpacer();
    
//    gui->addImage("SAMPLE COLOUR", &sampleColor, 10, 10);
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    
    animationIndex = -1;
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
    if(mode == 1){
        ofColor colorRed (0, 255, 0);
        targetColor = colorRed;
        
        for (int i = 0; i<imageObjects.size(); i++){
            myImage = imageObjects[i].mImg;
            myImageName = imageObjects[i].mName;
            myImage.update();
            
            ofxCv::threshold(myImage, thresholdImage, threshold);
            sampleColor.setColor(targetColor);
            contourFinder.setTargetColor(targetColor);
            contourFinder.setThreshold(threshold);
            contourFinder.setMinAreaRadius(minAreaValue);
            contourFinder.setMaxAreaRadius(maxAreaValue);
            contourFinder.findContours(myImage);
            
            loadDataAuto(i);
            cout << "inside loadDataAuto i = " << i << endl;
        }
    }
}

void testApp::draw() {
    if(mode == 0){ //load data
        loadingImageObjectData();
    }
    
//    if(mode == 1){
//        loadDataAuto();
//    }
    if(mode == 2){ //pick one image at a time
        drawRect();
        drawImages(currPathPoint);
    }
    
    if(mode == 3){ //set a path to select multiple images at once
        // draw rect and each point to visualize location
        drawRect();
        drawPath(0, 0, 0);
    }
    
    if (mode == 4){ //see the path animated and draw the images at the same time
        // draw rect and points to visualize path
        drawRect();
        drawPath(0, 0, 0);
        
        // animate frames
        ofPushMatrix();
        ofTranslate((ofGetWidth()*0.5 - myImage.getWidth()), mouseOffSetY);
        closestImages[animationIndex].mImg.draw(0, 0, closestImages[animationIndex].mImg.getWidth(), closestImages[animationIndex].mImg.getHeight());
        animationIndex++;
        
        if(animationIndex > closestImages.size()-1)
            animationIndex = 0;
        ofPopMatrix();
        cout << "animationIndex = " << animationIndex << endl;
        
        // draw points in diff color to visualize path
        drawAnimatedPoints(255, 0, 0);
    }
}

//------------------------ load one point and image at a time ---------------------------//

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
    
    return originalImageObjects[closestImageIndex];
}

void testApp::drawImages(ofVec2f currPathPoint){
    // to search one point at a time
    ObjectData closestImage = closestImageToPoint(currPathPoint);
    ofPushMatrix();
    ofTranslate((ofGetWidth()*0.5 - myImage.getWidth()), mouseOffSetY);
    closestImage.mImg.draw(0, 0, closestImage.mImg.getWidth(), closestImage.mImg.getHeight());
    ofPopMatrix();
}

//------------------------ load many points and images at once ---------------------------//
vector <ObjectData> testApp:: closestImageToPoint(vector<ofVec2f> pathPoints){
    float minDist = 10000;
    int closestImageIndex = 0;
    vector <ObjectData> imageObjectsSet;
    
    for (int j=0; j<pathPoints.size(); j++){
//        cout <<"closestImageIndex: " << closestImageIndex << endl;
        cout << "pathPoints: " << pathPoints.size() << endl;
        for (int i =0; i<imageObjects.size(); i++) {
            float d = imageObjects[i].measureDistance(pathPoints[j]);
            
            if(d < minDist){
                minDist = d;
                closestImageIndex = i;
            }
        }
        minDist =1000;
//        imageObjectsSet.push_back(imageObjects[closestImageIndex]);
        imageObjectsSet.push_back(originalImageObjects[closestImageIndex]);
        cout <<"imageObejctsSet: " << imageObjectsSet.size() << endl;
        
    }
    
    return imageObjectsSet;
}

void testApp::drawImages(vector <ofVec2f> currentPath){
    // to search vector of points and get vector of ObjectData
    closestImages = closestImageToPoint(currentPath);
    animationIndex = 0;
    cout << "closestImages: " << closestImages.size() << endl;
}

//------------------------ load image object data one at a time ---------------------------//

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
	ofTranslate(8, 100);
	ofFill();
	ofSetColor(0);
	ofRect(-3, -3, 64+6, 64+6);
	ofSetColor(targetColor);
	ofRect(0, 0, 64, 64);
    ofPopStyle();
    ofPopMatrix();
    
    // go through the contours and get W, H, Ratio of the image you are on
    for (int i = 0;  i<contourFinder.getBoundingRects().size(); i ++) {
        contourW = contourFinder.getBoundingRects()[i].width;
        contourH = contourFinder.getBoundingRects()[i].height;
        contourR = contourW / contourH;
        
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

//---------------this is to load the data automatically. need to finish.-------------------//
void testApp:: loadDataAuto(int x){

        for (int j = 0;  j<contourFinder.getBoundingRects().size(); j ++) {
            // store the x, y, height and width of the contour into the image object
            imageObjects[x].mCWidth = contourFinder.getBoundingRects()[j].width;
            cout << "mCWidth: " << imageObjects[x].mCWidth << endl;
            imageObjects[x].mCHeight = contourFinder.getBoundingRects()[j].height;
            cout << "mCHeight: " << imageObjects[x].mCHeight << endl;

            imageObjects[x].mCx = contourFinder.getBoundingRects()[j].x;
            //        cout << "mCx: " << imageObjects[x].mCx << endl;
            imageObjects[x].mCy = contourFinder.getBoundingRects()[j].y;
            //        cout << "mCy: " << imageObjects[x].mCy << endl;
    }
}



//------------------------ drawing functions to visualize frame and paths ---------------------------//
void testApp:: drawRect(){
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(mouseOffSetX, mouseOffSetY);
    ofFill();
    ofSetColor(255);
    ofRect(0, 0, 320, 240);
    ofPopStyle();
    ofPopMatrix();
}

void testApp::drawPath(int r, int g, int b){
    ofPushMatrix();
    ofPushStyle();
    ofFill();
    ofSetColor(r, g, b);
    ofTranslate(mouseOffSetX, mouseOffSetY);
    for(int i = 0; i<currPath.size(); i++){
        ofCircle(currPath[i].x, currPath[i].y, 5);
    }
    ofPopStyle();
    ofPopMatrix();
}

void testApp::drawAnimatedPoints(int r, int g, int b){
    ofPushMatrix();
    ofPushStyle();
    ofFill();
    ofSetColor(r, g, b);
    ofTranslate(mouseOffSetX, mouseOffSetY);
    ofCircle(currPath[animationIndex].x, currPath[animationIndex].y, 5);
    ofPopStyle();
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
        if(x > ofGetWidth()*0.3 && x < ofGetWidth()*0.3 + myImage.getWidth()
           && y< myImage.getHeight()){
            targetColor = myImage.getPixelsRef().getColor(x - ofGetWidth()*0.3, y);
            contourFinder.setTargetColor(targetColor, trackingColorMode);
        }
    }
    
    if (mode == 2){
        // if mouse is in the rect
        if(x >= mouseOffSetX && x <= mouseOffSetX + rectWidth && y>= mouseOffSetY && y <= mouseOffSetY + rectHeight){
            // click to make path points
            currPathPoint = ofVec2f(x - mouseOffSetX, y - mouseOffSetY);
            // cout << "currentPathPoint: " << currPathPoint << endl;
            
            currPath.push_back( currPathPoint );
            cout << "currPath: " << currPath.size() << endl;
        }
    }
    
    if (mode == 3){
        if (x >= mouseOffSetX && x <= mouseOffSetX + rectWidth && y>= mouseOffSetY && y <= mouseOffSetY + rectHeight){
            // click to make path points
            currPoint = ofVec2f(x - mouseOffSetX, y - mouseOffSetY);
            // cout << "currentPoint: " << currPoint << endl;
            
            currPath.push_back( currPoint );
            cout << "currPath: " << currPath.size() << endl;
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
    if(key == '2') {
		mode = 2;
	}
    if(key == '3') {
		mode = 3;
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
    
    if(key == 's') {
        mode = 4;
        drawImages(currPath);
        ofSetFrameRate(8);
        cout <<"S was pressed, drawImages" << endl;
	}
    
    if(key == 'c') {
        currPath.clear();
        cout <<"C was pressed" << currPath.size() << endl;
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