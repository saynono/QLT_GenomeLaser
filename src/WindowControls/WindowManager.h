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
#include "cinder/gl/Fbo.h"

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
#include "Gwen/Controls/StatusBar.h"
#include "Gwen/Controls/Label.h"

#include "ColourCorrectionWindow.h"
#include "PreviewWindow.h"
#include "Preview3DWindow.h"
#include "SettingsPanel.h"


#include "CinderIldaFrame.h"

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

    void setPreviewFbo(ci::gl::Fbo* fbo);
    void setIldaFrame(ciilda::Frame* frame);
    void setLaserController(ciilda::LaserController* controller);
    
private:
    
    void addPreviewWindow();
    void addPreview3DWindow();
    void addSettingsList();
    void addColourCorrectionWindow();
    void createMainControls();
    
	cigwen::GwenRendererGl*     mRenderer;
	cigwen::GwenInputRef        mGwenInput;
	Gwen::Controls::Canvas*     mCanvas;
    PreviewWindow*              pPreviewControl;
    Preview3DWindow*            pPreview3DControl;
    ColourCorrectionWindow*     pColourControl;
    Gwen::Controls::Label*      pStatusFPSLabel;
    Gwen::Controls::Label*      pStatusBuildLabel;
    SettingsPanel*              mSettingsControl;
        
    XmlTree                     mSettingsSaver;
    
    ci::gl::Fbo*                mPreviewFbo;
    string                      mRenderDate;
    
};



