//
//  PluginController.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "PluginController.h"
#include "ParticlePlugin.h"

void PluginController::setup( vector<DataCrawler>* crawlers, DataSaver* dataSaver ){
    mAmountCrawlers = crawlers->size();
    mOscController.setup( dataSaver );
    for(int i=0;i<crawlers->size()  ;i++){
        addPlugin( &crawlers->at(i), new PulsePlugin() );
        addPlugin( &crawlers->at(i), new ScannerPlugin() );
        addPlugin( &crawlers->at(i), new SwirlPlugin() );
        addPlugin( &crawlers->at(i), new BitsPlugin() );
        addPlugin( &crawlers->at(i), new WebsPlugin() );
        addPlugin( &crawlers->at(i), new ParticlePlugin() );
        addPlugin( &crawlers->at(i), new BitsAndLinesPlugin() );
        addPlugin( &crawlers->at(i), new OoliganLogo() );
        addPlugin( &crawlers->at(i), new BarsPlugin() );
    }
}

void PluginController::dispose(){
    for(int i=0;i<mPlugins.size();i++){
        mPlugins[i]->dispose();
    }
    mPlugins.clear();
    mOscController.dispose();
}

void PluginController::addPlugin( DataCrawler* crawler, BasePlugin* plugin ){
    plugin->setup();
    plugin->activate(mPluginsDirectory[ crawler->crawlerID ].size() == 0);
	mPlugins.push_back( plugin );
    mOscController.registerPlugin( plugin );
//    mPluginsDirectory[ plugin->pluginID() ].push_back( plugin );
    mPluginsDirectory[ crawler->crawlerID ].push_back( plugin );
    
}

void PluginController::update(){
    mOscController.update();
}

const ColouredShape2d& PluginController::getShape( DataCrawler* crawler ){
    mEmptyShape.clear();
    vector<BasePlugin*> v = mPluginsDirectory[crawler->crawlerID];
    vector<BasePlugin*>::iterator it ;
    for(it=v.begin();it!=v.end();++it){
        if( (*it)->isActivated() ){
            mEmptyShape.appendColouredShape2d( (*it)->getShape( crawler->dataSet ) );
        }
    }
    return mEmptyShape;
}

map<int, vector<BasePlugin*> > PluginController::getPluginsDirectory(){
    return mPluginsDirectory;
}
