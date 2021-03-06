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
    
    float outputScale = mIldaFrame->params.output.transform.scale.x;
	Vec2f pos( cigwen::fromGwen( LocalPosToCanvas() ) );
	ci::Rectf bounds( cigwen::fromGwen( GetBounds() ) );
	float aspect = (float)m_InnerBounds.w / (float)m_InnerBounds.h;
    gl::pushMatrices();
    
    float width = bounds.getWidth();
    float height = bounds.getHeight();
    
    if(aspect > 1){
        width /= aspect;
    }else{
        height *= aspect;
    }
    
	gl::translate( pos );
//    gl::color( ci::Color( 0.1,0.1,0.1 ) );
    
//    ColorA clr = cigwen::fromGwen( GetSkin()->Colors.Category. );
    
//    gl::color( ci::Color( 0x26/255.f,0x27/255.f,0x26/255.f ) );
//    gl::color( ci::Color( 0,0,0 ) );
    gl::color( ci::Color( 0x13/255.0,0x14/255.0,0x13/255.0  ) );

    gl::drawSolidRect(Rectf(0,0,m_InnerBounds.w,m_InnerBounds.h));
    
    Vec2f offset(bounds.getWidth()-width,bounds.getHeight()-height);
	gl::translate( offset/2.0 );

    gl::color( ci::Color( 0x13/255.0,0x14/255.0,0x13/255.0  ) );
    gl::drawSolidRect(Rectf(0,0,width,height));
    
    if(bIldaFrameSet){
        mIldaFrame->draw(0,0,width,height);
//        gl::draw( mPreviewFbo->getTexture(),Rectf(0,0,m_InnerBounds.w,m_InnerBounds.h) );
    }
    
    gl::pushMatrices();
    
    gl::color( ci::ColorA( .5,.5,.5,.5 ) );
    gl::drawStrokedRect( Rectf(0,0,width,height) );
    gl::translate( Vec2f(width/2,height/2) );
    gl::drawStrokedCircle(Vec2f::zero(), width/2.0);
    gl::drawStrokedCircle(Vec2f::zero(), 5);
    
    gl::color( ci::Color( 1,0,0 ) );
    gl::drawStrokedCircle(Vec2f::zero(), width/2.0*outputScale);
    gl::popMatrices();
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
