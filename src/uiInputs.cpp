//
//  uiInputs.cpp
//  openPixelMapper
//
//  Created by Tobias Ebsen on 14/03/14.
//
//

#include "uiInputs.h"

uiInputs::uiInputs(float x, float y, float w, float h) : ofxUISuperCanvas("INPUTS", x, y, w, h) {
}

void uiInputs::setup() {

    setColorBack(ofxUIColor::darkGray);
    setGlobalButtonDimension(24);
    setVisible(false);
    
    addSpacer();
    
    inputChecker = addImageToggle("Checkerboard", "Checkerboard.png", false);
    inputChecker->setLabelVisible(true);
    setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT, OFX_UI_ALIGN_RIGHT);
    ofxUIMinimalSlider *checkSize = addMinimalSlider("CheckerSize", 1, 40, 10, 140, 24);
    checkSize->setColorBack(ofxUIColor::lightGray);
    checkSize->setShowValue(false);
    checkSize->setLabelVisible(false);
    
    setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    addImageToggle("Image", "Picture.png", false)->setLabelVisible(true);
    setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT, OFX_UI_ALIGN_RIGHT);
    addLabelButton("BrowseImage", false, 140, 0)->setLabelText("Browse...");
    setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    inputMovie = addImageToggle("Movie", "Movie.png", false);
    inputMovie->setLabelVisible(true);
    setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT, OFX_UI_ALIGN_RIGHT);
    addLabelButton("BrowseMovie", false, 140, 0)->setLabelText("Browse...");
    setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    inputWebcam = addImageToggle("WebCam", "Video.png", false);
    inputWebcam->setLabelVisible(true);
    setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT, OFX_UI_ALIGN_RIGHT);
    addLabelToggle("Grabber", false, 140, 0)->setLabelText("Open");
    setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    inputSyphon = addImageToggle("Syphon", "Syphon.png", false);
    inputSyphon->setLabelVisible(true);
    setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT, OFX_UI_ALIGN_RIGHT);
    vector<string> ss;
    ofxUIDropDownList *servers = addDropDownList("Servers", ss, 140);
    servers->setLabelText("Select");
    servers->setShowCurrentSelected(true);
    servers->setAutoClose(true);
    servers->setAllowMultiple(false);
    ofxUIRectangle *rect = servers->getRect();
    rect->height = 24;
    
    autoSizeToFitWidgets();
}