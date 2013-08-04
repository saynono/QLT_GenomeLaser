//
//  CrawlerPluginsWindow.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 02.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "CrawlerPluginsWindow.h"
#include "cinder/app/AppNative.h"
#include "cinder/Utilities.h"
#include "CinderGwen.h"

using namespace Gwen;



CrawlerPluginsWindow::CrawlerPluginsWindow( Gwen::Controls::Base *parent )
: Gwen::Controls::ScrollControl( parent, "CrawlerPluginsWindow" )
{
    bLayerSet = false;
    bDataControllerSet = false;
    
    pTestArea = new Controls::Base( this );
    pTestArea->SetBounds( 0, 0, 900, 600 );

}

CrawlerPluginsWindow::~CrawlerPluginsWindow(){
    
}

void CrawlerPluginsWindow::Render( Gwen::Skin::Base* skin )
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
    
    float y = 30;
    vector<CrawplContainer*>::iterator itr;
    for(itr=mCrawplContainer.begin();itr!=mCrawplContainer.end();++itr){
        (*itr)->SetPos(0,y);
        y += (*itr)->getHeight();
    }
    pTestArea->SetSize(900,y);
    
    
    
//    Vec2f offset(bounds.getWidth()-width,bounds.getHeight()-height);
//    gl::translate( offset/2.0 );
//    
//    gl::color( ci::Color( 0,0,0 ) );
//    gl::drawSolidRect(Rectf(0,0,width,height));
//    
//    if(bLayerSet){
//        gl::color( ci::Color( 1,1,1 ) );
//        gl::draw( mDataLayer->getTexture()->getTexture(0), Rectf(0,0,width,height) );
//    }
//    
//    if(bDataControllerSet){
//        
//        gl::color( ci::Color( 1,1,1 ) );
//        gl::drawStrokedCircle( Vec2f(width/2,height/2), width * .45 );
//        
//        vector<DataCrawler>* crawler = mDataController->getCrawler();
//        float dia;
//        Vec2f center(width/2,height/2);
//        float h;
//        float dist;
//        Vec2f vec;
//        float angle;
//        float angleOffset;
//        int amount = crawler->size();
//        for(int i=0;i<amount;i++){
//            h = 60 + i*50;
//            dia = lerp(width * .45 * .5, width * .45, crawler->at(i).pos);
//            vec = center - Vec2f(0,h);
//            dist = vec.length();
//            angle = M_PI * .2;
//            angleOffset = crawler->at(i).pos * M_PI * 10.0f;
//            gl::color( ci::Color( 1,1,1 ) );
//            gl::drawStrokedCircle( center, dia );
//            gl::drawLine(Vec2f(-100,h), Vec2f(0,h) );
//            gl::drawLine(Vec2f(0,h), Vec2f(0,h) + vec * (1.0-dia/dist)  );
//            
//            gl::lineWidth(4);
//            drawArc( center, dia, angleOffset, angleOffset + crawler->at(i).length );
//            gl::lineWidth(1);
//        }
//        
//        for(int i=0;i<mCrawlerLabels.size();i++){
//            
//            if(i>=amount) h = 2000;
//            else h = 45 + i*50;
//            mCrawlerLabels[i]->SetPos(offset.x/2 - 100, h);
//        }
//        
//    }
    
    gl::popMatrices();
    
}

void CrawlerPluginsWindow::setDataController(DataController* d){
    mDataController = d;
    bDataControllerSet = true;
    
    int amountCrawler = mDataController->getCrawler()->size();
    for(int i=0;i<amountCrawler;i++){
        CrawplContainer* cr = new CrawplContainer( pTestArea );
        cr->setName( "Crawler Container => "  + toString(i) );
        cr->SetSize( 900, 100 );
        cr->SetPos( 0, i*100 );
        cr->setCrawler( &mDataController->getCrawler()->at(i) );
        mCrawplContainer.push_back( cr );
    }
}

void CrawlerPluginsWindow::setMainController( MainController* mc ){
    mMainController = mc;
    mDataController = mMainController->getDataController();
    mPluginController = mMainController->getPluginController();
    bDataControllerSet = true;
    
    map< string, vector<BasePlugin*> > pmap = mPluginController->getPluginsDirectory();
    map< string, vector<BasePlugin*> >::iterator it;
//    for(it=pmap.begin();it!=pmap.end();++it){
//        console() << "PLUGIN " << (*it).first << "  => " << (*it).second.size() << std::endl;
//    }
    
    int amountCrawler = mDataController->getCrawler()->size();
    for(int i=0;i<amountCrawler;i++){
        CrawplContainer* cr = new CrawplContainer( pTestArea );
        cr->setName( "Crawler Container => "  + toString(i) );
        cr->SetSize( 900, 100 );
        cr->SetPos( 0, i*100 );
        cr->setCrawler( &mDataController->getCrawler()->at(i) );
        for(it=pmap.begin();it!=pmap.end();++it){
            cr->addPlugin( (*it).second.at(i) );
        }
        mCrawplContainer.push_back( cr );
    }
}
