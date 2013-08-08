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

CrawplContainer::CrawplContainer( Gwen::Controls::CollapsibleCategory* parent )
: Gwen::Controls::Base( parent, "Yes" )
{
    
    mParentCat = parent;
    Dock( Gwen::Pos::Top );
    SetSize( 800, 300);
//    Gwen::Controls::Properties* props = mPropTree->Add( "PluginSetting " + plugin->pluginID() );


//    Gwen::Controls::PropertyTree* ptree = new Gwen::Controls::PropertyTree( this );
//    ptree->SetBounds( 10, 28, 650, 300 );
//    mPropTree = ptree;
    
    mTopBar = new Gwen::Controls::Base(this);
    mTopBar->SetSize(500, 30);
    mTopBar->SetPos(10, 5);
    Gwen::Controls::Button* btn = new Gwen::Controls::Button(mTopBar);
    btn->SetSize( 140, 20 );
    btn->SetText( "ON" );
    btn->onPress.Add( this, &CrawplContainer::onOnOffClick );
    mOnOffButton = btn;

    Gwen::Controls::ComboBox* combo = new Gwen::Controls::ComboBox( this );
    combo->SetPos( 160, 00 );
    combo->SetWidth( 200 );
    combo->onSelection.Add( this, &CrawplContainer::onPluginComboClick );
    mPluginComboList = combo;
    mPluginComboList->SetHidden( true );

    mPluginList = new Gwen::Controls::ListBox( this );
    mPluginList->SetBounds( 10, 30, 150, 200 );
    mPluginList->SelectByString( "Bl*", true );
    mPluginList->SetAllowMultiSelect( true );
    mPluginList->SetKeyboardInputEnabled( true );    
    mPluginList->onRowSelected.Add( this, &CrawplContainer::onRowSelected );

    
    
//    Gwen::Controls::ListBox* ctrl = new Gwen::Controls::ListBox( this );
//    ctrl->SetBounds( 120, 10, 600, 400 );
//    ctrl->SetColumnCount( 6 );
//    ctrl->SetAllowMultiSelect( true );
////    ctrl->onRowSelected.Add( this, &ThisClass::RowSelected );
//    {
//        Gwen::Controls::Layout::TableRow* pRow = ctrl->AddItem( L"Baked Beans" );
//        pRow->SetCellText( 1, L"Heinz" );
//        pRow->SetCellText( 2, "£3.50" );
//    }
//    {
//        Gwen::Controls::Layout::TableRow* pRow = ctrl->AddItem( L"Bananas" );
//        pRow->SetCellText( 1, L"Trees" );
//        pRow->SetCellText( 2, L"$1.27" );
//    }
//    {
//        Gwen::Controls::Layout::TableRow* pRow = ctrl->AddItem( L"Chicken" );
//        pRow->SetCellText( 1, L"\u5355\u5143\u6D4B\u8BD5" );
//        pRow->SetCellText( 2, L"\u20AC8.95" );
//    }
    
//    mValueList = ctrl;


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
}

void CrawplContainer::setCrawler(DataCrawler* crawler){
    mDataCrawler = crawler;
}

void CrawplContainer::addPlugin( BasePlugin* plugin){
    mPlugins.push_back( plugin );

    const string pluginId = plugin->pluginID();
    Gwen::Controls::Layout::TableRow* row = mPluginList->AddItem( pluginId );
    mPluginsRowMap[row] = plugin;
    createPluginSettings( plugin );
    mValueList = mPluginsListBoxMap[plugin];
    mPluginList->SetSize( mPluginList->GetSize().x, mPluginsRowMap.size() * 20 + 10);
//    displayPluginSettings( plugin );
    
    SetHeight( mPluginList->GetSize().y + 60 );
    Gwen::UnicodeString pluginIdUni = Gwen::Utility::StringToUnicode( pluginId );
    mPluginComboList->AddItem( pluginIdUni, pluginId );
    mPluginComboList->SetHidden( false );
}

void CrawplContainer::displayPluginSettings( BasePlugin* plugin){
    mValueList->SetHidden( true );
    mValueList = mPluginsListBoxMap[plugin];
    mValueList->SetHidden( false );
    SetHeight( min( mPluginList->GetSize().y, mValueList->GetPos().y + mValueList->GetSize().y) + 60 );
}


void CrawplContainer::createPluginSettings( BasePlugin* plugin){

    Gwen::Controls::ListBox* ctrl = new Gwen::Controls::ListBox( this );
    ctrl->SetBounds( 160, 30, 600, 200 );
//    ctrl->SetWidth( 600 );
    ctrl->SetColumnCount( 6 );
    ctrl->SetAllowMultiSelect( true );
    ctrl->SetColumnWidth(0,100);
    ctrl->SetColumnWidth(1,320);
    ctrl->SetColumnWidth(2,100);

    mPluginsListBoxMap[plugin] = ctrl;
    
    float val;
    int cnt = 0;
    OSCElement* element;
    Gwen::Controls::Layout::TableRow* pRow;
    map<string, OSCElement*> valMap = plugin->getOSCMapping();
    map<string, OSCElement*>::iterator it;

    for( it=valMap.begin(); it!=valMap.end(); ++it){
        
        element = (*it).second;
        val = *(static_cast<float*>(element->pointer));
        
        pRow = ctrl->AddItem( (*it).first );
        pRow->SetHeight( 20 );
        
        
        Gwen::Controls::HorizontalSlider* pSlider = new Gwen::Controls::HorizontalSlider( this );
//        pSlider->SetSize( 200, 30 );
        pSlider->SetRange( element->minValue, element->maxValue );
        pSlider->SetFloatValue( val );
        pSlider->SetName("SLIDER YEAH");
        pSlider->onValueChanged.Add( this, &CrawplContainer::onSliderChange );
        pSlider->SetHeight( 20 );
        pSlider->SetWidth( 300 );

        pRow->SetCellContents( 1, pSlider  );
        pRow->SetCellText( 2, "£3.50" );
        
        mValueMap[pSlider] = element;
        cnt++;
    }
    
    ctrl->SetSize(ctrl->GetSize().x, cnt*20+20);
    ctrl->SetHidden( true );
}


void CrawplContainer::update(){
    map<Gwen::Controls::Slider*, OSCElement*>::iterator it;
    float val;
    for( it=mValueMap.begin();it!=mValueMap.end();++it ){
        if((*it).second->listeningToEvents){
            val = *(static_cast<float*>((*it).second->pointer));
            if( val != (*it).first->GetFloatValue() ){
                (*it).first->SetFloatValue( val );
            }
        }
    }
    
    string str;
    if(mDataCrawler->isActive){
        str = "ON";
        mParentCat->SetText("Crawler #" + toString(mDataCrawler->crawlerID) + "   ( " + mPluginComboList->GetSelectedItem()->GetName() + " )");
    }
    else{
        str = "OFF";
        mParentCat->SetText("Crawler #" + toString(mDataCrawler->crawlerID) + "   ( " + str + " )");
    }
    
    mOnOffButton->SetText( str );

//    float yMax = 0;
//    yMax = max( (float)(*it).first->GetBounds().y , yMax);
//    float yMax = mPropertiesPlugin->GetBounds().y + mPropertiesPlugin->GetBounds().h;
//    console() << "h : " << yMax << std::endl;
//    SetSize(GetSize().x, yMax + 20 );
    
}


// ----------------------------------------------------------------------------------------

void CrawplContainer::onRowSelected(){
    console() << "LOG : " << mPluginsRowMap[mPluginList->GetSelectedRow()]->pluginID() << std::endl;
    displayPluginSettings( mPluginsRowMap[mPluginList->GetSelectedRow()] );
}

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

void CrawplContainer::onOnOffClick( Gwen::Controls::Base* pControl ){
    mDataCrawler->isActive = !mDataCrawler->isActive;
    console() << " mDataCrawler->isActive : " << mDataCrawler->isActive << std::endl;
}

void CrawplContainer::onPluginComboClick( Gwen::Controls::Base* pControl ){
    console() << " =====> " << mPluginComboList->GetSelectedItem()->GetName() << std::endl;
    vector<BasePlugin*>::iterator it;
    for(it=mPlugins.begin();it!=mPlugins.end();++it){
        if( (*it)->pluginID().compare( mPluginComboList->GetSelectedItem()->GetName() ) == 0 ){
            (*it)->activate(true);
        }else{
            (*it)->activate(false);
        }
    }
}
