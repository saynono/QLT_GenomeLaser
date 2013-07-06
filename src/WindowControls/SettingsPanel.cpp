//
//  SettingsPanel.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 06.07.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "SettingsPanel.h"


SettingsPanel::SettingsPanel(Gwen::Controls::Base *parent): Gwen::Controls::DockBase( parent ){
//    , "QLT Settings Dock"
}

SettingsPanel::~SettingsPanel(){
}

void SettingsPanel::Render( Gwen::Skin::Base* skin )
{
}

void SettingsPanel::RenderUnder( Gwen::Skin::Base* skin )
{
}

void SettingsPanel::setup(){

////    Gwen::Controls::DockBase* dock = new Gwen::Controls::DockBase( mCanvas );
//    this->Dock( Gwen::Pos::Fill );
//    Gwen::Controls::CollapsibleList* pList = new Gwen::Controls::CollapsibleList( this );
//    pList->SetHeight(300);
////    //    mCanvas->
//    Gwen::Controls::TabControl* tabControl = this->GetLeft()->GetTabControl();
//	tabControl->AddPage( "Settings", pList );
//	this->GetLeft()->SetWidth( 250 );

    
    Gwen::Controls::DockBase* dock = this;
    dock->Dock( Gwen::Pos::Fill );
    Gwen::Controls::TabControl* tabControl = dock->GetLeft()->GetTabControl();
    Gwen::Controls::CollapsibleList* pList = new Gwen::Controls::CollapsibleList( dock );
    pList->SetHeight(300);
	tabControl->AddPage( "Settings", pList );
	dock->GetLeft()->SetWidth( 250 );
    
    Gwen::Controls::CollapsibleCategory* cat1 = pList->Add( "Basic" );
    Gwen::Controls::CollapsibleCategory* cat2 = pList->Add( "Laser Output Settings" );
    
    Gwen::Controls::Button* pButton1 = cat1->Add("Normal Window");//new Gwen::Controls::Button( cat );
    Gwen::Controls::Button* pButton2 = cat1->Add("Normal Window");//new Gwen::Controls::Button( cat );

//    Gwen::Controls::Button* pButton3 = cat2->Add("Not Normal Window");//new Gwen::Controls::Button( cat );
//    Gwen::Controls::Button* pButton4 = cat2->Add("Burp");//new Gwen::Controls::Button( cat );
//    pButton4->SetPos( 10, 60 );
//    pButton4->SetSize(200, 60 );
//    
//    cat2->SetSize(250, 400);
    
    mLaserCat = cat2;

}

void SettingsPanel::update(){
	
}

void SettingsPanel::setIldaFrame(ciilda::Frame* frame){
    mIldaFrame = frame;
    
    Gwen::Controls::Base* pSlider;
    Gwen::Controls::Base* pCheckBox;
    
    pSlider = addSlider(mLaserCat, getBounds(mLaserCatElements), "Target Points Count", mIldaFrame->params.output.targetPointCount, 1, 3000 );
    mLaserCatElements.push_back(pSlider);
    
    pSlider= addSlider(mLaserCat, getBounds(mLaserCatElements), "Blank Count", mIldaFrame->params.output.blankCount, 0, 100 );
    mLaserCatElements.push_back(pSlider);
    
    pSlider = addSlider(mLaserCat, getBounds(mLaserCatElements), "End Count", mIldaFrame->params.output.endCount, 0, 100 );
    mLaserCatElements.push_back(pSlider);

    pCheckBox = addCheckBox(mLaserCat, getBounds(mLaserCatElements), "Draw Lines", mIldaFrame->params.draw.lines );
    mLaserCatElements.push_back(pCheckBox);
    
    pCheckBox = addCheckBox(mLaserCat, getBounds(mLaserCatElements), "Draw Points", mIldaFrame->params.draw.points );
    mLaserCatElements.push_back(pCheckBox);
    
//    struct {
//        bool doFlipX;
//        bool doFlipY;
//        Vec2f offset;
//        Vec2f scale;
//    } transform;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////

Gwen::Controls::Base* SettingsPanel::addCheckBox( Base* pControl , Rectf bounds, string name, bool selected){
    Gwen::Controls::CheckBoxWithLabel* labeled = new Gwen::Controls::CheckBoxWithLabel( pControl );
    int px = bounds.getX1();
    int py = bounds.getY1();
    int w = bounds.getWidth();
//    labeled->SetName( name );
    labeled->SetPos( px, py );
    labeled->Label()->SetText( name );
//    labeled->Label()->SetName( name );
    labeled->Checkbox()->SetChecked(selected);
    labeled->Checkbox()->SetName( name );
    labeled->Checkbox()->onCheckChanged.Add( this, &SettingsPanel::onCheckBoxLaserOutput );
    return labeled;
}

Gwen::Controls::Base* SettingsPanel::addSlider( Base* pControl , Rectf bounds, string name, int value, int valueMin, int valueMax){
//
//    int py = mSlider.size() * 20 + 50;
//    int px = 10;
//    int w = 200;
    
    int px = bounds.getX1();
    int py = bounds.getY1();
    int w = bounds.getWidth();
    
    Gwen::Controls::Label* label = new Gwen::Controls::Label( pControl );
    label->SetText( name );
    label->SizeToContents();
    label->SetPos( px, py );
    
    Gwen::Controls::Label* labelValue = new Gwen::Controls::Label( pControl );
//    labelValue->SizeToContents();
    labelValue->SetWidth(w);
    labelValue->SetAlignment(Gwen::Pos::Right);
    labelValue->SetPos( px, py );
    labelValue->SetText( toString((int)value) );
    py += 10;
    Gwen::Controls::HorizontalSlider* pSlider = new Gwen::Controls::HorizontalSlider( pControl );
    pSlider->SetPos( px, py );
    pSlider->SetSize( w, 20 );
    pSlider->SetRange( valueMin, valueMax );
    pSlider->SetFloatValue( value );

//    pSlider->SetNotchCount( 10 );
//    pSlider->SetClampToNotches( true );
    pSlider->SetName(name);
    pSlider->onValueChanged.Add( this, &SettingsPanel::onSliderLaserOutput );
    
    mLabelsMap[pSlider] = labelValue;
    
    return pSlider;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////

Rectf SettingsPanel::getBounds(const vector<Gwen::Controls::Base*>& vec){
    Rectf rect;
    rect.set(10, vec.size() * 40 + 50, 200 + 10, 30);
    //    int py = mSlider.size() * 20 + 50;
    //    int px = 10;
    //    int w = 200;
    return rect;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    ACTIONS

void SettingsPanel::onSliderLaserOutput( Base* pControl ){
    Gwen::Controls::Label* label = mLabelsMap[pControl];
    Gwen::Controls::Slider* pSlider = ( Gwen::Controls::Slider* ) pControl;
    label->SetValue( toString(( int ) pSlider->GetFloatValue()));
    console() << label->GetValue().c_str() << "   Slider Value: " <<  ( float ) pSlider->GetFloatValue() << std::endl;
    
    string controlName = pSlider->GetName().c_str();
    if (controlName.compare("Target Points Count") == 0){
        mIldaFrame->params.output.targetPointCount = ( int ) pSlider->GetFloatValue();
        mIldaFrame->update();
    }
    else if (controlName.compare("Blank Count") == 0){
        mIldaFrame->params.output.blankCount = ( int ) pSlider->GetFloatValue();
        mIldaFrame->update();
    }
    else if (controlName.compare("End Count") == 0){
        mIldaFrame->params.output.endCount = ( int ) pSlider->GetFloatValue();
        mIldaFrame->update();
    }
    
}

void SettingsPanel::onCheckBoxLaserOutput( Base* pControl ){
    
    Gwen::Controls::CheckBox* pCheckBox = ( Gwen::Controls::CheckBox* ) pControl;
    string controlName = pControl->GetName().c_str();
    console() << controlName << " : " << pCheckBox->GetValue().c_str() << std::endl;
    if (controlName.compare("Draw Lines") == 0){
        mIldaFrame->params.draw.lines = pCheckBox->IsChecked() == 1;
//        console() <<  "mIldaFrame->params.draw.lines : " << mIldaFrame->params.draw.lines << std::endl;
    }
    else if (controlName.compare("Draw Points") == 0){
        mIldaFrame->params.draw.points = pCheckBox->IsChecked() == 1;
    }
    
}
