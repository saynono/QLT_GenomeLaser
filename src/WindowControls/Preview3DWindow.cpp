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
    bPreviewFboSet = false;
}

Preview3DWindow::~Preview3DWindow()
{
}

void Preview3DWindow::Render( Skin::Base* skin )
{
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
    gl::color( ci::Color( 0.1,0.1,0.1 ) );
    gl::drawSolidRect(Rectf(0,0,m_InnerBounds.w,m_InnerBounds.h));
    
    Vec2f offset(bounds.getWidth()-width,bounds.getHeight()-height);
	gl::translate( offset/2.0 );
    
    gl::color( ci::Color( 0,0,0 ) );
    gl::drawSolidRect(Rectf(0,0,width,height));
    
    if(bPreviewFboSet){
        gl::draw( mPreview3DFbo->getTexture(),Rectf(0,0,m_InnerBounds.w,m_InnerBounds.h) );
    }
    
    gl::popMatrices();    
    
}


void Preview3DWindow::RenderUnder( Skin::Base* skin )
{
}

void Preview3DWindow::setPreviewFbo(ci::gl::Fbo* fbo){
    mPreview3DFbo = fbo;
    bPreviewFboSet = true;
}