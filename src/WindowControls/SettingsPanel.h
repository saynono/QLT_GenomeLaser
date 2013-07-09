//
//  SettingsPanel.h
//  QLT_GenomeLaser
//
//  Created by say nono on 06.07.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once

#include <stdlib.h>

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

#include "CinderIldaFrame.h"
#include "CinderLaserDac.h"
#include "ColourCorrectionWindow.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SettingsPanel : public Gwen::Controls::DockBase {

public:
	
    SettingsPanel( Gwen::Controls::Base *parent );
    virtual ~SettingsPanel();
    
	virtual void Render( Gwen::Skin::Base* skin );
	virtual void RenderUnder( Gwen::Skin::Base* skin );

	void setup();
	void update();
	void draw();
    
    void setIldaFrame(ciilda::Frame* frame);
    void setLaserController(ciilda::LaserController* controller);
    
private:

    void onSliderLaserOutput( Base* pControl );
    void onCheckBoxLaserOutput( Base* pControl );
    Gwen::Controls::Base* addCheckBox( Base* pControl , Rectf bounds, string name, bool selected);
    Gwen::Controls::Base* addSlider( Base* pControl , Rectf bounds, string name, int value, int valueMin, int valueMax);
    Gwen::Controls::Base* addProperty( Base* pControl , Rectf bounds, string name, int val);
    Rectf getBounds(const vector<Gwen::Controls::Base*>& vec);
    
    
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    
    ciilda::Frame*                              mIldaFrame;
    ciilda::LaserController*                    mLaserController;

    
    Gwen::Controls::CollapsibleCategory*        mLaserCat;
    Gwen::Controls::CollapsibleCategory*        mLaserStatsCat;
    
    vector<Gwen::Controls::Base*>                               mLaserCatElements;
    vector<Gwen::Controls::Base*>                               mLaserStatsCatElements;
    map<Gwen::Controls::Base*,Gwen::Controls::Label*>           mLabelsMap;
    map<string,Gwen::Controls::Label*>                          mLabelsValueMap;
    
    bool                                        bIldaFrameSet;
    bool                                        bLaserControllerSet;
    
};


