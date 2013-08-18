//
//  CrawlerPluginsWindow.h
//  QLT_GenomeLaser
//
//  Created by say nono on 02.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once

#include "cinder/app/AppBasic.h"
#include "cinder/gl/Fbo.h"

#include "Gwen/Controls/ScrollControl.h"
#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/PropertyTree.h"
#include "Gwen/Controls/Property/ColorSelector.h"
#include "Gwen/Controls/Property/Checkbox.h"
#include "Gwen/Controls/Property/ComboBox.h"
#include "Gwen/Controls/DockBase.h"
#include "Gwen/Controls/ComboBox.h"
#include "Gwen/Controls/TabControl.h"
#include "Gwen/Controls/CollapsibleList.h"
#include "Gwen/Controls/CollapsibleCategory.h"
#include "Gwen/Controls/RadioButtonController.h"
#include "Gwen/Controls/VerticalSlider.h"
#include "Gwen/Controls/HorizontalSlider.h"
#include "Gwen/Controls/CheckBox.h"
#include "Gwen/Controls/WindowControl.h"
//#include "MultiPropertyBox.h"

#include "MainController.h"
#include "DataController.h"
#include "PluginController.h"
#include "CrawplContainer.h"
#include "PluginOscSettings.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class CrawlerPluginsWindow : public Gwen::Controls::ScrollControl {

public:
	
	CrawlerPluginsWindow( Gwen::Controls::Base *parent );
	virtual ~CrawlerPluginsWindow();
    
	virtual void Render( Gwen::Skin::Base* skin );
    
    void update();
    
    void setMainController( MainController* mc );
    void onOpenOscSettings( OSCElement* element);
//    void setDataController( DataController* d );

private:
    
    bool                        bLayerSet;
    bool                        bDataControllerSet;
    DataController*             mDataController;
    MainController*             mMainController;
    PluginController*           mPluginController;
    Gwen::Controls::PropertyTree*   mPropTree;
    Gwen::Controls::CollapsibleList*  mCrawlerList;
    
    vector<CrawplContainer*>    mCrawplContainer;
    Gwen::Controls::Base*       pTestArea;
	
};



