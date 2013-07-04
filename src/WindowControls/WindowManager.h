//
//  WindowManager.h
//  LaserGateway
//
//  Created by say nono on 18.03.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once


#include "cinder/app/AppBasic.h"
#include "cinder/Xml.h"

#include "cigwen/GwenRendererGl.h"
#include "cigwen/GwenInput.h"
#include "cigwen/CinderGwen.h"

#include "Gwen/Skins/Simple.h"
#include "Gwen/Skins/TexturedBase.h"
#include "Gwen/Controls/TabControl.h"
#include "Gwen/Controls/DockBase.h"
#include "Gwen/Controls/Button.h"
#include "Gwen/Controls/WindowControl.h"
#include "Gwen/Controls/CollapsibleList.h"
#include "Gwen/Controls/CollapsibleCategory.h"

#include "ColourCorrectionWindow.h"
#include "PreviewWindow.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class WindowManager{

public:
	
	void setup();
	void update();
	void draw();
    
    void saveSettings();
    
    ColourCorrectionWindow* getColorValueController();

private:
    
    void addPreviewWindow();
    void addSettingsList();
    void addColourCorrectionWindow();
    void createMainControls();
    
	cigwen::GwenRendererGl*     mRenderer;
	cigwen::GwenInputRef        mGwenInput;
	Gwen::Controls::Canvas*     mCanvas;
    PreviewWindow*              pPreviewControl;
    ColourCorrectionWindow*     pColourControl;
        
    XmlTree                     mSettingsSaver;
    
};



