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

#include "MainController.h"
#include "DataController.h"
#include "PluginController.h"
#include "CrawplContainer.h"

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
    void setDataController( DataController* d );

private:
    
    bool                        bLayerSet;
    bool                        bDataControllerSet;
    DataController*             mDataController;
    MainController*             mMainController;
    PluginController*           mPluginController;
    
    vector<CrawplContainer*>    mCrawplContainer;
    Gwen::Controls::Base*       pTestArea;
	
};



