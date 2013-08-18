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
//    SetSize( 800, 300);

    mTopBar = new Gwen::Controls::Base(this);
    mTopBar->SetSize(500, 30);
    mTopBar->SetPos(10, 5);
    Gwen::Controls::Button* btn = new Gwen::Controls::Button(mTopBar);
    btn->SetSize( 140, 20 );
    btn->SetText( "ON" );
    btn->onPress.Add( this, &CrawplContainer::onOnOffClick );
    mOnOffButton = btn;

    Gwen::Controls::ComboBox* combo = new Gwen::Controls::ComboBox( this );
    combo->SetPos( 160, 5 );
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

}

CrawplContainer::~CrawplContainer(){};

void CrawplContainer::Render( Gwen::Skin::Base* skin )
{

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
    SetHeight( max( mPluginList->GetSize().y+mPluginList->GetPos().y, mValueList->GetPos().y + mValueList->GetSize().y) + 10 );
}


void CrawplContainer::createPluginSettings( BasePlugin* plugin){

    Gwen::Controls::ListBox* ctrl = new Gwen::Controls::ListBox( this );
    ctrl->SetBounds( 160, 30, 600, 200 );
//    ctrl->SetWidth( 600 );
    ctrl->SetColumnCount( 4 );
    ctrl->SetAllowMultiSelect( true );
    ctrl->SetColumnWidth(0,100);
    ctrl->SetColumnWidth(1,240);
    ctrl->SetColumnWidth(2,100);
    ctrl->SetColumnWidth(3,80);
    
    mPluginsListBoxMap[plugin] = ctrl;
    
    float val;
    int cnt = 0;
    ColorAf clr;
    bool isColor = false;
    OSCElement* element;
    Gwen::Controls::Layout::TableRow* pRow;
    map<string, OSCElement*> valMap = plugin->getOSCMapping();
    map<string, OSCElement*>::iterator it;

    for( it=valMap.begin(); it!=valMap.end(); ++it){
        
        element = (*it).second;
        
        isColor = false;
        if(element->type == OSCElement::OSCElementTypes::INTEGER){
            val = *(static_cast<int*>(element->pointer));
        }else if(element->type == OSCElement::OSCElementTypes::COLOR){
            clr = *(static_cast<ColorAf*>(element->pointer));
            isColor = true;
        }else{
            val = *(static_cast<float*>(element->pointer));
        }
        
        
        pRow = ctrl->AddItem( (*it).first );
//        pRow->Dock( Gwen::Pos::Fill );
        pRow->SetHeight( 20 );
        
        if( isColor ){
            Gwen::Controls::Property::ColorSelector* clrs = new Gwen::Controls::Property::ColorSelector( this );
            clrs->onChange.Add( this, &CrawplContainer::onColorChange );
            clrs->SetWidth(100);
//            L"ColorSelector", new Gwen::Controls::Property::ColorSelector( props ), L"255 0 0"
            const string clrStr = toString((int)clr.r*255)+" "+toString((int)clr.b*255)+" "+toString((int)clr.b * 255);
            pRow->SetCellContents( 1, clrs );
            pRow->SetCellText( 2, "WORM COLOR" );
            mClrValueMap[clrs] = element;
            
        }else{
            Gwen::Controls::HorizontalSlider* pSlider = new Gwen::Controls::HorizontalSlider( this );
            pSlider->SetRange( element->minValue, element->maxValue );
            pSlider->SetFloatValue( val );
            pSlider->SetName("SLIDER YEAH");
            pSlider->onValueChanged.Add( this, &CrawplContainer::onSliderChange );
            pSlider->SetHeight( 20 );
            pSlider->SetWidth( 220 );
            pRow->SetCellContents( 1, pSlider  );
            pRow->SetCellText( 2, toString(val) );
            mSliderLabelMap[pSlider] = pRow->GetCellContents(2);
            mValueMap[pSlider] = element;
        }
    
        Gwen::Controls::Button* btn = new Gwen::Controls::Button( this );
        pRow->SetCellContents( 3, btn );
        btn->onPress.Add( this, &CrawplContainer::onOscClick );
        btn->SetText( "OSC" );
        btn->SetWidth( 60 );
        mOscButton = btn;
        
        mOscButtonMap[mOscButton] = element;
        
        cnt++;
    }
    
    ctrl->SetSize(ctrl->GetSize().x, cnt*20+20);
    ctrl->SetHidden( true );
}


void CrawplContainer::update(){
    float val;
    map<Gwen::Controls::Slider*, OSCElement*>::iterator it;
    for( it=mValueMap.begin();it!=mValueMap.end();++it ){
        if((*it).second->listeningToEvents){
            (*it).first->SetDisabled( true );
            OSCElement* element = (*it).second;
            if(element->type == OSCElement::OSCElementTypes::INTEGER) val = *(static_cast<int*>(element->pointer));
            else val = *(static_cast<float*>(element->pointer));
            if( val != (*it).first->GetFloatValue() ){
                (*it).first->SetFloatValue( val );
                mSliderLabelMap[(*it).first]->SetValue( toString(val) );
            }
        }else{
            (*it).first->SetDisabled( false );
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
}

void CrawplContainer::updateValues(){
}
// ----------------------------------------------------------------------------------------

//void CrawplContainer::getRowValue( Gwen::Controls::Layout::TableRow* row ){
//
//}

// ----------------------------------------------------------------------------------------

void CrawplContainer::onRowSelected(){
    displayPluginSettings( mPluginsRowMap[mPluginList->GetSelectedRow()] );
}

void CrawplContainer::OnMouseClickLeft( int x, int y, bool bDown ) {
}

void CrawplContainer::onSliderChange( Gwen::Controls::Base* pControl ){
    Gwen::Controls::Slider* pSlider = static_cast<Gwen::Controls::Slider*> (pControl);
    float val = pSlider->GetFloatValue();
    OSCElement* element = mValueMap[pSlider];
    if(element->type == OSCElement::OSCElementTypes::INTEGER) *(static_cast<int*>(element->pointer)) = (int)val;
    else *(static_cast<float*>(element->pointer)) = val;
    mSliderLabelMap[pSlider]->SetValue( toString(val) );
}

void CrawplContainer::onOnOffClick( Gwen::Controls::Base* pControl ){
    mDataCrawler->isActive = !mDataCrawler->isActive;
}

void CrawplContainer::onOscClick( Gwen::Controls::Base* b ){
    sOpenOscSettingsWindow( mOscButtonMap[b] );
}

void CrawplContainer::onColorChange( Gwen::Controls::Base* b ){
    Gwen::Controls::Property::ColorSelector* clrs = static_cast<Gwen::Controls::Property::ColorSelector*>(b);
    string val = clrs->Gwen::Controls::Property::Text::GetPropertyValue().Get();
    console() << " CrawplContainer::onColorChange : " << val << std::endl;
    
    vector<string> tokens;
    boost::split(tokens,val,boost::is_any_of(" "));
    
    OSCElement* element = mClrValueMap[b];
    ColorAf* clr = static_cast<ColorAf*> (element->pointer);
    clr->r = stoi(tokens[0]) / 255.0f;
    clr->g = stoi(tokens[1]) / 255.0f;
    clr->b = stoi(tokens[2]) / 255.0f;

}

void CrawplContainer::onPluginComboClick( Gwen::Controls::Base* pControl ){
//    console() << " =====> " << mPluginComboList->GetSelectedItem()->GetName() << std::endl;
    vector<BasePlugin*>::iterator it;
    for(it=mPlugins.begin();it!=mPlugins.end();++it){
        if( (*it)->pluginID().compare( mPluginComboList->GetSelectedItem()->GetName() ) == 0 ){
            (*it)->activate(true);
        }else{
            (*it)->activate(false);
        }
    }
}
