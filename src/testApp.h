#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxCanvas.h"
#include "ofxCheckerboard.h"
#include "ofxSyphonDraws.h"
#include "uiToolbar.h"
#include "uiInputs.h"
#include "ofxPixelMapper.h"

typedef enum _elementType {
    TYPE_INPUT,
    TYPE_PIXEL
} elementType;

class baseElement {
public:
    baseElement(elementType t, float w, float h) : type(t), visible(false), x(0), y(0), width(w), height(h) {}

    elementType type;
    bool visible;
    
    ofVec2f corner[4];
    
    float x;
    float y;
    float width;
    float height;
};

class inputElement : public baseElement {
public:
    inputElement(ofBaseVideoDraws* i, float w, float h) : baseElement(TYPE_INPUT, w, h), input(i) {}
    inputElement(ofBaseVideoDraws* i) : baseElement(TYPE_INPUT, i->getWidth(), i->getHeight()), input(i) {}
    ofBaseVideoDraws* input;
};

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    uiToolbar *guiToolbar;
    ofxUICanvas *guiStatus;
    ofxUILabel *labelStatus;
    uiInputs *guiInputs;
    ofxUISuperCanvas *guiOutputs;
    ofxUISuperCanvas *guiSettings;
    ofxUISuperCanvas *guiInfo;
    void guiEvent(ofxUIEventArgs &e);
    
    void syphonServerAnnounced(ofxSyphonServerDirectoryEventArgs &arg);
    void syphonServerUpdated(ofxSyphonServerDirectoryEventArgs &arg);
    void syphonServerRetired(ofxSyphonServerDirectoryEventArgs &arg);
    
    ofxCanvas canvas;
    ofPoint mouseDown;
    bool bIsMouseDown;
    
    ofxCheckerboard checkerboard;
    ofVideoGrabber grabber;
    ofVideoPlayer player;
    ofxSyphonDraws syphon;
    ofxSyphonServerDirectory syphonServers;
    
    map<string,baseElement*> elements;
    vector<baseElement*> selected;
    
    ofxPixelMapper mapper;
};
