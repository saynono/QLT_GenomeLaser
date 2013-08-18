//
//  BasePlugin.h
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"

#include "OscMessage.h"

#include "GenomeData.h"
#include "ColouredShape2d.h"

using namespace ci;
using namespace ci::app;
using namespace std;

// forward declaration of BasePlugin
class BasePlugin;

class OSCElement{

public:
    
    enum OSCElementTypes {
        FLOAT = 0,
        INTEGER,
        BANG
    };
    
    OSCElement(){};
    OSCElement( BasePlugin* plug, void* p, OSCElementTypes t ){
        plugin = plug; pointer = p; type = t; minValue = numeric_limits<float>::min(); maxValue = numeric_limits<float>::max();
    };
    OSCElement( BasePlugin* plug, void* p, OSCElementTypes t, float minVal, float maxVal) {
        plugin = plug; pointer = p; type = t; minValue = minVal; maxValue = maxVal;
    };
    BasePlugin*     plugin;
    void*           pointer;
    OSCElementTypes type;
    float           minValue;
    float           maxValue;
    
};

class BasePlugin{

public:
    
    virtual ~BasePlugin(){};
	virtual void setup(){};
    virtual void dispose(){};
    virtual const ColouredShape2d& getShape(const GenomeData::BasePairDataSet& dataSet) = 0;//{return ColouredShape2d(); };
	
    virtual void onActivated(){};
    virtual void onDeActivated(){};
    
    virtual const map<string, OSCElement*>& getOSCMapping() {};
    virtual void processOSCMessage( const osc::Message& message ) {};

    const string pluginID() { return mPluginID;};

    void activate(bool b){ bIsActive = b; };
    bool isActivated(){ return bIsActive; };
    
protected:
    
    BasePlugin( string name = "BasePlugin" );
    
    bool            bIsActive;
    string          mPluginID;
    
};



