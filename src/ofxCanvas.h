//
//  ofxCanvas.h
//  openPixelMapper
//
//  Created by Tobias Ebsen on 11/03/14.
//
//

#pragma once

#include "ofMain.h"

class ofxCanvas {
public:
    
    ofxCanvas();
    
    void begin();
    void end();
    
    void move(float x, float y);
    void zoom(float zoom);
    void zoomIn();
    void zoomOut();
    void resize(int width, int height);
    
    float getScale() { return scale; }
    float getX() { return x; }
    float getY() { return y; }
    
    int getWidth() { return width; }
    int getHeight() { return height; }
    
    void setWidth(int width) { this->width = width; }
    void setHeight(int height) { this->height = height; }
    
    ofPoint pointToCanvas(int x, int y);

private:
    float scale;
    float x, y;
    int width, height;
};