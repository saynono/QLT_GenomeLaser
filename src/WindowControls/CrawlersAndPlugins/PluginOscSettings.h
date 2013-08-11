//
//  PluginOscSettings.h
//  QLT_GenomeLaser
//
//  Created by say nono on 10.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once

#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/PropertyTree.h"
#include "Gwen/Controls/Property/ColorSelector.h"
#include "Gwen/Controls/Property/Checkbox.h"
#include "Gwen/Controls/Property/ComboBox.h"
#include "Gwen/Controls/DockBase.h"
#include "Gwen/Controls/CheckBox.h"
#include "Gwen/Controls/WindowControl.h"

#include "cinder/app/AppBasic.h"
#include "CinderGwen.h"
#include "cinder/Utilities.h"
#include "BasePlugin.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class PluginOscSettings : public Gwen::Controls::WindowControl{

public:
	
    PluginOscSettings( Gwen::Controls::Base* parent );
	void setup( OSCElement* element );

    Gwen::Event::Caller	onWindowClosed;
    
private:
    void OnOscChange(Gwen::Controls::Base* pControl);
    void OnButtonApply();
    void OnButtonCancel();
    void OnWindowClosed();

    OSCElement*                 mElement;
    
    Gwen::Controls::Property::Checkbox*   mCheckBox;
    Gwen::Controls::Button*     mButtonCancel;
    Gwen::Controls::Button*     mButtonApply;
    Gwen::Controls::Properties* mProperties;
    bool                        mChanged;
};



