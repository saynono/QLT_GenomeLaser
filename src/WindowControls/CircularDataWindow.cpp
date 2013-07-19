//
//  CircularDataWindow.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 18.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "CircularDataWindow.h"

#include "CinderGwen.h"

using namespace Gwen;

	
CircularDataWindow::CircularDataWindow( Gwen::Controls::Base *parent )
: Gwen::Controls::Base( parent, "CircularDataWindow" )
{
    bLayerSet = false;
}

CircularDataWindow::~CircularDataWindow(){
    
}

void CircularDataWindow::Render( Gwen::Skin::Base* skin )
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
    
    if(bLayerSet){
        gl::color( ci::Color( 1,1,1 ) );
        gl::draw( mDataLayer->getTexture()->getTexture(0), Rectf(0,0,width,height) );
    }
    
    gl::popMatrices();
    
}


void CircularDataWindow::setCircularDataLayer( CircularDataLayer* layer ){
    mDataLayer = layer;
    bLayerSet = true;
}
