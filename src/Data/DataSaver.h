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

class DataElement{
    
public:
    enum VarTypes {
        FLOAT = 0,
        INTEGER,
        STRING,
        BOOLEAN
    };
    DataElement(){};
    DataElement(string n, void* p, VarTypes t){ name=n;pointer=p;type=t; };
    string          name;
    void*           pointer;
    VarTypes        type;
};

class DataSaver{

public:
	
	void setup();
    void update();
    void loadAppSettings(string path);
    void saveAppSettings(string path);
    void parseAppSettings(XmlTree data);
    
    void registerVariable(DataElement data);
    
    map<string, DataElement> mDataElements;
    
    boost::signals2::signal<void(void)> sOnLoadedSettings;
    
private:
    
    
    int getSettingInteger(string id);
    float getSettingFloat(string id, float default_val=0.f);
    string getSettingString(string id);
    bool getSettingBoolean(string id, bool default_val=false);
    string getSetting(string id);

    XmlTree     mXmlSettings;
};



