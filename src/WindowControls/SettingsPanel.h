//
//  SettingsPanel.h
//  QLT_GenomeLaser
//
//  Created by say nono on 06.07.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <stdlib.h>
#include <boost/algorithm/string.hpp>

#include "cinder/Xml.h"

#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/DockBase.h"
#include "Gwen/Controls/ComboBox.h"
#include "Gwen/Controls/TabControl.h"
#include "Gwen/Controls/CollapsibleList.h"
#include "Gwen/Controls/CollapsibleCategory.h"
#include "Gwen/Controls/RadioButtonController.h"
#include "Gwen/Controls/VerticalSlider.h"
#include "Gwen/Controls/HorizontalSlider.h"
#include "Gwen/Controls/CheckBox.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/Button.h"

#include "CinderIldaFrame.h"
#include "CinderLaserDac.h"
#include "ColourCorrectionWindow.h"
#include "LaserPreview3D.h"
#include "MainController.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SettingsPanel: public Gwen::Event::Handler {

public:
	
    SettingsPanel();
    ~SettingsPanel();
    
	void setup( Gwen::Controls::DockBase *parent );
	void update();
	void draw();
    
    void setIldaFrame(ciilda::Frame* frame);
//    void setLaserController(ciilda::LaserController* controller);
    void setLaserPreview3d( LaserPreview3D* laserPreview3D );
    void setOutputOptions( MainController* mc );
    
    void updateValues();
    
    void onEnableLaser();
    void onDisableLaser();
    
public:
    
    Gwen::Event::Caller	onPress;
    boost::signals2::signal<void(void)> sOnLaserButtonClick;
    
    
private:

    void onSliderLaserOutput( Gwen::Controls::Base* pControl );
    void onCheckBoxLaserOutput( Gwen::Controls::Base* pControl );
    void onLaserButtonClick( Gwen::Controls::Base* pControl );
    Gwen::Controls::Base* addCheckBox( Gwen::Controls::Base* pControl , Rectf bounds, string name, bool selected);
    Gwen::Controls::Base* addSlider( Gwen::Controls::Base* pControl , Rectf bounds, string name, float value, float valueMin, float valueMax);
    Gwen::Controls::Base* addProperty( Gwen::Controls::Base* pControl , Rectf bounds, string name, int val);
    Rectf getBounds(const vector<Gwen::Controls::Base*>& vec);
    
    void updateValue(string str, float value);
    void updateValue(string str, bool value);
    void updateValue(string str, int value);
    void updateValue(string str, string value);
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    MainController*                             mMainController;
    
    ciilda::Frame*                              mIldaFrame;
    ciilda::LaserController*                    mLaserController;
    
    LaserPreview3D*                             mLaserPreview3D;
    
    Gwen::Controls::Button*                     mLaserButton;

    
    Gwen::Controls::CollapsibleCategory*        mLaserCat;
    Gwen::Controls::CollapsibleCategory*        mLaserStatsCat;
    Gwen::Controls::CollapsibleCategory*        mLaserPreviewCat;
    Gwen::Controls::CollapsibleCategory*        mLaserColourCorCat;
    
    vector<Gwen::Controls::Base*>                               mLaserCatElements;
    vector<Gwen::Controls::Base*>                               mLaserStatsCatElements;
    vector<Gwen::Controls::Base*>                               mLaserPreviewCatElements;
    map<Gwen::Controls::Base*,Gwen::Controls::Label*>           mLabelsMap;
    map<string,Gwen::Controls::Label*>                          mLabelsValueMap;
    map<string,Gwen::Controls::CheckBoxWithLabel*>              mCheckboxValueMap;
    map<string,Gwen::Controls::Base*>                           mSliderValueMap;
    
    bool                                        bIldaFrameSet;
    bool                                        bLaserControllerSet;
    
};



