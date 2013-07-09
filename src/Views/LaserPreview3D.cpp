//
//  LaserPreview3D.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 09.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "LaserPreview3D.h"

	
void LaserPreview3D::setup( ciilda::Frame* frame, int w, int h ){
    
	mCamera = CameraPersp( w, h, 60.0f, 0.0001f, 1000.0f );
	mCamera.lookAt( Vec3f( 0.0f, -5.0f, 0.0f ), Vec3f::zero() );
	mCameraPosition = Vec3f( 0.0f, 0.0f, -9.0f );
	mUp				= Vec3f::yAxis();
    mIldaFrame      = frame;
    
    gl::Fbo::Format format;
    //	format.setSamples( 2 ); // uncomment this to enable 4x antialiasing
	mPreview3DFbo = gl::Fbo( w, h, format );
    
    mTempRotation.setToIdentity();

}
	
void LaserPreview3D::update(){
	mCamera.lookAt( mCameraPosition, mTargetPosition, mUp );
    mTempRotation.rotate( Vec3f( 0.16666f, 0.333333f, 0.666666f ).normalized(), 0.01f );
	
}

void LaserPreview3D::draw(){
    
    ColorA clr;
    vector<ciilda::Point> points = mIldaFrame->getPoints();
    int l = points.size();
    float scale = 1.0/(float)kIldaMaxPoint;
    float clrScale = 1.0/(float)kIldaMaxIntensity;
    scale *= 5.0;
    
    mPreview3DFbo.bindFramebuffer();
    glPushAttrib( GL_VIEWPORT_BIT ); // *NEW*
    gl::setViewport( mPreview3DFbo.getBounds() );
    gl::pushMatrices();
    gl::setMatricesWindow( mPreview3DFbo.getSize(), false ); // *NEW*
	gl::clear( Color( .15, .1, .2 ) );
    gl::color( Color( 1, 1, 1 ) );
    
    gl::pushMatrices();
	gl::setMatrices( mCamera );

    gl::enableAlphaBlending();
//    gl::enable( GL_DEPTH_TEST );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    //    gl::enableAdditiveBlending();
    
    gl::multModelView( mTempRotation );
    gl::color(1, 1, 1);
    gl::drawCube( Vec3f::zero(), Vec3f(.2,.2,.2) );
    
    gl::pushMatrices();
    gl::scale( Vec3f(scale,scale,scale) );
    gl::color( ColorAf(1,1,1,.5) );
    gl::begin(GL_TRIANGLES);
    for(int i=0;i<l-1;i++){
        clr = ColorAf( points[i].r*clrScale, points[i].g*clrScale, points[i].b*clrScale, points[i].a*clrScale );
        gl::color( clr );
        gl::vertex( 0,0,0 );
        clr.a = 0;
        gl::color( clr );
        gl::vertex(points[i].x, points[i].y, -3/scale);
        gl::vertex(points[i+1].x, points[i+1].y, -3/scale);
    }
    gl::end();
    glDisable(GL_BLEND);
    gl::disable( GL_DEPTH_TEST );

    gl::popMatrices();
    gl::popMatrices();
    
    
    gl::popMatrices();
    glPopAttrib(); // *NEW*
    mPreview3DFbo.unbindFramebuffer();

    
//    gl::draw( mPreview3DFbo.getTexture() );
}

void LaserPreview3D::setTargetPosition(Vec3f vec){
    mTargetPosition = vec;
}

void LaserPreview3D::setCameraPosition(Vec3f vec){
	mCameraPosition = vec;
}

Vec3f LaserPreview3D::getCameraPosition(){
    return mCameraPosition;
}

Vec3f LaserPreview3D::getTargetPosition(){
    return mTargetPosition;
}

ci::gl::Fbo* LaserPreview3D::getTexture(){
    return &mPreview3DFbo;
}