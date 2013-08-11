//
//  DataSaver.h
//  QLT_GenomeLaser
//
//  Created by say nono on 10.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "cinder/app/AppBasic.h"
#include "cinder/Xml.h"

#include "DataController.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class DataSaver{

public:
	
	void setup();
    void update();
    void loadAppSettings(string path);
    void saveAppSettings(string path);
    void parseAppSettings(XmlTree data);
    void gatherAppSettings(XmlTree* data);
    
    void loadPluginSettings(string path);
    void savePluginSettings(string path);
	
//    boost::signals2::signal<void(OSCElement*)> sSave;
//    boost::signals2::signal<vector<float>(void)> sSaveAppSettings;
    
    boost::signals2::signal< map<string, string>(void)> sGetApplicationData;
//    boost::signals2::signal< int(void)> sGetApplicationData;
    
    
private:
    
    bool        bDoSaveAppSettings;

};



