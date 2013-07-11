//
//  SettingsPanel.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 06.07.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "SettingsPanel.h"


SettingsPanel::SettingsPanel(){
}

SettingsPanel::~SettingsPanel(){
}

void SettingsPanel::setup(Gwen::Controls::DockBase *parent){
    
    bIldaFrameSet = false;
    bLaserControllerSet = false;
    mLaserCatElements.clear();

////    Gwen::Controls::DockBase* dock = new Gwen::Controls::DockBase( mCanvas );
//    this->Dock( Gwen::Pos::Fill );
//    Gwen::Controls::CollapsibleList* pList = new Gwen::Controls::CollapsibleList( this );
//    pList->SetHeight(300);
////    //    mCanvas->
//    Gwen::Controls::TabControl* tabControl = this->GetLeft()->GetTabControl();
//	tabControl->AddPage( "Settings", pList );
//	this->GetLeft()->SetWidth( 250 );

    Gwen::Controls::TabControl* tabControl = parent->GetLeft()->GetTabControl();

    Gwen::Controls::CollapsibleList* pList = new Gwen::Controls::CollapsibleList( parent );
    pList->SetHeight(300);
	tabControl->AddPage( "Settings", pList );
    tabControl->SetAllowReorder(false);
    
	parent->GetLeft()->SetWidth( 250 );
    
    Gwen::Controls::CollapsibleCategory* cat1 = pList->Add( "Laser Stats" );
    Gwen::Controls::CollapsibleCategory* cat2 = pList->Add( "Laser Output Settings" );

//    cat1->get
    
//    Gwen::Padding padding = Gwen::Padding( 10, 0, 10, 30 );
//    cat1->SetPadding( padding );
    
    mLaserStatsCat = cat1;
    mLaserCat = cat2;

}

void SettingsPanel::update(){
    if(bIldaFrameSet){
        mLabelsValueMap["Points Count"]->SetValue( toString( mIldaFrame->getPoints().size()) );
        mLabelsValueMap["Length Blank"]->SetValue( toString( mIldaFrame->stats.lengthBlank) );
        mLabelsValueMap["Length Visible"]->SetValue( toString( mIldaFrame->stats.lengthLines) );
        mLabelsValueMap["Length Total"]->SetValue( toString( mIldaFrame->stats.lengthTotal) );
        mLabelsValueMap["Contour Count"]->SetValue( toString( mIldaFrame->stats.countContours) );
        mLabelsValueMap["Segment Count"]->SetValue( toString( mIldaFrame->stats.countSegments) );
    }
}

void SettingsPanel::setIldaFrame(ciilda::Frame* frame){
    mIldaFrame = frame;
    
    Gwen::Controls::Base* pSlider;
    Gwen::Controls::Base* pCheckBox;
    Gwen::Controls::Base* pLabel;
    
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
    
    pLabel = addProperty(mLaserStatsCat, getBounds(mLaserStatsCatElements), "Points Count", 0);
    mLaserStatsCatElements.push_back(pLabel);
    
    pLabel = addProperty(mLaserStatsCat, getBounds(mLaserStatsCatElements), "Length Blank", 0);
    mLaserStatsCatElements.push_back(pLabel);

    pLabel = addProperty(mLaserStatsCat, getBounds(mLaserStatsCatElements), "Length Visible", 0);
    mLaserStatsCatElements.push_back(pLabel);
    
    pLabel = addProperty(mLaserStatsCat, getBounds(mLaserStatsCatElements), "Length Total", 0);
    mLaserStatsCatElements.push_back(pLabel);
    
    pLabel = addProperty(mLaserStatsCat, getBounds(mLaserStatsCatElements), "Contour Count", 0);
    mLaserStatsCatElements.push_back(pLabel);
    
    pLabel = addProperty(mLaserStatsCat, getBounds(mLaserStatsCatElements), "Segment Count", 0);
    mLaserStatsCatElements.push_back(pLabel);

    
    bIldaFrameSet = true;
    
//    Rectf r = getBounds(mLaserCatElements);
//    ColourCorrectionWindow *control = new ColourCorrectionWindow( mLaserCat );
//    control->setup();
//	control->SetPos( r.getX1(), r.getY1() );
//    control->SetPadding(Gwen::Padding(0,0,0,0));
//	control->Dock( Gwen::Pos::Fill );

//    struct {
//        bool doFlipX;
//        bool doFlipY;
//        Vec2f offset;
//        Vec2f scale;
//    } transform;

}

void SettingsPanel::setLaserController(ciilda::LaserController* controller){
    mLaserController = controller;
    
    Gwen::Controls::Base* pSlider;
    Gwen::Controls::Base* pCheckBox;
    
    pSlider = addSlider(mLaserCat, getBounds(mLaserCatElements), "Laser pps", mLaserController->getPPS(), 1000, 30000 );
    mLaserCatElements.push_back(pSlider);
    
    bLaserControllerSet = true;

}

void SettingsPanel::setLaserPreview3d( LaserPreview3D* laserPreview3D ){
    mLaserPreview3D = laserPreview3D;
    Gwen::Controls::Base* pSlider = addSlider(mLaserCat, getBounds(mLaserCatElements), "Laser Angle", mLaserPreview3D->getLaserAngle(), 0, 180 );
    mLaserCatElements.push_back(pSlider);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////

Gwen::Controls::Base* SettingsPanel::addCheckBox( Gwen::Controls::Base* pControl , Rectf bounds, string name, bool selected){
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

Gwen::Controls::Base* SettingsPanel::addSlider( Gwen::Controls::Base* pControl , Rectf bounds, string name, int value, int valueMin, int valueMax){
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

Gwen::Controls::Base* SettingsPanel::addProperty( Gwen::Controls::Base* pControl , Rectf bounds, string name, int val){
    Gwen::Controls::Label* pLabelName = new Gwen::Controls::Label( pControl );
    Gwen::Controls::Label* pLabelValue = new Gwen::Controls::Label( pControl );
    int px = bounds.getX1();
    int py = bounds.getY1();
    int w = bounds.getWidth();
    //    labeled->SetName( name );
    pLabelName->SetPos( px, py );
    pLabelName->SetText( name );
    pLabelName->SetAlignment(Gwen::Pos::Left );
//    pLabelName->SetName( name );

    pLabelValue->SetPos( px, py );
    pLabelValue->SetWidth( w );
    pLabelValue->SetText( toString(val) );
    pLabelValue->SetAlignment( Gwen::Pos::Right );
    pLabelValue->SetName( name );

    mLabelsValueMap[name] = pLabelValue;
    return pLabelName;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////

Rectf SettingsPanel::getBounds(const vector<Gwen::Controls::Base*>& vec){
    Rectf rect;
    int h = 0;
    int dist = 15;
    for(int i=0;i<vec.size();i++){
        h += vec[i]->GetSize().y + dist;
    }
    rect.set(10, h + 50, 200 + 10, 30);
    console() << " ADD : "  << rect << std::endl;
    return rect;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    ACTIONS

void SettingsPanel::onSliderLaserOutput( Gwen::Controls::Base* pControl ){
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
    else if (controlName.compare("Laser pps") == 0){
        mLaserController->setPPS(( int ) pSlider->GetFloatValue());
    }
    else if (controlName.compare("Laser Angle") == 0){
        mLaserPreview3D->setLaserAngle( ( int ) pSlider->GetFloatValue() );
    }
    
    
}

void SettingsPanel::onCheckBoxLaserOutput( Gwen::Controls::Base* pControl ){
    
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
