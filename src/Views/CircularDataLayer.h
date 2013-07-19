//
//  CircularDataLayer.h
//  QLT_GenomeLaser
//
//  Created by say nono on 18.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "cinder/app/AppBasic.h"
#include "cinder/gl/Fbo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CircularDataLayer{

public:
	
	void setup(int w, int h);
    void setDataBuffer(Buffer* buffer);
	void updateLayer(int pos, int len);
    gl::Fbo* getTexture();
    
private:
    
    bool                bDataBufferSet;
	Buffer*             mBuffer;
    gl::Fbo             mCircularDataFbo;
    ci::Rand            mRandom;
};



