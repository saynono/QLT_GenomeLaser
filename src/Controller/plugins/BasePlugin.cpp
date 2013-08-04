//
//  BasePlugin.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "BasePlugin.h"


BasePlugin::BasePlugin(string name){
    bIsActive = true;
    mPluginID = name;
    console() << "New Plugin : " << name << std::endl;
}
//
//void BasePlugin::dispose(){
//    
//}
//
////void BasePlugin::update(const GenomeData::BasePairDataSet& dataSet){
////    
////}
////
//const ColouredShape2d& BasePlugin::getShape(const GenomeData::BasePairDataSet& dataSet){
//    
//}

