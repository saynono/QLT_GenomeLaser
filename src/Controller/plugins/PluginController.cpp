//
//  PluginController.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "PluginController.h"

	
void PluginController::setup(int amount){
    mOscController.setup();
    for(int i=0;i<amount;i++){
        addPlugin( new BitsAndLinesPlugin() );
    }
}

void PluginController::dispose(){
    for(int i=0;i<mPlugins.size();i++){
        mPlugins[i]->dispose();
    }
    mPlugins.clear();
    mOscController.dispose();
}

void PluginController::addPlugin( BasePlugin* plugin ){
    plugin->setup();
	mPlugins.push_back( plugin );
    mOscController.registerPlugin( plugin );
    mPluginsDirectory[ plugin->pluginID() ].push_back( plugin );
}

void PluginController::update(){
    mOscController.update();
}

const ColouredShape2d& PluginController::getShape( int crawlerID, const GenomeData::BasePairDataSet& dataSet ){
    // TODO this is not nice!
    return mPlugins[crawlerID%mPlugins.size()]->getShape(dataSet);
}

map<string, vector<BasePlugin*> > PluginController::getPluginsDirectory(){
    return mPluginsDirectory;
}
