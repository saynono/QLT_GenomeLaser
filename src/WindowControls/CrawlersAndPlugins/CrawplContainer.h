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
#include "cinder/gl/Fbo.h"

#include "DataController.h"
#include "BasePlugin.h"
#include "DataCrawler.h"

using namespace ci;
using namespace ci::app;
using namespace std;



class CrawplContainer : public Gwen::Controls::Base {

public:
	
    CrawplContainer( Gwen::Controls::Base *parent );
    virtual ~CrawplContainer();
    virtual void Render( Gwen::Skin::Base* skin );
    void setName(string name);
    void setCrawler(const DataCrawler& crawler);
    void setPlugins(const vector<BasePlugin*>& plugins);
	void update();

private:
    
    Gwen::Controls::Label*          mLabel;
//    const DataCrawler               mDataCrawler;
//	const vector<BasePlugin*>       mPlugins;
};



