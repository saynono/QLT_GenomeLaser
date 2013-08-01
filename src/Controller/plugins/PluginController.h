//
//  PluginController.h
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "cinder/app/AppBasic.h"
#include "GenomeData.h"
#include "BasePlugin.h"
#include "BitsAndLinesPlugin.h"
#include "PluginOSCController.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class PluginController{

public:
	
	void setup();
    void dispose();
	void update();
    void addPlugin( BasePlugin* plugin );
    const ColouredShape2d& getShape( int crawlerID, const GenomeData::BasePairDataSet& dataSet );

	
private:
    
    PluginOSCController         mOscController;
    
    
    BitsAndLinesPlugin          mTempPlugin1;
    BitsAndLinesPlugin          mTempPlugin2;
    BitsAndLinesPlugin          mTempPlugin3;
    BitsAndLinesPlugin          mTempPlugin4;
    BitsAndLinesPlugin          mTempPlugin5;

    vector<BasePlugin*>                 mPlugins;
    map<string, vector<BasePlugin*> >     mPluginsDirectory;
    
};



