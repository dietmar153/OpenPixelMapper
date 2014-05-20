//
//  ofxCheckerboard.h
//  openPixelMapper
//
//  Created by Tobias Ebsen on 13/03/14.
//
//

#pragma once

#include "ofMain.h"

class ofxCheckerboard : public ofImage, public ofBaseVideoDraws {
public:
    ofxCheckerboard() {
        ofImage();
        allocate(10, 10, OF_IMAGE_COLOR);
        setSize(10);
    }
    ~ofxCheckerboard() {}
    
    void setSize(int s) {
        ofImage::resize(s, s);
        ofImage::getTextureReference().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        unsigned char *pixels = this->getPixels();
        unsigned char p = 0;
        for (int y=0; y<ofImage::getHeight(); y++) {
            for (int x=0; x<ofImage::getWidth(); x++) {
                p = ~p;
                pixels[0] = p;
                pixels[1] = p;
                pixels[2] = p;
                pixels += 3;
            }
            p = ((y + 1) % 2) * 255;
        }
        ofImage::update();
    }
        
    // ofBaseUpdates
    virtual void update() {}
    
    // ofBaseVideo
	virtual bool isFrameNew() { return true; }
	virtual void close() {}
    
    //ofBaseDraws
	virtual void draw(float x, float y) { ofImage::draw(x, y); }
	virtual void draw(float x, float y, float w, float h) { ofImage::draw(x, y, w, h); }
	virtual float getHeight() { return ofImage::getHeight(); }
	virtual float getWidth() { return ofImage::getWidth(); }
    
    // ofHasTexture
	virtual ofTexture & getTextureReference() { return ofImage::getTextureReference(); }
	virtual void setUseTexture(bool bUseTex) { ofImage::setUseTexture(bUseTex); }
};