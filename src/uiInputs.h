//
//  uiInputs.h
//  openPixelMapper
//
//  Created by Tobias Ebsen on 14/03/14.
//
//

#pragma once

#include "ofxUI.h"

class uiInputs : public ofxUISuperCanvas {
public:
    
    uiInputs(float x, float y, float w, float h);
    
    void setup();

private:
    ofxUIImageToggle *inputChecker, *inputImage, *inputMovie, *inputWebcam, *inputSyphon;

};