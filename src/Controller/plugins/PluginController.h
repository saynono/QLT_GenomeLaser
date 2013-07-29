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

using namespace ci;
using namespace ci::app;
using namespace std;

class PluginController{

public:
	
	void setup();
	void update();
    const ColouredShape2d& getShape( int crawlerID, const GenomeData::BasePairDataSet& dataSet );

	
private:
    
    BitsAndLinesPlugin          mTempPlugin1;
    BitsAndLinesPlugin          mTempPlugin2;

    vector<BasePlugin*>         mPlugins;
    
};



