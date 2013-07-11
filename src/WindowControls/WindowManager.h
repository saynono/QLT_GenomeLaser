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
#include "Gwen/Controls/CrossSplitter.h"
#include "Gwen/Controls/Layout/Position.h"

#include "ColourCorrectionWindow.h"
#include "PreviewWindow.h"
#include "Preview3DWindow.h"
#include "SettingsPanel.h"
#include "LaserPreview3D.h"


#include "CinderIldaFrame.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class WindowManager: public Gwen::Event::Handler{

public:
	
	void setup();
	void update();
	void draw();
    
    void saveSettings();
    
    ColourCorrectionWindow* getColorValueController();

    void setPreviewFbo(ci::gl::Fbo* fbo);
    void setIldaFrame(ciilda::Frame* frame);
    void setLaserController(ciilda::LaserController* controller);
    void setLaserPreview3d( LaserPreview3D* laserPreview3D );
    
private:
    
    void setupMainArea();
    void addPreviewWindow();
    void addPreview3DWindow();
    void addSettingsList();
    void addColourCorrectionWindow();
    void createMainControls();
    
//    void ZoomTest( Gwen::Controls::Base* pFromPanel );
    void showAllPanels( Gwen::Controls::Base* pFromPanel );
//    void CenterPanels( Gwen::Controls::Base* pFromPanel );
    
    void zoomToPanel( Gwen::Event::Info info );
    
	cigwen::GwenRendererGl*     mRenderer;
	cigwen::GwenInputRef        mGwenInput;
	Gwen::Controls::Canvas*     mCanvas;
    Gwen::Controls::Base*       mMainArea;
    Gwen::Controls::DockBase*   mTotalWindowArea;
    PreviewWindow*              pPreviewControl;
    Preview3DWindow*            pPreview3DControl;
    ColourCorrectionWindow*     pColourControl;
//    LaserPreview3D*             mLaserPreview3D;
    Gwen::Controls::Label*      pStatusFPSLabel;
    Gwen::Controls::Label*      pStatusBuildLabel;
    SettingsPanel*              mSettingsControl;
        
    XmlTree                     mSettingsSaver;
    
    ci::gl::Fbo*                mPreviewFbo;
    string                      mRenderDate;
    
    Gwen::Controls::CrossSplitter* m_Splitter;
    
    
};



