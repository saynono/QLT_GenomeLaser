//
//  LaserPreview3D.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 09.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "LaserPreview3D.h"

	
void LaserPreview3D::setup( int w, int h ){
    
    mLaserAngle = 90;
    
    mPov			= POV( cinder::app::App::get() , ci::Vec3f( 0.0f, 0.0f, 10.0f ), ci::Vec3f( 0.0f, 0.0f, 0.0f ) );
    
	mCamera = CameraPersp( w, h, 60.0f, 0.0001f, 1000.0f );
	mCamera.lookAt( Vec3f( 0.0f, -1.0f, 0.0f ), Vec3f::zero() );
	mCameraPosition = Vec3f( 0.0f, 0.0f, -3.0f );
	mUp				= Vec3f::yAxis();
    
    gl::Fbo::Format format;
    format.setSamples( 4 ); // uncomment this to enable 4x antialiasing
	mPreview3DFbo = gl::Fbo( w, h, format );
    
    mTempRotation.setToIdentity();
    mTempRotation.rotate( Vec3f( 0.0f, 0.0f, 1.0f ).normalized(), toRadians(-90.0f) );
    mTempRotation *= Quatf( Vec3f( 0.0f, 1.0f, 0.0f ).normalized(), toRadians(-90.0f) );

    paramsView.showFrame = true;
    paramsView.showDotsOnGauze = true;
    paramsView.showLinesOnGauze = true;
    paramsView.showRays = false;
    paramsView.showFans = true;
    paramsView.fansIntensity = .8f;


}
	
void LaserPreview3D::update(){
	mCamera.lookAt( mCameraPosition, mTargetPosition, mUp );
//    calculateDotsOnGauze(ciilda::Frame* frame);
}

void LaserPreview3D::draw(){
    
    Vec3f centerOfSpace(0,0,-.5);
    
    mPreview3DFbo.bindFramebuffer();
    glPushAttrib( GL_VIEWPORT_BIT );
    gl::setViewport( mPreview3DFbo.getBounds() );
    gl::pushMatrices();
    gl::setMatricesWindow( mPreview3DFbo.getSize(), false );
	gl::clear( Color( 0x13/255.0,0x14/255.0,0x13/255.0  ) );
    gl::color( Color( 1, 1, 1 ) );
    
    gl::pushMatrices();
	gl::setMatrices( mCamera );
    
    gl::multModelView( mTempRotation );

    gl::translate( -centerOfSpace );
    
    float scale = 1.45f;
    gl::scale( scale,scale,scale );
    
    gl::enableAlphaBlending();

    if(paramsView.showFrame){
        gl::color( ColorAf(1,1,1,.4) );
        glLineWidth(3);
        gl::drawLine( Vec3f(0,0,.2), Vec3f::zero());
        glLineWidth(1);
        gl::color( ColorAf(.5,.5,.5,.8) );
        gl::drawSphere( Vec3f::zero(), .05f, 90 );
        gl::drawStrokedCircle( Vec2f::zero(), 1.0f, 90 );
        gl::drawStrokedCube( centerOfSpace, Vec3f(2,2,1) );
    }
    
    if(paramsView.showDotsOnGauze) drawLaserDotsOnGauze();
    if(paramsView.showLinesOnGauze) drawLaserLinesOnGauze(.5);
    if(paramsView.showRays) drawLaserRays(.2);
    if(paramsView.showFans) drawLaserFans(paramsView.fansIntensity);
//    if(paramsView.showFans) drawLaserFansTest(paramsView.fansIntensity);
    
    gl::popMatrices();
    
    
    gl::popMatrices();
    glPopAttrib(); // *NEW*
    mPreview3DFbo.unbindFramebuffer();

    
//    gl::draw( mPreview3DFbo.getTexture() );
}

void LaserPreview3D::drawLaserDotsOnGauze(){
    Vec3f point3d;
    ColorA clr;
    int l = mGauzeDots.size();
    glPointSize(2);
    gl::begin(GL_POINTS);
    for(int i=0;i<l;i++){
        gl::color( mGauzeDots[i].clr );
        gl::vertex( mGauzeDots[i].vec );
    }
    gl::end();
    glPointSize(1);
}

void LaserPreview3D::drawLaserLinesOnGauze(float alpha){
    Vec3f point3d;
    ColorA clr;
    int l = mGauzeDots.size();
    
    gl::enableAlphaBlending();
    
    gl::begin(GL_LINE_LOOP);
    for(int i=0;i<l;i++){
        clr = mGauzeDots[i].clr;
        if(clr.length()==0) clr = ColorA(.5,0,0,alpha);
//        clr.r = .5;
//        clr.a = alpha;
        gl::color( clr );
        gl::vertex( mGauzeDots[i].vec );
    }
    gl::end();
    
    glDisable(GL_BLEND);
}

void LaserPreview3D::drawLaserRays(float alpha){
    Vec3f point3d;
    ColorA clr;
    int l = mGauzeDots.size();
    
    gl::enableAlphaBlending();
    
    gl::begin(GL_LINE_STRIP);
    for(int i=0;i<l;i++){
        clr = mGauzeDots[i].clr;
        clr.a *= alpha;
        gl::color( clr );
        gl::vertex( Vec3f::zero() );
        gl::vertex( mGauzeDots[i].vec );
    }
    gl::end();
    
    glDisable(GL_BLEND);
}

void LaserPreview3D::drawLaserFansTest(float alpha){
    
    Vec3f point3d;
    ColorA clr;
    int l = mGauzeDots.size();
    
    //    gl::enableAlphaBlending();
    gl::disableAlphaBlending();
    //    gl::enable( GL_DEPTH_TEST );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    gl::begin(GL_TRIANGLE_FAN);
    gl::color( ColorAf(1,1,1,alpha) );
    gl::vertex( 0,0,0 );
    for(int i=0;i<l;i++){
        gl::color( ColorAf::black() );
        gl::vertex( mGauzeDots[i].vec * .9 );
    }
    gl::end();
    
    glDisable(GL_BLEND);
    gl::disable( GL_DEPTH_TEST );
    gl::enableAlphaBlending();
    
}

void LaserPreview3D::drawLaserFans(float alpha){

    Vec3f point3d;
    ColorA clr;
    int l = mGauzeDots.size();
    
//    gl::enableAlphaBlending();
    gl::disableAlphaBlending();
    //    gl::enable( GL_DEPTH_TEST );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    gl::begin(GL_TRIANGLES);
    for(int i=0;i<l-1;i++){
        clr = mGauzeDots[i].clr;
        clr *= clr.a * alpha;
        point3d = mGauzeDots[i].vec * .9;
        gl::color( clr );
        gl::vertex( 0,0,0 );
//        clr.a = 0;
        clr = ColorA::black();
        gl::color( clr );
        gl::vertex( point3d );
        clr = ColorA::black();
//        clr = mGauzeDots[(i+1)%l].clr;
//        clr *= clr.a * alpha;
//        clr.a = 0;
        point3d = mGauzeDots[(i+1)%l].vec * .9;
        gl::color( clr );
        gl::vertex( point3d );        
    }
    gl::end();
    
    glDisable(GL_BLEND);
    gl::disable( GL_DEPTH_TEST );
    gl::enableAlphaBlending();
}

void LaserPreview3D::calculateDotsOnGauze( ciilda::Frame* frame){
    
    float scale = 1.0/((float)kIldaMaxPoint*frame->params.output.transform.scale.x);
    float clrScale = 1.0/(float)kIldaMaxIntensity;
    Vec3f pointRay( 0,0,-1 );
    Vec3f point3d;
    Vec3f pointScale3d;
    Vec3f pNow,pBefore;
    float px,py;
    ColorA clr;
    vector<ciilda::Point> points = frame->getPoints();
    int l = points.size();
    float angleProj = scale*mLaserAngle/90.0;
    float a1,a2;
    
    mGauzeDots.clear();

    for(int i=0;i<l-1;i++){
        px = points[i].x;
        py = points[i].y;
        clr = ColorAf( points[i].r*clrScale, points[i].g*clrScale, points[i].b*clrScale, points[i].a*clrScale );
        a1 = toRadians((Vec2f(px,py)*angleProj).length()*90);
        a2 = atan2(px,py);
        point3d = pointRay;
        point3d.rotateY(a1);
        point3d.rotateZ(a2);
        GauzeDots gd;
        gd.vec = point3d;
        gd.clr = clr;
        mGauzeDots.push_back(gd);
    }
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

void LaserPreview3D::resetView(){
    mCameraPosition = Vec3f( 0.0f, 0.0f, -3.0f );
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
