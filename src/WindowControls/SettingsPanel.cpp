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
	tabControl->AddPage( "Settings", pList );
    tabControl->SetAllowReorder(false);

	parent->GetLeft()->SetWidth( 250 );

    Gwen::Controls::CollapsibleCategory* cat0 = pList->Add( "Laser Button!" );
    Gwen::Controls::CollapsibleCategory* cat1 = pList->Add( "Laser Stats" );
    Gwen::Controls::CollapsibleCategory* cat2 = pList->Add( "Laser Output Settings" );
    Gwen::Controls::CollapsibleCategory* cat3 = pList->Add( "Laser Preview Settings" );
    Gwen::Controls::CollapsibleCategory* cat4 = pList->Add( "Laser Colour Correction" );
    
    
    mLaserButton = new Gwen::Controls::Button( cat0 );
    mLaserButton->SetText(" DISABLE LASER ");
    mLaserButton->Dock( Gwen::Pos::Top );
    mLaserButton->SetHeight(40);
    mLaserButton->SetMargin( Gwen::Margin(5,7,5,7) );
    mLaserButton->onPress.Add( this, &SettingsPanel::onLaserButtonClick );

    
    Gwen::Padding padding = Gwen::Padding( 10, 0, 10, 20 );
    cat1->SetPadding( padding );
    cat2->SetPadding( padding );
    cat3->SetPadding( padding );
    cat4->SetPadding( padding );
    
    mLaserStatsCat = cat1;
    mLaserCat = cat2;
    mLaserPreviewCat = cat3;
    mLaserColourCorCat = cat4;
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

void SettingsPanel::setOutputOptions(MainController* mc){
    
    mMainController = mc;
    
    Gwen::Controls::Base* pSlider;
    Gwen::Controls::Base* pCheckBox;
    Gwen::Controls::Base* pLabel;
    
    
//    pLabel = addProperty(mLaserCat, getBounds(mLaserCatElements), "Main speed", mMainController->getDataManager()->getMainSpeed());
//    mLaserCatElements.push_back(pLabel);
    pSlider = addSlider(mLaserCat, getBounds(mLaserCatElements), "Main speed", mMainController->getDataManager()->getMainSpeed()*100, 50, 1000 );
    mLaserCatElements.push_back(pSlider);
    
}

void SettingsPanel::setIldaFrame(ciilda::Frame* frame){
    mIldaFrame = frame;
    
    Gwen::Controls::Base* pSlider;
    Gwen::Controls::Base* pCheckBox;
    Gwen::Controls::Base* pLabel;

    
    pLabel = addProperty(mLaserCat, getBounds(mLaserCatElements), "Scanner Angle Total", mIldaFrame->params.output.scannerAngleX);
    mLaserCatElements.push_back(pLabel);

    float val = mIldaFrame->params.output.transform.scale.x * mIldaFrame->params.output.scannerAngleX ;
    pLabel = addProperty(mLaserCat, getBounds(mLaserCatElements), "Scanner Angle Max Input", val);
    mLaserCatElements.push_back(pLabel);

    
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
    
    
//    ColourCorrectionWindow *control = new ColourCorrectionWindow( window );
//    control->setup();
//	control->SetPos( 0, 0 );
//    control->SetPadding(Gwen::Padding(0,0,0,0));
//	control->Dock( Gwen::Pos::Fill );
//    pColourControl = control;

    
    Rectf r = getBounds(mLaserCatElements);
    ColourCorrectionWindow *control = new ColourCorrectionWindow( mLaserColourCorCat );
    control->setup();
    control->SetBounds( 10, 30, r.getWidth(), 200 );
    control->SetPadding(Gwen::Padding(0,0,0,0));

}

//void SettingsPanel::setLaserController(ciilda::LaserController* controller){
////    console() << "SettingsPanel::setLaserController : " << controller << std::endl;
//    mLaserController = controller;
////    console() << "-------------::setLaserController : " << mLaserController << std::endl;
//    Gwen::Controls::Base* pSlider;
////    Gwen::Controls::Base* pCheckBox;
//    
//    pSlider = addSlider(mLaserCat, getBounds(mLaserCatElements), "Laser pps", mLaserController->getPPS(), 1000, 30000 );
//    mLaserCatElements.push_back(pSlider);
//    mSliderValueMap["Laser pps"] = pSlider;
//
//    bLaserControllerSet = true;
//
//}

void SettingsPanel::setLaserPreview3d( LaserPreview3D* laserPreview3D ){
    mLaserPreview3D = laserPreview3D;

    Gwen::Controls::Base* pSlider;
    Gwen::Controls::Base* pCheckBox;
//    Gwen::Controls::Base* pLabel;

    pSlider = addSlider(mLaserCat, getBounds(mLaserCatElements), "Laser Angle", mLaserPreview3D->getLaserAngle(), 0, 90 );
    mLaserCatElements.push_back(pSlider);
    
    
    pCheckBox = addCheckBox(mLaserPreviewCat, getBounds(mLaserPreviewCatElements), "Show Frame", mLaserPreview3D->paramsView.showFrame );
    mLaserPreviewCatElements.push_back(pCheckBox);
    
    pCheckBox = addCheckBox(mLaserPreviewCat, getBounds(mLaserPreviewCatElements), "Show Dots on Gauze", mLaserPreview3D->paramsView.showDotsOnGauze );
    mLaserPreviewCatElements.push_back(pCheckBox);

    pCheckBox = addCheckBox(mLaserPreviewCat, getBounds(mLaserPreviewCatElements), "Show Lines on Gauze", mLaserPreview3D->paramsView.showLinesOnGauze );
    mLaserPreviewCatElements.push_back(pCheckBox);

    pCheckBox = addCheckBox(mLaserPreviewCat, getBounds(mLaserPreviewCatElements), "Show Rays", mLaserPreview3D->paramsView.showRays );
    mLaserPreviewCatElements.push_back(pCheckBox);

    pCheckBox = addCheckBox(mLaserPreviewCat, getBounds(mLaserPreviewCatElements), "Show Fans", mLaserPreview3D->paramsView.showFans );
    mLaserPreviewCatElements.push_back(pCheckBox);
    
    pSlider = addSlider(mLaserPreviewCat, getBounds(mLaserPreviewCatElements), "Fans Intensity", mLaserPreview3D->paramsView.fansIntensity*100.0f, 0, 100 );
    mLaserPreviewCatElements.push_back(pSlider);


    
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////

Gwen::Controls::Base* SettingsPanel::addCheckBox( Gwen::Controls::Base* pControl , Rectf bounds, string name, bool selected){
    Gwen::Controls::CheckBoxWithLabel* labeled = new Gwen::Controls::CheckBoxWithLabel( pControl );
//    int px = bounds.getX1();
//    int py = bounds.getY1();
//    int w = bounds.getWidth();
//    labeled->SetName( name );
//    labeled->SetPos( px, py );
    labeled->Dock( Gwen::Pos::Top );
    labeled->SetMargin( Gwen::Margin(5,7,5,7) );
    labeled->SetHeight( 20 );
    labeled->Label()->SetText( name );
//    labeled->Label()->SetName( name );
    labeled->Checkbox()->SetChecked(selected);
    labeled->Checkbox()->SetName( name );
    labeled->Checkbox()->onCheckChanged.Add( this, &SettingsPanel::onCheckBoxLaserOutput );
    mSliderValueMap[name] = labeled;
    return labeled;
}

Gwen::Controls::Base* SettingsPanel::addSlider( Gwen::Controls::Base* pControl , Rectf bounds, string name, float value, float valueMin, float valueMax){
    
    
    Gwen::Controls::Base* cont = new Gwen::Controls::Base( pControl );
    cont->Dock( Gwen::Pos::Top );
    cont->SetMargin( Gwen::Margin(5,7,5,7) );
    cont->SetHeight( 38 );

    int px = 0;//bounds.getX1();
    int py = 0;//bounds.getY1();
    int w = bounds.getWidth();
    
    Gwen::Controls::Base* lbls = new Gwen::Controls::Base( cont );
    lbls->Dock( Gwen::Pos::Top );
    lbls->SetHeight( 20 );
    
    Gwen::Controls::Label* label = new Gwen::Controls::Label( lbls );
    label->Dock( Gwen::Pos::Left );
    label->SetText( name );
    label->SizeToContents();
//    label->SetPos( px, py );
    
    
    Gwen::Controls::Label* labelValue = new Gwen::Controls::Label( lbls );
//    labelValue->SizeToContents();
    labelValue->Dock( Gwen::Pos::Right );
    labelValue->SetWidth(w);
    labelValue->SetAlignment(Gwen::Pos::Right);
//    labelValue->SetPos( px, py );
    labelValue->SetText( toString(value) );
    
    Gwen::Controls::HorizontalSlider* pSlider = new Gwen::Controls::HorizontalSlider( cont );
    labelValue->Dock( Gwen::Pos::Top );
    pSlider->SetPos( px, py + 17 );
    pSlider->SetSize( w, 20 );
    pSlider->SetClampToNotches(false);
    pSlider->SetNotchCount( (valueMax-valueMin)/10 );
    pSlider->SetRange( valueMin, valueMax );
    pSlider->SetFloatValue( value );
    pSlider->SetName(name);
    pSlider->onValueChanged.Add( this, &SettingsPanel::onSliderLaserOutput );
        
    mLabelsMap[pSlider] = labelValue;
    mSliderValueMap[name] = pSlider;
    return pSlider;
}

Gwen::Controls::Base* SettingsPanel::addProperty( Gwen::Controls::Base* pControl , Rectf bounds, string name, int val){
    
    Gwen::Controls::Base* cont = new Gwen::Controls::Base( pControl );
    Gwen::Controls::Label* pLabelName = new Gwen::Controls::Label( cont );
    Gwen::Controls::Label* pLabelValue = new Gwen::Controls::Label( cont );
    
    cont->Dock( Gwen::Pos::Top );
    cont->SetMargin( Gwen::Margin(5,7,5,7) );
    cont->SetHeight( 20 );
    pLabelName->SetText( name );
    pLabelName->SetAlignment(Gwen::Pos::Left );
    pLabelName->Dock( Gwen::Pos::Left );
    pLabelName->SizeToContents();

    pLabelValue->Dock( Gwen::Pos::Right );
    pLabelValue->SetWidth( 300 );
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
    rect.set(10, h + 35, 200 + 10, 30);
    return rect;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    ACTIONS

void SettingsPanel::onSliderLaserOutput( Gwen::Controls::Base* pControl ){
    Gwen::Controls::Label* label = mLabelsMap[pControl];
    Gwen::Controls::Slider* pSlider = ( Gwen::Controls::Slider* ) pControl;
    label->SetValue( toString(( int ) pSlider->GetFloatValue()));
//    console() << label->GetValue().c_str() << "   Slider Value: " <<  ( float ) pSlider->GetFloatValue() << std::endl;
    
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
    else if (controlName.compare("Scanner Angle Max Input") == 0){
        float scale = pSlider->GetFloatValue()/(mIldaFrame->params.output.scannerAngleX);
//        float val = mIldaFrame->params.output.transform.scale.x * mIldaFrame->params.output.scannerAngleX * 100;
        mIldaFrame->params.output.transform.scale.x = scale;
        mIldaFrame->params.output.transform.scale.y = scale;
    }
    else if(controlName.compare("Fans Intensity") == 0){
        mLaserPreview3D->paramsView.fansIntensity = ( float ) pSlider->GetFloatValue() / 100.0;
    }
    else if(controlName.compare("Main speed") == 0){
        mMainController->getDataManager()->setMainSpeed( ( float ) ((int)pSlider->GetFloatValue())/100.0 );
    }
    
    
}

void SettingsPanel::onCheckBoxLaserOutput( Gwen::Controls::Base* pControl ){
    
    Gwen::Controls::CheckBox* pCheckBox = ( Gwen::Controls::CheckBox* ) pControl;
    string controlName = pControl->GetName().c_str();
    if (controlName.compare("Draw Lines") == 0){
        mIldaFrame->params.draw.lines = pCheckBox->IsChecked() == 1;
//        console() <<  "mIldaFrame->params.draw.lines : " << mIldaFrame->params.draw.lines << std::endl;
    }
    else if (controlName.compare("Show Frame") == 0){
        mLaserPreview3D->paramsView.showFrame = pCheckBox->IsChecked() == 1;
    }
    else if (controlName.compare("Draw Points") == 0){
        mIldaFrame->params.draw.points = pCheckBox->IsChecked() == 1;
    }
    else if (controlName.compare("Show Dots on Gauze") == 0){
        mLaserPreview3D->paramsView.showDotsOnGauze = pCheckBox->IsChecked() == 1;
    }
    else if (controlName.compare("Show Lines on Gauze") == 0){
        mLaserPreview3D->paramsView.showLinesOnGauze = pCheckBox->IsChecked() == 1;
    }
    else if (controlName.compare("Show Rays") == 0){
        mLaserPreview3D->paramsView.showRays = pCheckBox->IsChecked() == 1;
    }
    else if (controlName.compare("Show Fans") == 0){
        mLaserPreview3D->paramsView.showFans = pCheckBox->IsChecked() == 1;
    }
    
}

void SettingsPanel::onLaserButtonClick( Gwen::Controls::Base* pControl ){
    console() << "SettingsPanel::onLaserButtonClick " << std::endl;
    sOnLaserButtonClick();
}

void SettingsPanel::onEnableLaser(){
    mLaserButton->SetText("DISABLE LASER");    
}

void SettingsPanel::onDisableLaser(){
    mLaserButton->SetText("ENABLE LASER");
}


void SettingsPanel::updateValues(){

    updateValue("Show Frame",mLaserPreview3D->paramsView.showFrame);
    updateValue("Draw Points",mIldaFrame->params.draw.points);
    updateValue("Show Dots on Gauze",mLaserPreview3D->paramsView.showDotsOnGauze);
    updateValue("Show Lines on Gauze",mLaserPreview3D->paramsView.showLinesOnGauze);
    updateValue("Show Rays",mLaserPreview3D->paramsView.showRays);
    updateValue("Show Fans",mLaserPreview3D->paramsView.showFans);

    updateValue("Target Points Count",mIldaFrame->params.output.targetPointCount);
    updateValue("Blank Count",mIldaFrame->params.output.blankCount);
    updateValue("End Count",mIldaFrame->params.output.endCount);
//    updateValue("Laser pps",mIldaFrame->params.output.blankCount);
    updateValue("Laser Angle",mLaserPreview3D->getLaserAngle());
    float val = mIldaFrame->params.output.transform.scale.x * mIldaFrame->params.output.scannerAngleX;
    updateValue("Scanner Angle Max Input", toString(val) );
    updateValue("Fans Intensity",mLaserPreview3D->paramsView.fansIntensity*100.0f);
        
}

void SettingsPanel::updateValue(string str, bool value){
    if(mSliderValueMap.count(str)>0){
        static_cast<Gwen::Controls::CheckBoxWithLabel*>(mSliderValueMap[str])->Checkbox()->SetChecked( value );
    }
}
void SettingsPanel::updateValue(string str, float value){
    if(mSliderValueMap.count(str)>0){
        static_cast<Gwen::Controls::Slider*>(mSliderValueMap[str])->SetFloatValue( value );
        mLabelsMap[ mSliderValueMap[str] ]->SetText( toString( value ) );
    }
}
void SettingsPanel::updateValue(string str, int value){
    if(mSliderValueMap.count(str)>0){
        static_cast<Gwen::Controls::HorizontalSlider*>(mSliderValueMap[str])->SetFloatValue( value );
        mLabelsMap[ mSliderValueMap[str] ]->SetText( toString( value ) );
    }
}
void SettingsPanel::updateValue(string str, string value){
    if(mLabelsValueMap.count(str)>0){
        mLabelsValueMap[ str ]->SetText( value );
    }
}


