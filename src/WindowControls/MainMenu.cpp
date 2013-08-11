//
//  MainMenu.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 10.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "MainMenu.h"

MainMenu::MainMenu( Gwen::Controls::Base *parent )
: Gwen::Controls::MenuStrip( parent, "MenuStrip" )
{
    
    setup();
}
	
void MainMenu::setup(){
    
    {
        Gwen::Controls::MenuItem* pRoot = this->AddItem( L"Application" );
        pRoot->GetMenu()->AddItem( L"Load Settings", "", "Ctrl+L" )->SetAction( this, &MainMenu::onLoadAppSettings );
        pRoot->GetMenu()->AddItem( L"Save Settings", "", "CTRL+S" )->SetAction( this, &MainMenu::onSaveAppSettings );
        pRoot->GetMenu()->AddItem( L"Quit", "", "Ctrl+Q" )->SetAction( this, &MainMenu::onQuitApp );
    }
    {
        Gwen::Controls::MenuItem* pRoot = this->AddItem( L"Plugins" );
        pRoot->GetMenu()->AddItem( L"Load Settings" )->SetAction( this, &MainMenu::onLoadPluginSettings );
        pRoot->GetMenu()->AddItem( L"Save Settings" )->SetAction( this, &MainMenu::onSavePluginSettings );
    }
}

void MainMenu::onSaveAppSettings( Base* pControl ){
    sOnSaveAppSettings("QLT_Settings.xml");
}
void MainMenu::onLoadAppSettings( Base* pControl ){
    sOnLoadAppSettings("QLT_Settings.xml");
}
void MainMenu::onSavePluginSettings( Base* pControl ){
    sOnSavePlugSettings("QLT_Plugin_Settings.xml");
}
void MainMenu::onLoadPluginSettings( Base* pControl ){
    sOnLoadPlugSettings("QLT_Plugin_Settings.xml");
}

void MainMenu::onQuitApp( Base* pControl )
{
    AppBasic::get()->quit();
}
