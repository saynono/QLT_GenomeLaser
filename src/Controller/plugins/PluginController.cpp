//
//  PluginController.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "PluginController.h"

	
void PluginController::setup(){
    
    mOscController.setup();
    
    mTempPlugin1.setup();
    mTempPlugin2.setup();
    mTempPlugin3.setup();
    mTempPlugin4.setup();
    mTempPlugin5.setup();

    addPlugin(&mTempPlugin1);
    addPlugin(&mTempPlugin2);
    addPlugin(&mTempPlugin3);
    addPlugin(&mTempPlugin4);
    addPlugin(&mTempPlugin5);
    
}

void PluginController::dispose(){
    for(int i=0;i<mPlugins.size();i++){
        mPlugins[i]->dispose();
    }
    mPlugins.clear();
    mOscController.dispose();
}

void PluginController::addPlugin( BasePlugin* plugin ){
	mPlugins.push_back( plugin );
    mOscController.registerPlugin( plugin );
}

void PluginController::update(){
    mOscController.update();
}

const ColouredShape2d& PluginController::getShape( int crawlerID, const GenomeData::BasePairDataSet& dataSet ){
    // TODO this is not nice!
    return mPlugins[crawlerID%mPlugins.size()]->getShape(dataSet);
}