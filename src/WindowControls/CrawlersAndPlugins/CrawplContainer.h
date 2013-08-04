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
#include "Gwen/Controls/HorizontalSlider.h"

#include "cinder/gl/Fbo.h"
#include "cinder/Timeline.h"
#include "cinder/Utilities.h"

#include "DataController.h"
#include "BasePlugin.h"
#include "DataCrawler.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CrawplContainer : public Gwen::Controls::GroupBox {

public:
	
    CrawplContainer( Gwen::Controls::Base *parent );
    virtual ~CrawplContainer();
    virtual void Render( Gwen::Skin::Base* skin );
    void setName(string name);
    void setCrawler(DataCrawler* crawler);
//    void setPlugins(vector<BasePlugin*> plugins);
    void addPlugin( BasePlugin* plugin );
    void resize(bool doSmall);
	void update();
    float getHeight();

    
    virtual void OnMouseClickLeft( int x, int y, bool bDown );
    
    
public:
    
    Gwen::Event::Caller	onPress;

private:
    
    Gwen::Controls::Label*          mLabel;
    Gwen::Controls::Label*          mLabelBasePairs;
    Gwen::Controls::PropertyTree*   mProperties;
    
    bool                            bIsSmall;
    
    int                             mHeightSmall;
    int                             mHeightLarge;
    Anim<float>                     mHeightCurrent;
    int                             mWidth;
    string                          mName;
    DataCrawler*                    mDataCrawler;
	vector<BasePlugin*>             mPlugins;
};



