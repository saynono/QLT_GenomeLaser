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
    label->SetPos(10, 0);
    label->SetSize(500, 30);
    mLabel = label;
    bIsSmall = true;
    mHeightSmall = 50;
    mHeightLarge = 550;
    mHeightCurrent = mHeightSmall;
    mWidth = 900;
    SetSize(mWidth,mHeightSmall);

    label =  new Gwen::Controls::Label( this );
    label->SetText( mName );
    label->SetPos(400, 0);
    label->SetSize(400, 30);
    mLabelBasePairs = label;

    label =  new Gwen::Controls::Label( this );
    label->SetText( "-" );
    label->SetPos(100, 0);
    label->SetSize(300, 30);
    mLabelDescription = label;
    
    Gwen::Controls::Properties* props = new Gwen::Controls::Properties( this );
    props->SetBounds( 10, 10, 500, 300 );
    
    mProperties = props;


}

CrawplContainer::~CrawplContainer(){};

void CrawplContainer::Render( Gwen::Skin::Base* skin )
{
    
	Vec2f pos( cigwen::fromGwen( LocalPosToCanvas() ) );
	ci::Rectf bounds( cigwen::fromGwen( GetBounds() ) );
	float aspect = (float)m_InnerBounds.w / (float)m_InnerBounds.h;
    gl::pushMatrices();
    
    mLabelDescription->SetText( "ROI:" + mDataCrawler->roiDataSet.roiDescription + " OFFSET:" + toString(mDataCrawler->pos) );
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
    
//    Gwen::Controls::Properties* props = mProperties->Add( plugin->pluginID() );
//    props->SetSize(300, 200);
    int h = 0;
    float val;
    OSCElement* element;
    map<string, OSCElement*> valMap = plugin->getOSCMapping();
    map<string, OSCElement*>::iterator it;
    for( it=valMap.begin(); it!=valMap.end(); ++it){
        element = (*it).second;
        val = *(static_cast<float*>(element->pointer));
        Gwen::Controls::Base* b = mProperties->Add( (*it).first );
        Gwen::Controls::PropertyControlSlider* pRow = static_cast<Gwen::Controls::PropertyControlSlider*> (b);
        pRow->SetSize(400, 20);
        pRow->AddSlider(val,element->minValue,element->maxValue);
        pRow->GetSlider()->onValueChanged.Add( this, &CrawplContainer::onSliderChange );
        
        console() << "minVal : " << element->minValue << "     maxVal : " << element->maxValue << std::endl;
        mValueMap[pRow->GetSlider()] = (*it).second;
    }
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
    map<Gwen::Controls::Slider*, OSCElement*>::iterator it;
    float val;
    for( it=mValueMap.begin();it!=mValueMap.end();++it ){
        val = *(static_cast<float*>((*it).second->pointer));
        if( val != (*it).first->GetFloatValue() ){
            (*it).first->SetValue( toString(val) );
        }
    }

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

void CrawplContainer::onSliderChange( Gwen::Controls::Base* pControl ){

    Gwen::Controls::Slider* pSlider = ( Gwen::Controls::Slider* ) pControl;
    float val = pSlider->GetFloatValue();
    
    OSCElement* element = mValueMap[pSlider];
    *(static_cast<float*>(element->pointer)) = val;
    
//    console()<< "element->pointer : " << element->pointer << std::endl;
}
