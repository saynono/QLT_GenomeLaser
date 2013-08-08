//
//  CrawplContainer.h
//  QLT_GenomeLaser
//
//  Created by say nono on 02.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once

#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/GroupBox.h"
#include "Gwen/Controls/PropertyTree.h"
//#include "Gwen/Controls/PropertyNode.h"
#include "Gwen/Controls/HorizontalSlider.h"
#include "Gwen/Controls/ListBox.h"
#include "PropertyControlSlider.h"

#include "cinder/gl/Fbo.h"
#include "cinder/Timeline.h"
#include "cinder/Utilities.h"

#include "DataController.h"
#include "BasePlugin.h"
#include "DataCrawler.h"
#include "Gwen/Controls/Properties.h"
#include "Gwen/Utility.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CrawplContainer: public Gwen::Controls::Base{

public:
	
    CrawplContainer( Gwen::Controls::Base* parent );
    virtual ~CrawplContainer();
    virtual void Render( Gwen::Skin::Base* skin );
    void setName(string name);
    void setCrawler(DataCrawler* crawler);
//    void setPlugins(vector<BasePlugin*> plugins);
    void addPlugin( BasePlugin* plugin );
	void update();
    
    void displayPluginSettings( BasePlugin* plugin);
    void createPluginSettings( BasePlugin* plugin);
    
    virtual void OnMouseClickLeft( int x, int y, bool bDown );
    void onSliderChange( Gwen::Controls::Base* pControl );
    void onRowSelected();
    
public:
    
    Gwen::Event::Caller	onPress;

private:
    
    Gwen::Controls::Label*          mLabel;
    Gwen::Controls::Label*          mLabelBasePairs;
    Gwen::Controls::Label*          mLabelDescription;
    Gwen::Controls::ListBox*        mPluginList;
    Gwen::Controls::ListBox*        mValueList;
    
    string                          mName;
    DataCrawler*                    mDataCrawler;
	vector<BasePlugin*>             mPlugins;
    map<Gwen::Controls::Slider*, OSCElement*> mValueMap;
    map<Gwen::Controls::Layout::TableRow*, BasePlugin*> mPluginsRowMap;
    map<BasePlugin*, Gwen::Controls::ListBox*> mPluginsListBoxMap;
};



