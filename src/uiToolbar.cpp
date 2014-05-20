//
//  uiToolbar.cpp
//  openPixelMapper
//
//  Created by Tobias Ebsen on 14/03/14.
//
//

#include "uiToolbar.h"

uiToolbar::uiToolbar() : ofxUICanvas() {
}

void uiToolbar::setup() {

    setGlobalButtonDimension(24);
    setColorBack(ofxUIColor::darkGray);
    
    setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    pointer = addImageToggle("Pointer", "Pointer.png", true);
    move = addImageToggle("Move", "Directions.png", false);
    addImageToggle("Resize", "Direction Diag2.png", false);
    
    addSpacer(10, 0);
    
    hand = addImageToggle("Hand", "Hand.png", false);
    addImageButton("ZoomIn", "Zoom In.png", false);
    addImageButton("ZoomOut", "Zoom Out.png", false);
    addImageButton("Reset", "Home2.png", false);
    
    addSpacer(10, 0);
    
    addImageToggle("Inputs", "Go In.png", false);
    addImageToggle("Outputs", "Go Out.png", false);
    addImageToggle("Settings", "Gear.png", false);
    addImageToggle("Info", "Info2.png", false);
    
    addSpacer(10, 0);
    
    addImageToggle("FullScreen", "FullScreen.png", false);
    autoSizeToFitWidgets();
    
    ofAddListener(newGUIEvent, this, &uiToolbar::guiEvent);
}

void uiToolbar::guiEvent(ofxUIEventArgs &e) {
    
    string name = e.getName();

    if (name == "Pointer") {
        move->setValue(false);
        hand->setValue(false);
    }
    if (name == "Move") {
        pointer->setValue(false);
        hand->setValue(false);
    }
    if (name == "Hand") {
        pointer->setValue(false);
        move->setValue(false);
    }
}

string uiToolbar::getWidgetDescription(string name) {

    if (name == "Pointer")
        return "Pointer / Select";
    else if (name == "Move")
        return "Move";
    else if (name == "Resize")
        return "Resize";
    else if (name == "Hand")
        return "Hand tool / Move view";
    else if (name == "ZoomIn")
        return "Zoom in";
    else if (name == "ZoomOut")
        return "Zoom out";
    else if (name == "Reset")
        return "Reset view";
    else if (name == "Inputs")
        return "Show inputs menu";
    else if (name == "Outputs")
        return "Show outputs menu";
    else if (name == "Info")
        return "Show info menu";
    else if (name == "FullScreen")
        return "Go full screen";
    else
        return name;

    return "";
}