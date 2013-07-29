//
//  Preview3DWindow.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 08.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "Preview3DWindow.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"
#include "cinder/app/App.h"

#include "CinderGwen.h"

using namespace Gwen;
using namespace ci;

Preview3DWindow::Preview3DWindow( Gwen::Controls::Base *parent )
: Controls::Base( parent, "Preview3DWindow" )
{
    
    SetMouseInputEnabled( true );
    
    mMouseDownCurrent = Vec2f::zero();
    mMouseDownOffset = Vec2f::zero();
    
    bMouseDown = false;
    bPreviewFboSet = false;
    mImageTemp = gl::Texture( loadImage( loadAsset( "images/logo_outline_white.png" ) ) );
    gl::Fbo::Format format;
//    format.enableDepthBuffer(false);
    mFboTemp = gl::Fbo(mImageTemp.getWidth(),mImageTemp.getHeight(),format);
    mFboTemp.getTexture().setFlipped(true);    
//    this->onPress.Add( this, &Preview3DWindow::onMousePress );
//    this->onPress.Add( this, &Preview3DWindow::onMousePressP );
}

Preview3DWindow::~Preview3DWindow()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Preview3DWindow::Render( Skin::Base* skin )
{
    
//    mLaserPreview3D->
//    mEyeNode.mAcc += Vec3f( posOffset.xy(), distFromCenter );
//    console() << " mMouseDownSmoothed : " << mMouseDownSmoothed << std::endl;

    
    mFboTemp.bindFramebuffer();
    gl::clear();
    gl::color(1, 1, 1);
    gl::draw( mImageTemp );
    mFboTemp.unbindFramebuffer();

    
    Vec2f pos( cigwen::fromGwen( LocalPosToCanvas() ) );
	ci::Rectf bounds( cigwen::fromGwen( GetBounds() ) );
	float aspect = (float)m_InnerBounds.w / (float)m_InnerBounds.h;
    
    gl::pushMatrices();
    
    float width = max( (float)mPreview3DFbo->getWidth(), bounds.getWidth());
    float height = max( (float)mPreview3DFbo->getHeight(), bounds.getHeight());
    
    if(aspect < 1){
        width /= aspect;
    }else{
        height *= aspect;
    }
    
	gl::translate( pos );
    gl::color( ci::Color( 0.1,0.1,0.1 ) );
    gl::drawSolidRect(Rectf(0,0,m_InnerBounds.w,m_InnerBounds.h));
    
    Vec2f offset(bounds.getWidth()-width,bounds.getHeight()-height);
	gl::translate( offset/2.0 );
        
    gl::disableAlphaBlending();
    if(bPreviewFboSet){
        gl::color( ci::Color( 1,1,1 ) );
        gl::draw( mPreview3DFbo->getTexture(0), Rectf(0,0,width,height) );
    }
    gl::enableAlphaBlending();
    
    gl::popMatrices();

}


void Preview3DWindow::RenderUnder( Skin::Base* skin )
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Preview3DWindow::setPreviewFbo(ci::gl::Fbo* fbo){
    mPreview3DFbo = fbo;
    bPreviewFboSet = true;
}

void Preview3DWindow::setLaserPreview3d( LaserPreview3D* laserPreview3D ){
    mLaserPreview3D = laserPreview3D;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Preview3DWindow::update(){
    
    Vec2f dist = mMouseDownOffset - mMouseDownCurrent;
    if(dist.length() > 10){
        mMouseDownSmoothed = lerp( mMouseDownSmoothed,dist,.04f );
//        Vec3f mLaserPreview3D->getCameraPosition()
//        console() << "mMouseDownSmoothed : " << mMouseDownSmoothed << std::endl;
    
        Vec3f cam = mCameraPositionOrg;
        cam.rotateX( toRadians(mMouseDownSmoothed.y / 10.0) );
        cam.rotateY( toRadians(mMouseDownSmoothed.x / 1.0) );
        mLaserPreview3D->setCameraPosition(cam);
        
//        mCameraPosition = mLaserPreview3D->getCameraPosition();
//        Quatf mQuat;
//        mQuat.set(mMouseDownSmoothed.x/1000.0, mMouseDownSmoothed.y/1000.0, 0);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Preview3DWindow::OnMouseMoved( int x, int y, int deltaX, int deltaY ){

    if(bMouseDown){
        mMouseDownCurrent = Vec2f(x,y);
//        Vec2f dist = mMouseDownOffset - Vec2f(x,y);
//        mCameraPosition = mLaserPreview3D->getCameraPosition();
//        mMouseDownSmoothed = lerp( mMouseDownSmoothed,dist,.04f );
//        
//        console() << "mMouseDownSmoothed : " << mMouseDownSmoothed << std::endl;
//        
//        Quatf mQuat;
//        mQuat.set(mMouseDownSmoothed.x/1000.0, mMouseDownSmoothed.y/1000.0, 0);
//        
////        mCameraPosition += Vec3f( mMouseDownSmoothed.xy(), -3.0 );
////        mLaserPreview3D->setCameraPosition( mCameraPosition + Vec3f( mMouseDownSmoothed.xy(), -3.0 ) );
    }
}

void Preview3DWindow::OnMouseClickLeft( int x, int y, bool bDown ) {
    bMouseDown = bDown;
    if(bMouseDown){
        mMouseDownOffset = Vec2f(x,y);
        mMouseDownSmoothed = Vec2f::zero();
        mCameraPositionOrg = mLaserPreview3D->getCameraPosition();
    }
}

void Preview3DWindow::OnMouseEnter(){
    bMouseDown = false;
}

void Preview3DWindow::OnMouseLeave(){
    bMouseDown = false;
}

void Preview3DWindow::OnMouseDoubleClickLeft( int x, int y ){
    mLaserPreview3D->resetView();
    mMouseDownOffset = Vec2f(x,y);
    mMouseDownSmoothed = Vec2f::zero();
    mCameraPositionOrg = mLaserPreview3D->getCameraPosition();
}




