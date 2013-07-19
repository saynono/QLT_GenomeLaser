//
//  CircularDataLayer.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 18.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "CircularDataLayer.h"

	
void CircularDataLayer::setup(int w, int h){
    bDataBufferSet = false;
    gl::Fbo::Format format;
    //	format.setSamples( 2 ); // uncomment this to enable 4x antialiasing
	mCircularDataFbo = gl::Fbo( w, h, format );
    
}

void CircularDataLayer::setDataBuffer(Buffer* buffer){
	bDataBufferSet = true;
    mBuffer = buffer;
}

void CircularDataLayer::updateLayer(int pos, int len){    
    mCircularDataFbo.bindFramebuffer();
    glPushAttrib( GL_VIEWPORT_BIT ); // *NEW*
    gl::pushMatrices();
    
    gl::setViewport( mCircularDataFbo.getBounds() );
//    gl::setMatricesWindow( mCircularDataFbo.getSize(), false ); // *NEW*
    gl::setMatricesWindow( Vec2f::one(), false ); // *NEW*
	gl::clear( Color( .1, .1, .14 ) );
    gl::color( Color( 1, 1, 1 ) );
    
    gl::pushMatrices();
    gl::translate( Vec2f::one()/2.0 );
//    gl::color( Color( 1, 1, 0 ) );
//    gl::drawSolidRect( Rectf(-.45,-.45,.9,.9) );
    
    
    if(bDataBufferSet){
        float rad = .45;
        float clr;
        float ir = 0;
        int amount = 100000;
        int circles = 200;
        float circAngle = (circles * (M_PI*2)) / (float)amount;
        float radAdd = rad / (float)amount;
        char* datas = (char*)mBuffer->getData();

        gl::begin(GL_LINE_STRIP);
        for(float i=0;i<amount;i++){
            ir += circAngle;
            
            char d = *(datas+(int)i)-'A'+30;
            clr = (d*2) / 255.0;// mRandom.nextFloat(1.0f);
            if(i<100) console() << i << " -> " << clr << std::endl;
            gl::color( Color( clr,clr,clr ) );
            gl::vertex(sin(ir)*rad,cos(ir)*rad);
            rad -= radAdd;//(((int)(i/360))/1000.0f);
        }
        gl::end();        
    }
//    gl::color(.4, .4, .9);
//    gl::drawCube( Vec3f::zero(), Vec3f(.05,.05,.05) );

    gl::popMatrices();

    gl::popMatrices();
    glPopAttrib(); // *NEW*
    mCircularDataFbo.unbindFramebuffer();   
}

gl::Fbo* CircularDataLayer::getTexture(){
    return &mCircularDataFbo;
}