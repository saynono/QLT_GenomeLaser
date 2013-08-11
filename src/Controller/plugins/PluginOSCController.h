//
//  PluginOSCController.h
//  QLT_GenomeLaser
//
//  Created by say nono on 31.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once

//#include "boost/algorithm/string/classification.hpp"
#include <boost/algorithm/string.hpp>

#include "cinder/app/AppBasic.h"
#include "cinder/Utilities.h"

#include "OscListener.h"
#include "BasePlugin.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class PluginOSCController{

public:
	
	void setup();
    void dispose();
	void update();
	void draw();
    void registerPlugin( BasePlugin* bp );
    void onOscSettingsChange(OSCElement* element);
    
private:

    void        processMessage( const osc::Message& message );
    void        processPluginMessageDirect( const osc::Message& message, OSCElement* oscElement );
    void        processPluginMessage( const osc::Message& message, vector<string> tokens );
    void        processPluginMessageSingle( const osc::Message& message, BasePlugin* plugin );
    void        processPluginMessageGroup( const osc::Message& message, vector<BasePlugin*>* plugins );
    void        processInteralMessage( const osc::Message& message, vector<string> tokens );
        
    osc::Listener                         mOscListener;
    map<string, vector<BasePlugin*> >     mPluginsDirectory;

    map<string, OSCElement* >           mPluginsOSCMapping;
};



