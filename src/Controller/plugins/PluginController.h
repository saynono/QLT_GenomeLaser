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
#include "DataCrawler.h"
#include "DataSaver.h"
#include "BasePlugin.h"
#include "BitsAndLinesPlugin.h"
#include "WebsPlugin.h"
#include "BitsPlugin.h"
#include "PluginOSCController.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class PluginController{

public:
	
	void setup( vector<DataCrawler>* crawlers, DataSaver* dataSaver);
    void dispose();
	void update();
    
    void addPlugin( DataCrawler* crawler, BasePlugin* plugin );
    const ColouredShape2d& getShape( DataCrawler* crawler );
    map<int, vector<BasePlugin*> > getPluginsDirectory();
	
private:
    
    template<typename T> BasePlugin* createInstance() { return new T; }

    vector<BasePlugin*>                   mPlugins;
//    map< string, vector<BasePlugin*> >     mPluginsDirectory;
    map< int, vector<BasePlugin*> >     mPluginsDirectory;
    
    PluginOSCController         mOscController;
    int                         mAmountCrawlers;
    ColouredShape2d             mEmptyShape;


};



