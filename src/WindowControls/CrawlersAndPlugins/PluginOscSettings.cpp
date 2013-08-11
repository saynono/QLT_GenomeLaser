//
//  PluginOscSettings.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 10.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "PluginOscSettings.h"


PluginOscSettings::PluginOscSettings(Gwen::Controls::Base* parent) :
Gwen::Controls::WindowControl (parent, "OscSettings"){
    console() << "PluginOscSettings::PluginOscSettings!"<< std::endl;
}

void PluginOscSettings::setup( OSCElement* element ){
    
    console() << "PluginOscSettings::setup -> " << element->name << std::endl;
    mElement = element;
    mChanged = false;
    
    int px = (GetParent()->GetBounds().x + GetParent()->GetBounds().w)/2;
    int py = (GetParent()->GetBounds().y + GetParent()->GetBounds().h)/2;
    
    SetTitle( "OSC Settings " + element->name );
    SetSize( 300, 200 );
    MakeModal( true );
    SetPos( px-150, py-100 );
//    Position( Gwen::Pos::Center );
    SetDeleteOnClose( true );

    int btnWidth = (this->GetSize().x-10)/2;
    
    Gwen::Controls::Properties* props = new Gwen::Controls::Properties( this );
    props->Dock( Gwen::Pos::Top );
    mProperties = props;
    
    Gwen::Controls::Property::Checkbox* checkbox = new Gwen::Controls::Property::Checkbox( props );
    mCheckBox = checkbox;
    
    Gwen::Controls::PropertyRow* pRow;
//    props->Dock( Gwen::Pos::Fill );
    pRow = props->Add( "Name", element->name );
    pRow = props->Add( "OSC", element->oscVariable );
    pRow->onChange.Add( this, &PluginOscSettings::OnOscChange );
    pRow = props->Add( "OSC enabled", mCheckBox,toString(mElement->listeningToEvents) );
    pRow->onChange.Add( this, &PluginOscSettings::OnOscChange );
    
    
    Gwen::Controls::Base* buttonContainer = new Gwen::Controls::Base( this );
    buttonContainer->Dock( Gwen::Pos::Bottom );
    buttonContainer->SetHeight(20);
    mButtonCancel = new Gwen::Controls::Button( buttonContainer );
    mButtonCancel->SetText( "Cancel" );
    mButtonCancel->Dock( Gwen::Pos::Left );
    mButtonCancel->SetSize(btnWidth,20);
    mButtonApply = new Gwen::Controls::Button( buttonContainer );
    mButtonApply->SetText( "Apply" );
    mButtonApply->Dock( Gwen::Pos::Left );
    mButtonApply->SetSize(btnWidth,20);
    
    mButtonApply->onPress.Add( this, &PluginOscSettings::OnButtonApply );
    mButtonCancel->onPress.Add( this, &PluginOscSettings::OnButtonCancel );
    
//    this->CloseButtonPressed.Add( &PluginOscSettings::OnWindowClosed, this );
    
}

void PluginOscSettings::OnOscChange(Gwen::Controls::Base* pControl){
    mChanged = true;
}

void PluginOscSettings::OnButtonApply(){
    if(mChanged){
        mElement->oscVariable = mProperties->Find( "OSC" )->GetProperty()->GetPropertyValue().Get();
        mElement->listeningToEvents = mCheckBox->m_Checkbox->IsChecked();
        mElement->sOscSettingsChanged( mElement );
    }
    this->CloseButtonPressed();
}

void PluginOscSettings::OnButtonCancel(){
    this->CloseButtonPressed();    
}

void PluginOscSettings::OnWindowClosed(){
    
}





