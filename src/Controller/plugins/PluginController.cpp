//
//  PluginController.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "PluginController.h"
#include "ParticlePlugin.h"

void PluginController::setup(int amount){
    mAmountCrawlers = amount;
    mOscController.setup();
    for(int i=0;i<amount;i++){
        addPlugin( new BitsAndLinesPlugin() );
        addPlugin( new ParticlePlugin() );
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
    plugin->activate(mPluginsDirectory[ plugin->pluginID() ].size() == 0);
	mPlugins.push_back( plugin );
    mOscController.registerPlugin( plugin );
    mPluginsDirectory[ plugin->pluginID() ].push_back( plugin );
}

void PluginController::update(){
    mOscController.update();
}

const ColouredShape2d& PluginController::getShape( DataCrawler* crawler ){
    mEmptyShape.clear();
    map<string, vector<BasePlugin*> >::iterator it ;
    for(it=mPluginsDirectory.begin();it!=mPluginsDirectory.end();++it){
        if( (*it).second[crawler->crawlerID]->isActivated() ) mEmptyShape.appendColouredShape2d( mPlugins[crawler->crawlerID]->getShape( crawler->dataSet ) );
    }
    return mEmptyShape;
}

map<string, vector<BasePlugin*> > PluginController::getPluginsDirectory(){
    return mPluginsDirectory;
}
