//
//  PreviewWindow.cpp
//  LaserGateway
//
//  Created by say nono on 18.03.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "PreviewWindow.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"
#include "cinder/app/App.h"

#include "CinderGwen.h"

using namespace Gwen;
using namespace ci;

PreviewWindow::PreviewWindow( Gwen::Controls::Base *parent )
: Controls::Base( parent, "cigwen sample CustomControl" )
{
    bPreviewFboSet = false;
}

PreviewWindow::~PreviewWindow()
{
	app::console() << "CustomControl destroyed." << std::endl;
}




void PreviewWindow::Render( Skin::Base* skin )
{
	Vec2f pos( cigwen::fromGwen( LocalPosToCanvas() ) );
	ci::Rectf bounds( cigwen::fromGwen( GetBounds() ) );
	float aspect = (float)m_InnerBounds.w / (float)m_InnerBounds.h;
    
//	mCubeRotation.rotate( Vec3f( 1, 1, 1 ), 0.03f );
//    
//	gl::pushMatrices();
//    
//	gl::translate( pos );
//	float yOffset = 10;
//	float yHeight = 20;
//	gl::drawString( std::string( "pos: " ) + ci::toString( pos ), Vec2f( 10, yOffset ), ci::Color::black() );		yOffset += yHeight;
//	gl::drawString( std::string( "bounds: " ) + ci::toString( bounds ), Vec2f( 10, yOffset ), ci::Color::black() );		yOffset += yHeight;
//	gl::drawString( std::string( "aspect: " ) + ci::toString( aspect ), Vec2f( 10, yOffset ), ci::Color::black() );		yOffset += yHeight;
//    
//	static float rot = 0;
//	rot += 0.5f;
//    
//	float w = 40;
//	Rectf r( -w, -w, w, w );
//    
//	gl::translate( bounds.getCenter() );
//	gl::rotate( rot );
//	gl::color( ci::Color( 0, 0.8, 0 ) );
//	gl::drawSolidRect( r );
//	gl::color( ci::Color( 0, 0, 0.8 ) );
//	gl::drawStrokedRect( r );
//    
//	//----------------------
//	// TODO: draw cube
//    
//    //	gl::pushMatrices();
//    
//    //	gl::enableDepthRead();
//    //
//    //	mCamera.lookAt( Vec3f( 1, 1, -5 ), Vec3f::zero() );
//    //	mCamera.setPerspective( 60, aspect, 1, 1000 );
//    //
//    //	gl::setMatrices( mCamera );
//    //	gl::multProjection( mCamera.getProjectionMatrix() );
//    //	gl::multModelView( mCamera.getModelViewMatrix() );
//    //	gl::multModelView( mCubeRotation );
//    //
//    //	gl::color( ci::Color::white() );
//    //	gl::drawColorCube( Vec3f::zero(), Vec3f( 1.0f, 1.0f, 1.0f ) );
//    //
//    //	gl::disableDepthRead();
//    //
//    //	gl::popMatrices();
//    
//	//-------------------------------
//    gl::popMatrices();

    gl::pushMatrices();
    
    float width = bounds.getWidth();
    float height = bounds.getHeight();
    
    if(aspect > 1){
        width /= aspect;
    }else{
        height *= aspect;
    }
    
	gl::translate( pos );
    gl::color( ci::Color( 0.1,0.1,0.1 ) );
    gl::drawSolidRect(Rectf(0,0,m_InnerBounds.w,m_InnerBounds.h));
    
    Vec2f offset(bounds.getWidth()-width,bounds.getHeight()-height);
	gl::translate( offset/2.0 );

    gl::color( ci::Color( 0,0,0 ) );
    gl::drawSolidRect(Rectf(0,0,width,height));
    
    if(bIldaFrameSet){
        mIldaFrame->draw(0,0,width,height);
//        gl::draw( mPreviewFbo->getTexture(),Rectf(0,0,m_InnerBounds.w,m_InnerBounds.h) );
    }
    
    gl::popMatrices();    
    
}


void PreviewWindow::RenderUnder( Skin::Base* skin )
{
}

void PreviewWindow::setPreviewFbo(ci::gl::Fbo* fbo){
    
    mPreviewFbo = fbo;
    bPreviewFboSet = true;
}

void PreviewWindow::setIldaFrame(ciilda::Frame* frame){
    mIldaFrame = frame;
    bIldaFrameSet = true;
}