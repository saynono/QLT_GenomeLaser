//
//  CircularDataWindow.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 18.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "CircularDataWindow.h"
#include "cinder/app/AppNative.h"
#include "CinderGwen.h"

using namespace Gwen;

	
CircularDataWindow::CircularDataWindow( Gwen::Controls::Base *parent )
: Gwen::Controls::Base( parent, "CircularDataWindow" )
{
    bLayerSet = false;
    bDataControllerSet = false;
    
    for(int i=0;i<10;i++){
        Gwen::Controls::Label* label =  new Gwen::Controls::Label( this );
        label->SetText( "CRAWLER #" + to_string(i) );
        mCrawlerLabels.push_back( label );
    }

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
    gl::color( ci::Color( 0,0,0 ) );
    gl::drawSolidRect(Rectf(0,0,m_InnerBounds.w,m_InnerBounds.h));
    
    Vec2f offset(bounds.getWidth()-width,bounds.getHeight()-height);
	gl::translate( offset/2.0 );
    
    gl::color( ci::Color( 0,0,0 ) );
    gl::drawSolidRect(Rectf(0,0,width,height));
    
    if(bLayerSet){
        gl::color( ci::Color( 1,1,1 ) );
        gl::draw( mDataLayer->getTexture()->getTexture(0), Rectf(0,0,width,height) );
    }
    
    if(bDataControllerSet){
        
        gl::color( ci::Color( 1,1,1 ) );
        gl::drawStrokedCircle( Vec2f(width/2,height/2), width * .45 );
        
        vector<DataCrawler>* crawler = mDataController->getCrawler();
        float dia;
        Vec2f center(width/2,height/2);
        float h;
        float dist;
        Vec2f vec;
        float angle;
        float angleOffset;
        int amount = crawler->size();
        for(int i=0;i<amount;i++){
            h = 60 + i*50;
            dia = lerp(width * .45 * .5, width * .45, crawler->at(i).pos);
            vec = center - Vec2f(0,h);
            dist = vec.length();
            angle = M_PI * .2;
            angleOffset = crawler->at(i).pos * M_PI * 10.0f;
            gl::color( ci::Color( 1,1,1 ) );
            gl::drawStrokedCircle( center, dia );
            gl::drawLine(Vec2f(-100,h), Vec2f(0,h) );
            gl::drawLine(Vec2f(0,h), Vec2f(0,h) + vec * (1.0-dia/dist)  );
            
//            gl::color( ci::Color( 0,1,1 ) );
            gl::lineWidth(4);
            drawArc( center, dia, angleOffset, angleOffset + crawler->at(i).length );
            gl::lineWidth(1);
        }
        
        for(int i=0;i<mCrawlerLabels.size();i++){
            
            if(i>=amount) h = 2000;
            else h = 45 + i*50;
            mCrawlerLabels[i]->SetPos(offset.x/2 - 100, h);
        }
        
    }
    
    gl::popMatrices();
    
}

void CircularDataWindow::drawArc( Vec2f center, float dia, float angleStart, float angleEnd ){
    
    float start = min( angleStart, angleEnd );
    float end = max( angleStart, angleEnd );
    float len = (end-start);
    float step = toRadians( 3.0f );
    Vec2f p;
    float a;
    gl::begin(GL_LINE_STRIP);
    for( a=start;a<end;a+=step){
        p.x = sin(a)*dia;
        p.y = cos(a)*dia;
        gl::vertex( p + center );
    }
    p.x = sin(end)*dia;
    p.y = cos(end)*dia;
    gl::vertex( p + center );
    gl::end();
}


void CircularDataWindow::setCircularDataLayer( CircularDataLayer* layer ){
    mDataLayer = layer;
    bLayerSet = true;
}

void CircularDataWindow::setDataController(DataController* d){
    mDataController = d;
    bDataControllerSet = true;
}

