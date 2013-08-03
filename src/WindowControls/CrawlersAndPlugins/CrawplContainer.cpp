//
//  CrawplContainer.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 02.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "CrawplContainer.h"
#include "cinder/app/AppNative.h"
#include "CinderGwen.h"

CrawplContainer::CrawplContainer( Gwen::Controls::Base *parent )
: Gwen::Controls::Base( parent, "CrawplContainer" )
{
    Gwen::Controls::Label* label =  new Gwen::Controls::Label( this );
    label->SetText( "Crawler Dummy" );
    label->SetPos(10, 10);
    label->SetSize(500, 30);
    mLabel = label;
}

CrawplContainer::~CrawplContainer(){};

void CrawplContainer::Render( Gwen::Skin::Base* skin )
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
    gl::color( ci::Color( 0x13/255.0,0x14/255.0,0x13/255.0  ) );
    gl::drawSolidRect(Rectf(0,0,m_InnerBounds.w,m_InnerBounds.h));
    
    Vec2f offset(bounds.getWidth()-width,bounds.getHeight()-height);
	gl::translate( offset/2.0 );
    

    
    gl::popMatrices();
    
}

void CrawplContainer::setName(string name){
    mLabel->SetText( name );
}

void CrawplContainer::setCrawler(const DataCrawler& crawler){
//    mDataCrawler = crawler;
}

void CrawplContainer::setPlugins(const vector<BasePlugin*>& plugins){
    
}


void CrawplContainer::update(){
	
}
