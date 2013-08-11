//
//  MainMenu.h
//  QLT_GenomeLaser
//
//  Created by say nono on 10.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Label.h"
#include "Gwen/Controls/MenuStrip.h"

#include "cinder/app/AppBasic.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class MainMenu : public Gwen::Controls::MenuStrip {
    
public:
        
    MainMenu( Gwen::Controls::Base *parent );
    void setup();
    void onQuitApp( Base* pControl );
    
	void onSaveAppSettings( Base* pControl );
    void onLoadAppSettings( Base* pControl );
//    void onSavePluginSettings( Base* pControl );
//    void onLoadPluginSettings( Base* pControl );

    boost::signals2::signal<void(string)> sOnLoadAppSettings;
    boost::signals2::signal<void(string)> sOnSaveAppSettings;
//    boost::signals2::signal<void(string)> sOnLoadPlugSettings;
//    boost::signals2::signal<void(string)> sOnSavePlugSettings;
    
};



