//
//  ofxSyphonDraws.h
//  openPixelMapper
//
//  Created by Tobias Ebsen on 13/03/14.
//
//

#pragma once
#include "ofxSyphonClient.h"

class ofxSyphonDraws : public ofxSyphonClient, public ofBaseVideoDraws {
public:
    ofxSyphonDraws() {}
    ~ofxSyphonDraws() {}

    // ofBaseHasPixels
    virtual unsigned char * getPixels() { return NULL; }
	virtual ofPixels_<unsigned char> & getPixelsRef() { ofPixels_<unsigned char> *ref = NULL; return *ref; }

    // ofBaseUpdates
    virtual void update() {}
    
    // ofBaseVideo
	virtual bool isFrameNew() { return true; }
	virtual void close() {}
    
    //ofBaseDraws
	virtual void draw(float x, float y) { ofxSyphonClient::draw(x, y); }
	virtual void draw(float x, float y, float w, float h) { ofxSyphonClient::draw(x, y, w, h); }
	virtual float getHeight() { return ofxSyphonClient::getHeight(); }
	virtual float getWidth() { return ofxSyphonClient::getWidth(); }

    // ofHasTexture
	virtual ofTexture & getTextureReference() { return mTex; }
	virtual void setUseTexture(bool bUseTex) {}
};