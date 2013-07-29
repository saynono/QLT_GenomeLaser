//
//  PluginController.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "PluginController.h"

	
void PluginController::setup(){
    
    mTempPlugin1.setup();
    mTempPlugin2.setup();

	mPlugins.push_back(&mTempPlugin1);
	mPlugins.push_back(&mTempPlugin2);
    
}
	
void PluginController::update(){
}

const ColouredShape2d& PluginController::getShape( int crawlerID, const GenomeData::BasePairDataSet& dataSet ){
    // TODO this is not nice!
    return mPlugins[crawlerID%mPlugins.size()]->getShape(dataSet);
}