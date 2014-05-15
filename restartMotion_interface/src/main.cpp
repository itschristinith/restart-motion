#include "testApp.h"

int main() {
//	ofSetupOpenGL(1024, 768, OF_WINDOW);
    ofSetupOpenGL(1280, 800, OF_WINDOW);
    cout << ofGetHeight()<< endl;
	ofRunApp(new testApp());
}
