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
	
	void setup(int amount);
    void dispose();
	void update();
    void addPlugin( BasePlugin* plugin );
    const ColouredShape2d& getShape( int crawlerID, const GenomeData::BasePairDataSet& dataSet );
    map<string, vector<BasePlugin*> > getPluginsDirectory();
	
private:
    
    template<typename T> BasePlugin* createInstance() { return new T; }

    vector<BasePlugin*>                   mPlugins;
    map<string, vector<BasePlugin*> >     mPluginsDirectory;
    
    PluginOSCController         mOscController;

};



