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

CrawplContainer::CrawplContainer( Gwen::Controls::PropertyTree* parent )
: Gwen::Controls::Base( parent, "Yes" )
{
    
    
//    Gwen::Controls::Properties* props = mPropTree->Add( "PluginSetting " + plugin->pluginID() );

//    Gwen::Controls::PropertyTree* ptree = mPropTree->Add( "Crawler ", new Gwen::Controls::PropertyTree( parent ) );;
//    ptree->SetBounds( 10, 28, 650, 600 );
    

    mPropTree = parent;

//    Gwen::Controls::PropertyTreeNode* node = new Gwen::Controls::PropertyTreeNode( mPropTree );
//    node->SetText( "HELLO!" );
//    node->Dock( Gwen::Pos::Top );
//    
//    mPropNode = node;

//    mPropTree = parent;
    
//    mName = "Crawler Dummy";
//    Gwen::Controls::Label* label =  new Gwen::Controls::Label( this );
//    label->SetText( mName );
//    label->SetPos(10, 0);
//    label->SetSize(870, 30);
//    mLabel = label;
//    bIsSmall = true;
//    mHeightSmall = 30;
//    mHeightLarge = 250;
//    mHeightCurrent = mHeightSmall;
//    mWidth = 900;
//    SetSize(mWidth,mHeightSmall);
//
//    label =  new Gwen::Controls::Label( this );
//    label->SetText( mName );
//    label->SetPos(400, 0);
//    label->SetSize(400, 30);
//    mLabelBasePairs = label;
//
//    label =  new Gwen::Controls::Label( this );
//    label->SetText( "-" );
//    label->SetPos(100, 0);
//    label->SetSize(600, 30);
//    mLabelDescription = label;
//    
//    
//    Gwen::Controls::PropertyTree* ptree = new Gwen::Controls::PropertyTree( this );
//    ptree->SetBounds( 100, 28, 650, 300 );
//    
//    mPropTree = ptree;
//
//    resize(true);

}

CrawplContainer::~CrawplContainer(){};

void CrawplContainer::Render( Gwen::Skin::Base* skin )
{
//    
//	Vec2f pos( cigwen::fromGwen( LocalPosToCanvas() ) );
//	ci::Rectf bounds( cigwen::fromGwen( GetBounds() ) );
//	float aspect = (float)m_InnerBounds.w / (float)m_InnerBounds.h;
//    gl::pushMatrices();
//    
//    mLabelDescription->SetText( "ROI:" + mDataCrawler->roiDataSet.roiDescription + " OFFSET:" + toString(mDataCrawler->pos) );
//    mLabelBasePairs->SetText( mDataCrawler->dataSet.dataBitsString );
//    float width = bounds.getWidth();
//    float height = bounds.getHeight();
//    
//    if(aspect > 1){
//        width /= aspect;
//    }else{
//        height *= aspect;
//    }
//    
//	gl::translate( pos );
//    gl::color( ci::Color( 0x13/255.0,0x14/255.0,0x13/255.0  ) );
//    gl::drawSolidRect(Rectf(0,0,m_InnerBounds.w,m_InnerBounds.h));
//    
//    Vec2f offset(bounds.getWidth()-width,bounds.getHeight()-height);
//	gl::translate( offset/2.0 );
//    
//
//    
//    gl::popMatrices();    
}


// ----------------------------------------------------------------------------------------


void CrawplContainer::setName(string name){
    mName = name;
//    mLabel->SetText( name );
}

void CrawplContainer::setCrawler(DataCrawler* crawler){
    mDataCrawler = crawler;
}

void CrawplContainer::addPlugin( BasePlugin* plugin){
    mPlugins.push_back( plugin );
    
//    Gwen::Controls::Properties* props = mProperties->Add( plugin->pluginID() );
//    props->SetSize(300, 200);
//    int h = 0;
    float val;
    int cnt;
    OSCElement* element;
    map<string, OSCElement*> valMap = plugin->getOSCMapping();
    map<string, OSCElement*>::iterator it;
//    Gwen::Controls::Properties* props = new Gwen::Controls::Properties( mPropTree );
    Gwen::Controls::Properties* props = mPropTree->Add( "PluginSetting " + plugin->pluginID() );
//    props->SetMargin( Gwen::Margin( 2, 10, 2 , 10 ) );
    mPropertiesPlugin = props;
    mPropertiesPlugin->SetName( mName );
    for( it=valMap.begin(); it!=valMap.end(); ++it){
        element = (*it).second;
        val = *(static_cast<float*>(element->pointer));
        Gwen::Controls::Base* b = mPropertiesPlugin->Add( (*it).first );
        Gwen::Controls::PropertyControlSlider* pRow = static_cast<Gwen::Controls::PropertyControlSlider*> (b);
//        pRow->SetMargin( Gwen::Margin( 0, 4, 2 , 0 ) );
        pRow->AddSlider(val,element->minValue,element->maxValue);
        pRow->GetSlider()->onValueChanged.Add( this, &CrawplContainer::onSliderChange );
        console() << "<<<<<< pRow->GetSlider() : " << pRow->GetSlider() << std::endl;
        mValueMap[pRow->GetSlider()] = (*it).second;
        cnt++;
    }
    props->SetSize(600, cnt*20);
}

void CrawplContainer::update(){
    map<Gwen::Controls::Slider*, OSCElement*>::iterator it;
    float val;
    for( it=mValueMap.begin();it!=mValueMap.end();++it ){
        val = *(static_cast<float*>((*it).second->pointer));
//        console()<<  "<>>><< pRow->GetSlider() : " << (*it).first << std::endl;
//        if( val != (*it).first->GetFloatValue() ){
            (*it).first->SetFloatValue( val );
            console() << (*it).first->GetFloatValue() << " => " << val << "     " << std::endl;
//        }
    }
//    console() << "------------------------------------------" << std::endl;
}


// ----------------------------------------------------------------------------------------


void CrawplContainer::OnMouseClickLeft( int x, int y, bool bDown ) {

//    y -= cigwen::fromGwen( LocalPosToCanvas() ).y;
//    if(!bDown){
//        if(y<30){
//            resize(!bIsSmall);
//        }
//    }
}

void CrawplContainer::onSliderChange( Gwen::Controls::Base* pControl ){

    Gwen::Controls::Slider* pSlider = ( Gwen::Controls::Slider* ) pControl;
    float val = pSlider->GetFloatValue();
    
    OSCElement* element = mValueMap[pSlider];
    *(static_cast<float*>(element->pointer)) = val;
    
//    console()<< "element->pointer : " << element->pointer << std::endl;
}
