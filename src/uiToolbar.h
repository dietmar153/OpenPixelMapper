//
//  uiToolbar.h
//  openPixelMapper
//
//  Created by Tobias Ebsen on 14/03/14.
//
//

#pragma once

#include "ofxUI.h"

class uiToolbar : public ofxUICanvas {
public:

    uiToolbar();

    void setup();
    void guiEvent(ofxUIEventArgs &e);
    
    string getWidgetDescription(string name);

private:
    ofxUIImageToggle *pointer, *move, *hand;
};