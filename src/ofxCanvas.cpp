//
//  ofxCanvas.cpp
//  openPixelMapper
//
//  Created by Tobias Ebsen on 11/03/14.
//
//

#include "ofxCanvas.h"

ofxCanvas::ofxCanvas() {
    scale = 1;
    x = 0;
    y = 0;
    width = 640;
    height = 480;
}

void ofxCanvas::begin() {
    ofPushView();
    int w = ofGetWindowWidth() / 2;
    int h = ofGetWindowHeight() / 2;
    ofTranslate(w, h);
    ofScale(scale, scale);
    ofTranslate(x, y);
    ofTranslate(-w, -h);
}

void ofxCanvas::end() {
    ofPopView();
}

void ofxCanvas::move(float x, float y) {
    this->x = x / scale;
    this->y = y / scale;
}

void ofxCanvas::zoom(float zoom) {
    //x = x - (zoom / 100. - scale) * (float)ofGetWindowWidth() / 2.;
    //y = y - (zoom / 100. - scale) * (float)ofGetWindowHeight() / 2.;
    //float inc = zoom / 100. - scale;
    //x -= (ofGetWindowWidth() * inc) / 2;
    //y -= (ofGetWindowHeight() * inc) / 2;
    //x += (x - (float)ofGetWindowWidth() / 2.) * scale;
    //y += (y - (float)ofGetWindowHeight() / 2.) * scale;
    this->scale = zoom / 100.;
}

void ofxCanvas::zoomIn() {
    zoom(scale * 200.);
}

void ofxCanvas::zoomOut() {
    zoom(scale * 50);
}

void ofxCanvas::resize(int width, int height) {
    this->width = width;
    this->height = height;
}

ofPoint ofxCanvas::pointToCanvas(int x, int y) {
    ofPoint p(x / scale - this->x , y / scale - this->y);
    return p;
}
