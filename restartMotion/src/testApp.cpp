#include "testApp.h"

using namespace ofxCv;
using namespace cv;


void testApp::setup() {
    
	trackingColorMode = TRACK_COLOR_HSV;
    
    threshold = 100;
    minAreaValue = 0;
    maxAreaValue =100;
    
    mode = 0;
    
    mouseOffSetX = ofGetWidth()*0.5;
    mouseOffSetY = ofGetHeight()*0.7;
    rectWidth = 320;
    rectHeight = 240;
    
    cout << "size of imageObjects: " << imageObjects.size() << endl;
    gui = new ofxUICanvas(0 , 0, ofGetWidth() *0.3, ofGetHeight() * 0.2);
    gui->addSlider("CONT THRESHOLD", 0, 255, &threshold);
    gui->addMinimalSlider("MIN AREA", 0.0, 100.0, &minAreaValue);
    gui->addMinimalSlider("MAX AREA", 0.0, 100.0, &maxAreaValue);
    gui->addSpacer();
    
    loadImgsFromDir();
    
    //    gui->addImage("SAMPLE COLOUR", &sampleColor, 10, 10);
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    
    animationIndex = -1;
    loadDataAuto();
}

void testApp::update() {
//    if(mode == 0){
//        myImage = imageObjects[currentImage].mImg;
//        myImageName = imageObjects[currentImage].mName;
//        myImage.update();
//        
//        ofxCv::threshold(myImage, thresholdImage, threshold);
//        sampleColor.setColor(targetColor);
//        contourFinder.setTargetColor(targetColor);
//        contourFinder.setThreshold(threshold);
//        contourFinder.setMinAreaRadius(minAreaValue);
//        contourFinder.setMaxAreaRadius(maxAreaValue);
//        contourFinder.findContours(myImage);
//        thresholdImage.resize(320, 240);
//        thresholdImage.update();
//        
//    }
}

void testApp::draw() {
    if(mode == 0){ //load data
//        loadingImageObjectData();
    }
    
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
        ofTranslate((mouseOffSetX + myImage.getWidth()), mouseOffSetY);
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

//------------------------------ loadImages from directory --------------------------------//
void testApp:: loadImgsFromDir() {
// void (string path to directory, vector of strings for filenames, ofDirectory name, vector of images)
string dirNameEdit ="/Users/cvcarter/Documents/of_v0.8.0_osx_release/apps/thesis/restartMotion/bin/data/edited"; //directory path
string dirNameOrig ="/Users/cvcarter/Documents/of_v0.8.0_osx_release/apps/thesis/restartMotion/bin/data/originals";
vector<string> imageNamesEdit; //vector of strings to store file names
vector<string> imageNamesOrig;

myDirEdit = ofDirectory(dirNameEdit); //create ofDirectory with file path string
myDirOrig = ofDirectory(dirNameOrig);

if(myDirEdit.exists()){ //if directory exists, list the contents
    myDirEdit.listDir();
    
    vector<ofFile> files = myDirEdit.getFiles(); //create vector of ofFiles, call getFiles on the dir and store them in vector
    
    for(int i = 0 ; i<files.size(); i++){ //iterate through vector of ofFiles
        
        string imgLocation = files[i].getAbsolutePath(); //get absolute path for each in order to load the images
        imageNamesEdit.push_back(files[i].getFileName()); //get and store each file name to have for ObjectData later
        
        ofImage img;
        
        if(img.loadImage(imgLocation)){ //if image is loading, resize it and debugging
            img.resize(320,240);
            cout<<"Loading img : "<<imgLocation<<endl;
            }
            
            else{
                ofLogError()<<"Couldnt load img : "<<imgLocation<<endl;
            }
            
            mImages.push_back(img); //push each img into mImages vector of images to later be pushed into ObjectData
            }
            }
            else{
                ofLogError()<<"Directory : "<<dirNameEdit<<" doesnt exist"<<endl;
            }
            
            for(int i = 0; i < mImages.size(); i++) {
                oData = ObjectData( mImages[i], imageNamesEdit[i]); //push each mImages & each filename into ObjectData object
                imageObjects.push_back(oData); //then push entire object into a vector of ObjectData objects
            }
            
            if(myDirOrig.exists()){
                myDirOrig.listDir();
                
                vector<ofFile> filesO = myDirOrig.getFiles();
                
                for(int i = 0 ; i<filesO.size(); i++){
                    
                    string imgLocation = filesO[i].getAbsolutePath();
                    imageNamesOrig.push_back(filesO[i].getFileName());
                    
                    ofImage img;
                    
                    if(img.loadImage(imgLocation)){
                        img.resize(320,240);
                        cout<<"Loading img : "<<imgLocation<<endl;
                    }
                    
                    else{
                        ofLogError()<<"Couldnt load img : "<<imgLocation<<endl;
                    }
                    
                    mOriginalImages.push_back(img);
                }
            }
            else{
                ofLogError()<<"Directory : "<<dirNameEdit<<" doesnt exist"<<endl;
            }
            
            
            for(int i = 0; i < mOriginalImages.size(); i++) {
                oDataOrig = ObjectData( mOriginalImages[i], imageNamesOrig[i]);
                originalImageObjects.push_back(oDataOrig);
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
    
    //This is a debug draw
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
    
    
    
    // Iterate tthrough bounding boxes of current image and store in imageObjects.
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
        
        
        // draw subsections with the contours. (Also debug)
        ofPushMatrix();
        ofTranslate(ofGetWidth()*0.3, 5 + myImage.getHeight());
        myImage.drawSubsection(contourFinder.getBoundingRects()[i].x, contourFinder.getBoundingRects()[i].y, contourW, contourH, contourFinder.getBoundingRects()[i].x, contourFinder.getBoundingRects()[i].y);
    }
    ofPopMatrix();
}

//---------------load the data automatically in setup.-------------------//
void testApp:: loadDataAuto(){
    ofColor colorRed (255, 0, 0);
    targetColor = colorRed;

    for(int i =0; i<imageObjects.size();i++){
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
        
        for (int j = 0;  j<contourFinder.getBoundingRects().size(); j ++) {
            imageObjects[i].mCWidth = contourFinder.getBoundingRects()[j].width;
//            cout << "mCWidth: " << imageObjects[i].mCWidth << endl;
            imageObjects[i].mCHeight = contourFinder.getBoundingRects()[j].height;
//            cout << "mCHeight: " << imageObjects[i].mCHeight << endl;
            imageObjects[i].mCx = contourFinder.getBoundingRects()[j].x;
            imageObjects[i].mCy = contourFinder.getBoundingRects()[j].y;
            
        }
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
    
    }
    
    if (mode == 2){
        // if mouse is in the rect
        if(x >= mouseOffSetX && x <= mouseOffSetX + rectWidth && y>= mouseOffSetY && y <= mouseOffSetY + rectHeight){
            currPathPoint = ofVec2f(x - mouseOffSetX, y - mouseOffSetY); // click to make path points
            // cout << "currentPathPoint: " << currPathPoint << endl;
            
            currPath.push_back( currPathPoint );
            cout << "currPath: " << currPath.size() << endl;
        }
    }
    
    if (mode == 3){
        if (x >= mouseOffSetX && x <= mouseOffSetX + rectWidth && y>= mouseOffSetY && y <= mouseOffSetY + rectHeight){
            currPoint = ofVec2f(x - mouseOffSetX, y - mouseOffSetY); // click to make path points
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
        cout <<"C was pressed. currPath is now: " << currPath.size() << endl;
	}
    
    // cycle through the imageObjects
    if(key == 'k'){
        //go back but check for 0
            if (currentImage>0){
            currentImage--;
        }
    }
    if(key == 'l'){
        //go ++ and  check for Size -1
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