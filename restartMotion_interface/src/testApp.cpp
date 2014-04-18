#include "testApp.h"


using namespace ofxCv;
using namespace cv;

void testApp::setup() {
    
    
    bg.loadImage("shapes.png");
	trackingColorMode = TRACK_COLOR_HSV;
    
    threshold = 100;
    minAreaValue = 0;
    maxAreaValue =100;
    mode = 0;
    frameWidth = 320;
    frameHeight = 240;
    currPathPoint = ofVec2f(-2000, -2000);
    currPoint = ofVec2f(-2000, -2000);

    vector<string> ddmodes;
    ddmodes.push_back("DEMO MODE");
    ddmodes.push_back("DRAW MODE");
    
    myfont.loadFont("GUI/LetterGothicStd.otf", 32);
    myfontS.loadFont("GUI/LetterGothicStd-Slanted.otf", 32);
    myfontB.loadFont("GUI/LetterGothicStd-Bold.otf", 32);
    myfontSB.loadFont("GUI/LetterGothicStd-BoldSlanted.otf", 32);
    ofEnableAlphaBlending();
    
    gui = new ofxUICanvas(2, 5, ofGetWidth() *0.3, ofGetHeight() * 0.2);
    gui->setFont("GUI/LetterGothicStd.otf");
//    gui->setPosition(2, 5);
    gui->setTheme(29); //OFX_UI_THEME_RUSTICORANGE use with ofBackground(33, 46, 48, 10);//dark blue
    
//    ddmode = gui->addDropDownList("SELECT MODE", ddmodes);
//    ddmode->setAllowMultiple(false);
//    ddmode->setAutoClose(false);
    gui->addWidgetDown(new ofxUILabel("SELECT MODE", OFX_UI_FONT_LARGE));
    gui->addSpacer();
    gui->addRadio("Mode", ddmodes, OFX_UI_ORIENTATION_VERTICAL);
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    
    vector<string>output;
    output.push_back("GENERATE SINGLE FRAME");
    output.push_back("GENERATE PATTERN");
    
    gui2 = new ofxUICanvas(2, 0, ofGetWidth() *0.6, ofGetHeight());
    gui2->setFont("GUI/LetterGothicStd.otf");
    gui2->setTheme(29);
    gui2->addTextArea("instructions", "Draw a path of points in the frame above. Then click below to see your animation in a single frame or as a pattern.");
    gui2->addSpacer();
    gui2->addRadio("Output", output, OFX_UI_ORIENTATION_VERTICAL);
    gui2->addButton("NEW PATH", false);
//    gui2->autoSizeToFitWidgets();
    gui2->setVisible(false);
    
    ofAddListener(gui2->newGUIEvent,this,&testApp::guiEvent);
    
//    gui2->addButton("GENERATE FRAMES", false);
//    gui2->addButton("GENERATE PATTERN", false);
//    gui2->addButton("NEW PATH", false);

    
//    gui->addToggle("DEMO MODE", true);
//    gui->addToggle("DRAW MODE", false);

//    gui->addWidgetEastOf(new ofxUIToggle("DRAW MODE", false, false, false), "DEMO MODE");
//    toggle = gui->addToggleMatrix("MODE", 1, 2, "Draw", "Demo");
//    toggle->setAllowMultiple(false);
//    gui->addWidgetEastOf(gui->addToggle("DRAW MODE", false), "DEMO MODE");
//    gui->addToggle("SHOW ACTIVE", false);
    
//    ddl = gui->addDropDownList("DYNAMIC DROP DOWN", modes);
//    ddl->setAllowMultiple(false);
//    ddl->setAutoClose(true);
    
//    gui->setDrawWidgetPadding(true);
//    ofAddListener(gui->newGUIEvent, this, &ofApp::guiEvent);
//    gui->addSlider("CONT THRESHOLD", 0, 255, &threshold);
//    gui->addMinimalSlider("MIN AREA", 0.0, 100.0, &minAreaValue);
//    gui->addMinimalSlider("MAX AREA", 0.0, 100.0, &maxAreaValue);
//    gui->addSpacer();
//    gui->addImage("SAMPLE COLOUR", &sampleColor, 10, 10);
    
    loadImgsFromDir();
        
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
    mouseOffSetX = (ofGetWidth() - frameWidth)*0.5;
    mouseOffSetY = (ofGetHeight() - frameHeight*2)*0.5;
    
//    //adjust size of frame if in mode 3 and therefore mode 4
//    if (mode == 3){
//        frameWidth = 640;
//        frameHeight = 480;
//    }

}

void testApp::draw() {
//    ofBackground(220, 174, 154); //beige
//    ofBackground(114, 112, 136); //blue
      ofBackground(33, 46, 48, 100);//dark blue
//    ofBackground(103, 147, 142, 40);//light blue
//    ofBackground(244, 236, 93); //yellow
//    ofBackgroundGradient(ofColor::gray, ofColor::black);
    
//    ofPushStyle();
//    ofSetColor(255,255,255, 50);
//    bg.draw(50, 50, bg.getWidth(), bg.getHeight());
//    ofPopStyle();
    
    ofPushStyle();
    ofSetColor(211, 84, 40, 255);//orange
    ofFill();
    myfontB.drawString("RESTART", ofGetWidth()/2-150, 37);
    myfontS.drawString("MOTION", ofGetWidth()/2+30, 37);
    ofPopStyle();
    
    if(mode == 0){ //load data
//        loadingImageObjectData();
    }
    
    if(mode == 1){
   
    }
    
    if(mode == 2){ //pick one image at a time
        ofPushMatrix();
        ofTranslate(0, ofGetHeight()-300);
        
//        ofTranslate(ofGetWidth()*.2, 0); //for poster
        drawImageTiles();
        ofPopMatrix();
        
        drawRect();
        drawImages(currPathPoint);
        
    }
    
    if(mode == 3){ //set a path to select multiple images at once
        // draw rect and each point to visualize location
        drawRect();
        drawPath(0, 0, 0);
        ofPushStyle();
        ofSetColor(0, 0, 255);
        ofFill();
        
        line.draw();
        ofPopStyle();
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
        
        // draw points in diff color to visualize path
//        drawAnimatedPoints(255, 0, 0);
    }
    
    if (mode == 5){
        generatePattern();
    }
//for poster
//    ofPushStyle();
//    ofSetColor(211, 84, 40, 255);//orange
//    ofFill();
//    myfontB.drawString("RESTART", ofGetWidth()/2-160, ofGetHeight()*.5);
//    myfontS.drawString("MOTION", ofGetWidth()/2+20, ofGetHeight()*.5);
//    ofPopStyle();

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
//for poster
//void testApp::drawImageTiles(){
//    
//    row = 12;
//    col = 9;
//    gridWidth = ofGetWidth()*.6 / col;
//    gridHeight = ofGetHeight() / row;
//    
//    
//    for (int i = 0; i < row; i++) {
//        for (int j = 0; j < col; j++) {
//            index = j + i * col;
//            ofPushStyle();
//            ofSetColor(255, 255, 255, 75);
//            tile = mOriginalImages[index];
//            tile.draw(j*gridWidth, i*gridHeight, gridWidth, gridHeight);
//            //            cout << index << " -- (" << i << "," << j << ")  -- " << gridWidth << "," << gridHeight << endl;
//            ofPopStyle();
//        }
//    }
//}

void testApp::drawImageTiles(){
    
    row = 5;
    col = 23;
    gridWidth = ofGetWidth() / col;
    gridHeight = 300 / row;
    
    
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            index = j + i * col;
            ofPushStyle();
            ofSetColor(255, 255, 255, 100);
            tile = mOriginalImages[index];
            tile.draw(j*gridWidth, i*gridHeight, gridWidth, gridHeight);
//            cout << index << " -- (" << i << "," << j << ")  -- " << gridWidth << "," << gridHeight << endl;
            ofPopStyle();
        }
    }
}

void testApp::highlightSelectedImg(int selectedImg) {
    int indexWidth = selectedImg%23; //equivalent of j
    int indexHeight = ceil(selectedImg/23); //equivalent of i
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            
            ofPushMatrix();
            ofTranslate(0, ofGetHeight()-300);
            mOriginalImages[selectedImg].draw(indexWidth*gridWidth - gridWidth*.15, indexHeight*gridHeight - gridHeight*0.15, gridWidth*1.3, gridHeight*1.3);
            ofPushStyle();
            ofNoFill();
            ofSetColor(255, 0, 0);
            ofRect(indexWidth*gridWidth - gridWidth*.15, indexHeight*gridHeight - gridHeight*0.15, gridWidth*1.3, gridHeight*1.3);
            ofPopStyle();
            ofPopMatrix();
        }
    }

}

//void testApp::poster(){
//    
//    row = 15;
//    col = 23;
//    gridWidth = ofGetWidth() / col;
//    gridHeight = ofGetHeight() / row;
//    
//    
//    for (int i = 0; i < row; i++) {
//        for (int j = 0; j < col; j++) {
//            index = j + i * col;
//            ofPushStyle();
//            ofSetColor(255, 255, 255, 100);
//            tile = mOriginalImages[index];
//            tile.draw(j*gridWidth, i*gridHeight, gridWidth, gridHeight);
//            //            cout << index << " -- (" << i << "," << j << ")  -- " << gridWidth << "," << gridHeight << endl;
//            ofPopStyle();
//        }
//    }
//}


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
    ofSetColor(255, 255, 200, 150);
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
    ofTranslate(mouseOffSetX-frameWidth/2, mouseOffSetY);
    closestImages[animationIndex].mImg.draw(0, 0, closestImages[animationIndex].mImg.getWidth(), closestImages[animationIndex].mImg.getHeight());
    //        animationIndex++;
    ofPopMatrix();
    
    // animate frame, upper right
    ofPushMatrix();
    ofTranslate(mouseOffSetX + frameWidth/2, mouseOffSetY);
    ofImage upperRight = closestImages[animationIndex].mImg;
    
    upperRight.mirror(0, 180);
    upperRight.draw(0, 0, closestImages[animationIndex].mImg.getWidth(), closestImages[animationIndex].mImg.getHeight());
    //        animationIndex++;
    ofPopMatrix();
    
    // animate frame, bottom right
    ofPushMatrix();
    ofTranslate(mouseOffSetX + frameWidth/2, mouseOffSetY + frameHeight);
    upperRight.mirror(180, 0);
    upperRight.draw(0, 0, closestImages[animationIndex].mImg.getWidth(), closestImages[animationIndex].mImg.getHeight());
    //        animationIndex++;
    ofPopMatrix();
    
    // animate frame, bottom left
    ofPushMatrix();
    ofTranslate(mouseOffSetX-frameWidth/2, mouseOffSetY + frameHeight);
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

void testApp::mouseDragged(int x, int y, int button){
    if (mode == 3){
        ofPolyline line;

        if (x >= mouseOffSetX && x <= mouseOffSetX + frameWidth && y>= mouseOffSetY && y <= mouseOffSetY + frameHeight){
            
            vector<ofPoint> verts;
            verts.push_back(ofPoint(x - mouseOffSetX, y - mouseOffSetY));
//                        line.addVertices(verts);
            
        }
//        line.draw();
        
        cout << "polyLine: " << &line.getVertices() << endl;

    }

}

void testApp::mouseReleased(int x, int y, int button){
    line.addVertices(verts);
    line.close();
    cout << "mouseReleased" << endl;
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
    highlightSelectedImg(closestImageIndex);
     return originalImageObjects[closestImageIndex];
}

void testApp::drawImages(ofVec2f currPathPoint){
    // to search one point at a time
    ObjectData closestImage = closestImageToPoint(currPathPoint);
    ofPushMatrix();
    ofTranslate(mouseOffSetX, mouseOffSetY);
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
	
    if (name == "SHOW ACTIVE"){
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        ddl->setShowCurrentSelected(toggle->getValue());
    }
    
    else if (name == "SELECT MODE"){
        ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
        vector<ofxUIWidget *> &selected = ddlist->getSelected();
        
            }
    
    else if (name == "DEMO MODE"){
        mode = 2;
        gui2->setVisible(false);
    }
    
    else if (name == "DRAW MODE"){
        mode = 3;
        gui2->setVisible(true);
        gui2->setPosition(2, mouseOffSetY);
    }
    
    else if (name == "GENERATE SINGLE FRAME"){
        if (currPath.size() == 0){
            mode = 3;
        }
        else {
            
        mode = 4;
        drawImages(currPath);
        ofSetFrameRate(4);
        }
    }
    
    else if (name == "GENERATE PATTERN"){
        if (currPath.size() == 0){
            mode = 3;
        }
        else {
        mode = 5;
        drawImages(currPath);
        ofSetFrameRate(4);
        }
    }
    
    else if (name == "NEW PATH"){
        currPath.clear();
        mode = 3;
    }


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
    delete gui2;
}