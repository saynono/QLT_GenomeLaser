//
//  LaserPreview3D.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 09.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "LaserPreview3D.h"

	
void LaserPreview3D::setup( ciilda::Frame* frame, int w, int h ){
    
    mLaserAngle = 60;
    
	mCamera = CameraPersp( w, h, 60.0f, 0.0001f, 1000.0f );
	mCamera.lookAt( Vec3f( 0.0f, -1.0f, 0.0f ), Vec3f::zero() );
	mCameraPosition = Vec3f( 0.0f, 0.0f, -9.0f );
	mUp				= Vec3f::yAxis();
    mIldaFrame      = frame;
    
    gl::Fbo::Format format;
    //	format.setSamples( 2 ); // uncomment this to enable 4x antialiasing
	mPreview3DFbo = gl::Fbo( w, h, format );
    
    mTempRotation.setToIdentity();
//    mQuat.g

}
	
void LaserPreview3D::update(){
	mCamera.lookAt( mCameraPosition, mTargetPosition, mUp );
    mTempRotation.rotate( Vec3f( 0.16666f, 0.333333f, 0.666666f ).normalized(), 0.01f );
//	mTempRotation *= mQuat;
}

void LaserPreview3D::draw(){
    
    float scale = 1.0/(float)kIldaMaxPoint;
    float clrScale = 1.0/(float)kIldaMaxIntensity;
    scale *= 5.0;
    Vec3f pointRay( 0,0,-3 );
    Vec3f point3d;
    Vec3f pointScale3d;
    float angleLaser = toRadians( mLaserAngle / 2.0 );
    ColorA clr;
    vector<ciilda::Point> points = mIldaFrame->getPoints();
    int l = points.size();
    
    pointScale3d.x = toRadians( angleLaser/2.0f );
    pointScale3d.y = pointScale3d.x;
    pointScale3d.z = 1.0;
    
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
//    gl::scale( Vec3f(scale,scale,scale) );
    gl::color( ColorAf(1,1,1,.5) );
    
//    gl::lineWidth(5);
//    point3d = pointRay;
//    gl::drawLine(Vec3f( 0,0,0 ), point3d);
//
//    point3d = pointRay;
//    point3d.rotate( Vec3f(1,1,0), angleLaser );
//    gl::drawLine(Vec3f( 0,0,0 ), point3d);
//
//    point3d = pointRay;
//    point3d.rotateX( angleLaser );
//    gl::drawLine(Vec3f( 0,0,0 ), point3d);

    gl::begin(GL_TRIANGLES);
    for(int i=0;i<l-1;i++){
        clr = ColorAf( points[i].r*clrScale, points[i].g*clrScale, points[i].b*clrScale, points[i].a*clrScale );
        gl::color( clr );
        gl::vertex( 0,0,0 );
        clr.a = 0;
        gl::color( clr );
        
        point3d = pointRay;
        point3d.rotate( Vec3f(points[i].x,points[i].y,0)*scale, angleLaser );
        point3d.normalize();
        gl::vertex( point3d );
        
        point3d = pointRay;
        point3d.rotate( Vec3f(points[i+1].x,points[i+1].y,0)*scale, angleLaser );
        point3d.normalize();
        gl::vertex( point3d );
        
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

int LaserPreview3D::getLaserAngle(){
    return mLaserAngle;
}

void LaserPreview3D::setLaserAngle(int a){
    mLaserAngle = a;
}
