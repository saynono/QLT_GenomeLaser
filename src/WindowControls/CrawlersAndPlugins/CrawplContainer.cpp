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
: Gwen::Controls::GroupBox( parent, "CrawplContainer" )
{
    
//    Gwen::Controls::GroupBox* pGroup = new Gwen::Controls::GroupBox( this );
//    pGroup->SetText( "Group Box" );
//    pGroup->SetSize( 900, 200 );
//	pGroup->Dock( Gwen::Pos::Fill );
    
    mName = "Crawler Dummy";
    Gwen::Controls::Label* label =  new Gwen::Controls::Label( this );
    label->SetText( mName );
    label->SetPos(10, 10);
    label->SetSize(500, 30);
    mLabel = label;
    bIsSmall = true;
    mHeightSmall = 30;
    mHeightLarge = 550;
    mHeightCurrent = mHeightSmall;
    mWidth = 900;
    SetSize(mWidth,mHeightSmall);

    label =  new Gwen::Controls::Label( this );
    label->SetText( mName );
    label->SetPos(10, 20);
    label->SetSize(900, 30);
    mLabelBasePairs = label;
    
    Gwen::Controls::PropertyTree* ptree = new Gwen::Controls::PropertyTree( this );
    ptree->SetBounds( 20, 20, 300, 500 );
    mProperties = ptree;

}

CrawplContainer::~CrawplContainer(){};

void CrawplContainer::Render( Gwen::Skin::Base* skin )
{
    
	Vec2f pos( cigwen::fromGwen( LocalPosToCanvas() ) );
	ci::Rectf bounds( cigwen::fromGwen( GetBounds() ) );
	float aspect = (float)m_InnerBounds.w / (float)m_InnerBounds.h;
    gl::pushMatrices();
    
    
    mLabel->SetText( mName + "   POS : " + toString(mDataCrawler->dataSet.startPosition) + "    " + mDataCrawler->roiDataSet.roiDescription);
    mLabelBasePairs->SetText( mDataCrawler->dataSet.dataBitsString );
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


// ----------------------------------------------------------------------------------------


void CrawplContainer::setName(string name){
    mName = name;
    mLabel->SetText( name );
    SetText( name );
}

void CrawplContainer::setCrawler(DataCrawler* crawler){
    mDataCrawler = crawler;
}

void CrawplContainer::addPlugin( BasePlugin* plugin){
    mPlugins.push_back( plugin );
    
    Gwen::Controls::Properties* props = mProperties->Add( plugin->pluginID() );
    props->SetSize(300, 200);
    int h = 0;
    map<string, OSCElement> valMap = plugin->getOSCMapping();
    map<string, OSCElement>::iterator it;
    for( it=valMap.begin(); it!=valMap.end(); ++it){
        
//        Gwen::Controls::HorizontalSlider* pSlider = new Gwen::Controls::HorizontalSlider( props );
//        pSlider->SetPos( px, py );
//        pSlider->SetSize( w, 20 );
//        pSlider->SetRange( valueMin, valueMax );
//        pSlider->SetFloatValue( value );

        props->Add( (*it).first );//, new Gwen::Controls::HorizontalSlider( props ), 50.0f );
//        props->Add( L"ColorSelector", new Gwen::Controls::Property::ColorSelector( props ), L"255 0 0" );
        h += 20;
    }
//    props->SetSize(300, h);
}

float CrawplContainer::getHeight(){
    return mHeightCurrent;
}

void CrawplContainer::resize(bool doSmall){
    bIsSmall = doSmall;
    float th;
    if(!bIsSmall){
        th = mHeightLarge;
    }else{
        th = mHeightSmall;
    }
    TweenRef<float> tweenRef = timeline().apply( &mHeightCurrent, th, .34f, EaseOutSine() );

}


void CrawplContainer::update(){
	
}


// ----------------------------------------------------------------------------------------


void CrawplContainer::OnMouseClickLeft( int x, int y, bool bDown ) {

    y -= cigwen::fromGwen( LocalPosToCanvas() ).y;
    if(!bDown){
        if(y<30){
            resize(!bIsSmall);
        }
    }
}

