#include "testApp.h"


using namespace ofxCv;
using namespace cv;

void testApp::setup() {
    ofBackground(0, 0, 0);
    
	trackingColorMode = TRACK_COLOR_HSV;
    
    threshold = 100;
    minAreaValue = 0;
    maxAreaValue =100;
    mode = 3;
//    mouseOffSetX = (ofGetWidth() - frameWidth*2)*0.5;
//    mouseOffSetY = (ofGetHeight() - frameHeight*2)*0.5;
    frameWidth = 320;
    frameHeight = 240;
    tileColor = (ofColor(ofRandom(128, 255), 0, 0));
    vector<string> modes;
    modes.push_back("0");
    modes.push_back("1");
    modes.push_back("2");
    modes.push_back("3");
    modes.push_back("4");
    gui = new ofxUICanvas(0 , 0, ofGetWidth() *0.3, ofGetHeight() * 0.2);
//    gui->addButton("MODE", false);
//    gui->addRadio("MODE", modes, 1, 15, 15);
    
    gui->addLabel("MODE");
    gui->addSpacer();
    gui->addLabel("'0' FOR NOTHING", OFX_UI_FONT_SMALL);
    gui->addLabel("'1' FOR NOTHING", OFX_UI_FONT_SMALL);
    gui->addLabel("'2' TO DRAW INDIVIDUAL POINTS", OFX_UI_FONT_SMALL);
    gui->addLabel("'3' TO DRAW MANY POITNS", OFX_UI_FONT_SMALL);
    gui->addSpacer();
    gui->setWidgetFontSize(OFX_UI_FONT_SMALL);
    gui->addToggle("SHOW ACTIVE", false);
    ddl = gui->addDropDownList("DYNAMIC DROP DOWN", modes);
    ddl->setAllowMultiple(true);
    //    ddl->setAutoClose(true);
    gui->autoSizeToFitWidgets();
    //    gui->setDrawWidgetPadding(true);
//    ofAddListener(gui->newGUIEvent, this, &ofApp::guiEvent);

//    gui->addSlider("CONT THRESHOLD", 0, 255, &threshold);
//    gui->addMinimalSlider("MIN AREA", 0.0, 100.0, &minAreaValue);
//    gui->addMinimalSlider("MAX AREA", 0.0, 100.0, &maxAreaValue);
    gui->addSpacer();
    
    loadImgsFromDir();
    
    //    gui->addImage("SAMPLE COLOUR", &sampleColor, 10, 10);
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    
    animationIndex = -1;
    loadDataAuto();
    
//    writeJSON();
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
    mouseOffSetX = (ofGetWidth() - frameWidth*2)*0.5;
    mouseOffSetY = (ofGetHeight() - frameHeight*2)*0.5;
    
//    //adjust size of frame if in mode 3 and therefore mode 4
//    if (mode == 3){
//        frameWidth = 640;
//        frameHeight = 480;
//    }

}

void testApp::draw() {
//    ofBackgroundGradient(ofColor::gray, ofColor::black);

    
    if(mode == 0){ //load data
//        loadingImageObjectData();
    }
    
    if(mode == 1){
    }
    
    if(mode == 2){ //pick one image at a time
        ofPushMatrix();
        ofTranslate(0, ofGetHeight()-300);
        drawImageTiles(closestImageIndex);
        ofPopMatrix();
        
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
        
        ofPushMatrix();
        ofTranslate(mouseOffSetX, mouseOffSetY);
        closestImages[animationIndex].mImg.draw(0, 0, closestImages[animationIndex].mImg.getWidth(), closestImages[animationIndex].mImg.getHeight());
        animationIndex++;
        ofPopMatrix();
        
        if(animationIndex > closestImages.size()-1)
            animationIndex = 0;
//        cout << "animationIndex = " << animationIndex << endl;
        
        // draw points in diff color to visualize path
        drawAnimatedPoints(255, 0, 0);
    }
    
    if (mode == 5){
        generatePattern();
    }
}

//------------------------------ loadImages from directory  -----------------------------//

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
            img.resize(frameWidth, frameHeight);
//            cout<<"Loading img : "<<imgLocation<<endl;
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
                        img.resize(frameWidth, frameHeight);
//                        cout<<"Loading img : "<<imgLocation<<endl;
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

//----------------------- load the data automatically in setup -------------------------//

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
            imageObjects[i].center = toOf(contourFinder.getCenter(j));
//            cout << "center x: " << imageObjects[i].center.x << " y: " << imageObjects[i].center.y << endl;
            imageObjects[i].mCWidth = contourFinder.getBoundingRects()[j].width;
            imageObjects[i].mCHeight = contourFinder.getBoundingRects()[j].height;
            imageObjects[i].mCx = contourFinder.getBoundingRects()[j].x;
            imageObjects[i].mCy = contourFinder.getBoundingRects()[j].y;
            
        }
    }
}

//-------------------------------- draw image tiles ------------------------------------//

void testApp::drawImageTiles(int selectedImg){
    
    row = 5;
    col = 23;
    gridWidth = ofGetWidth() / col;
    gridHeight = 300 / row;
    
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            index = j + i * col;
            tile = mOriginalImages[index];
            tile.draw(j*gridWidth, i*gridHeight, gridWidth, gridHeight);
            cout << index << " -- (" << i << "," << j << ")  -- " << gridWidth << "," << gridHeight << endl;
        }
    }
}
//
void testApp::drawCurrImage(int currIndex) {
    int indexWidth = gridWidth * currIndex;
    int indexHeight = gridHeight * currIndex;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
//            index = j + i * col;
            ofPushMatrix();
            ofTranslate(0, ofGetHeight()-300);
            ofPushStyle();
            ofFill();
            ofSetColor(0);
            ofRect(j*indexWidth, i*indexHeight, gridWidth, gridHeight);
            ofPopStyle();
            ofPopMatrix();
            cout << currIndex << " -- (" << i << "," << j << ")  -- " << gridWidth << "," << gridHeight << endl;
        }
    }

}

//------------------------ load many points and images at once --------------------------//

vector <ObjectData> testApp:: closestImageToPoint(vector<ofVec2f> pathPoints){
    float minDist = 10000;
    closestImageIndex = 0;
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
        minDist =10000;
        //        imageObjectsSet.push_back(imageObjects[closestImageIndex]);
        imageObjectsSet.push_back(originalImageObjects[closestImageIndex]);
        cout <<"imageObjectsSet: " << imageObjectsSet.size() << endl;
        
    }
    
    return imageObjectsSet;
}

void testApp::drawImages(vector <ofVec2f> currentPath){
    // to search vector of points and get vector of ObjectData
    closestImages = closestImageToPoint(currentPath);
    animationIndex = 0;
    cout << "closestImages: " << closestImages.size() << endl;
}

//------------------- drawing functions to visualize frame and paths -------------------//

void testApp:: drawRect(){
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(mouseOffSetX, mouseOffSetY);
    ofFill();
    ofSetColor(255);
    ofRect(0, 0, frameWidth, frameHeight);
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

//----------------------------- mode to generate pattern -------------------------------//

void testApp::generatePattern(){
    drawRect();
    drawPath(0, 0, 0);

    // animate frames, upper left
    ofPushMatrix();
    ofTranslate(mouseOffSetX, mouseOffSetY);
    closestImages[animationIndex].mImg.draw(0, 0, closestImages[animationIndex].mImg.getWidth(), closestImages[animationIndex].mImg.getHeight());
    //        animationIndex++;
    ofPopMatrix();
    
    // animate frame, upper right
    ofPushMatrix();
    ofTranslate(mouseOffSetX + frameWidth, mouseOffSetY);
    ofImage upperRight = closestImages[animationIndex].mImg;
    
    upperRight.mirror(0, 180);
    upperRight.draw(0, 0, closestImages[animationIndex].mImg.getWidth(), closestImages[animationIndex].mImg.getHeight());
    //        animationIndex++;
    ofPopMatrix();
    
    // animate frame, bottom right
    ofPushMatrix();
    ofTranslate(mouseOffSetX + frameWidth, mouseOffSetY + frameHeight);
    upperRight.mirror(180, 0);
    upperRight.draw(0, 0, closestImages[animationIndex].mImg.getWidth(), closestImages[animationIndex].mImg.getHeight());
    //        animationIndex++;
    ofPopMatrix();
    
    // animate frame, bottom left
    ofPushMatrix();
    ofTranslate(mouseOffSetX, mouseOffSetY + frameHeight);
    upperRight.mirror(0, 180);
    upperRight.draw(0, 0, closestImages[animationIndex].mImg.getWidth(), closestImages[animationIndex].mImg.getHeight());
    animationIndex++;
    ofPopMatrix();
    
    cout << "animationIndex = " << animationIndex << endl;
    if(animationIndex > closestImages.size()-1)
        animationIndex = 0;

}

//------------------------------ mouse & key functions ---------------------------------//

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
        if(x >= mouseOffSetX && x <= mouseOffSetX + frameWidth && y>= mouseOffSetY && y <= mouseOffSetY + frameHeight){
            currPathPoint = ofVec2f(x - mouseOffSetX, y - mouseOffSetY); // click to make path points
            // cout << "currentPathPoint: " << currPathPoint << endl;
            
            currPath.push_back( currPathPoint );
            cout << "currPath: " << currPath.size() << endl;
        }
    }
    
    if (mode == 3){
        if (x >= mouseOffSetX && x <= mouseOffSetX + frameWidth && y>= mouseOffSetY && y <= mouseOffSetY + frameHeight){
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
    
    if(key == '5'){
        mode = 5;
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
    
    if (key == 'p'){
        mode = 5;
        drawImages(currPath);
        ofSetFrameRate(4);
        cout <<"P was pressed, drawImages" << endl;
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

//------------------------------- create JSON object -----------------------------------//

void testApp::writeJSON() {
    
    std::ofstream file;
    
    try{
        file.open("/Users/cvcarter/Documents/of_v0.8.0_osx_release/apps/thesis/restartMotion xml/bin/data/images.json", std::ofstream::out );
        
        std::string str = "[";
        
//        // get upper left corner
//        for(int i = 0; i<imageObjects.size(); i++){
//            str+= " { \"filename\" : \" "+ originalImageObjects[i].mName +" \", \"corner\" : { \"x\": \""+ ofToString(imageObjects[i].mCx) +" \" , \"y\": \" "+ ofToString(imageObjects[i].mCy) +" \" } } ";
//            if(i != imageObjects.size()-1) str+=",";
//            
//        }
        
        // get center x and y
        for(int i = 0; i<imageObjects.size(); i++){
            str+= " { \"filename\" : \" "+ originalImageObjects[i].mName +" \", \"center\" : { \"x\": \""+ ofToString(imageObjects[i].center.x) +" \" , \"y\": \" "+ ofToString(imageObjects[i].center.y) +" \" }, \"corner\" : { \"x\": \""+ ofToString(imageObjects[i].mCx) +" \" , \"y\": \" "+ ofToString(imageObjects[i].mCy) +" \" } } ";
            if(i != imageObjects.size()-1) str+=",";
            
        }

        str+="]";
        cout << "json data: " << str << endl;
        
        
        file<< str;
        file.close();
    }catch(std::exception e){
        std::cout<<"Exception: "<<e.what()<<endl;
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
    if (mode == 2){
        drawCurrImage(closestImageIndex);
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

//------------------------ load image object data one at a time -------------------------//

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