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
	bDataControllerSet = false;
    gl::Fbo::Format format;
    //	format.setSamples( 2 ); // uncomment this to enable 4x antialiasing
	mCircularDataFbo = gl::Fbo( w, h, format );
	mCircularDataStructureFbo = gl::Fbo( w, h, format );
}

void CircularDataLayer::setDataBuffer(Buffer* buffer){
	bDataBufferSet = true;
    mBuffer = buffer;
}

void CircularDataLayer::setDataController(DataController* d){
	bDataControllerSet = true;
    mDataController = d;
}

void CircularDataLayer::updateLayer(){
    mCircularDataFbo.bindFramebuffer();
    glPushAttrib( GL_VIEWPORT_BIT ); // *NEW*
    gl::pushMatrices();
    
    gl::setViewport( mCircularDataFbo.getBounds() );
    gl::setMatricesWindow( mCircularDataFbo.getSize(), false ); // *NEW*
//    gl::setMatricesWindow( Vec2f::one(), false ); // *NEW*
//	gl::clear( Color( 0,0,0 ) );
    gl::clear( Color( 0x13/255.0,0x14/255.0,0x13/255.0  ) );
    gl::color( Color( 1, 1, 1 ) );
    
    gl::draw( mCircularDataStructureFbo.getTexture() );
    
    gl::popMatrices();
    glPopAttrib(); // *NEW*
    mCircularDataFbo.unbindFramebuffer();
}

void CircularDataLayer::drawCircularDataStructure(int pos, int len){
    mCircularDataStructureFbo.bindFramebuffer();
    glPushAttrib( GL_VIEWPORT_BIT ); // *NEW*
    gl::pushMatrices();
    
    gl::setViewport( mCircularDataStructureFbo.getBounds() );
//    gl::setMatricesWindow( mCircularDataFbo.getSize(), false ); // *NEW*
    gl::setMatricesWindow( Vec2f::one(), false ); // *NEW*
	gl::clear( Color( 0x13/255.0,0x14/255.0,0x13/255.0  ) );
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
        radAdd /= 2.0;
        char* datas = (char*)mBuffer->getData();

        gl::begin(GL_LINE_STRIP);
        for(float i=0;i<amount;i++){
            ir += circAngle;
            
            char d = *(datas+(int)i)-'A'+30;
            clr = (d*2) / 255.0;// mRandom.nextFloat(1.0f);
//            if(i<100) console() << i << " -> " << clr << std::endl;
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
    mCircularDataStructureFbo.unbindFramebuffer();
}

gl::Fbo* CircularDataLayer::getTexture(){
    return &mCircularDataFbo;
}