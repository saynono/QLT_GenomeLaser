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
#include "Gwen/Controls/WindowControl.h"


//#include "cinderSyphon.h"

#include "ColourCorrectionWindow.h"
#include "PreviewWindow.h"
#include "Preview3DWindow.h"
#include "CircularDataWindow.h"
#include "CrawlerPluginsWindow.h"

#include "SettingsPanel.h"
#include "LaserPreview3D.h"
#include "CircularDataLayer.h"
#include "DataController.h"

#include "CinderIldaFrame.h"

#include "MainController.h"
#include "ViewManager.h"
#include "PluginController.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class WindowManager: public Gwen::Event::Handler{

public:
	
	void setup( MainController* mc, ViewManager* vm );
    void setMainController( MainController* mc );
    void setViewManager( ViewManager* vm );
	void update();
	void draw();
    
    void saveSettings();
    
    ColourCorrectionWindow* getColorValueController();

    void setPreviewFbo( ci::gl::Fbo* fbo );
    void setIldaFrameRef( ciilda::Frame* frame );
    void setLaserController(ciilda::LaserController* controller);
    void setLaserPreview3d( LaserPreview3D* laserPreview3D );
    void setCircularDataLayer( CircularDataLayer* circularDataLaser );
    void setDataController(DataController* d);
    void setPluginController(PluginController* d);
    LaserPreview3D* getLaserPreview3d();
    void reloadSkin();
    
private:
    
    void setupMainArea();
    void addPreviewWindow();
    void addPreview3DWindow();
    void addCircularDataWindow();
    void addSettingsList();
    void addColourCorrectionWindow();
    void addCrawlerPluginWindow();
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
    Gwen::Controls::CrossSplitter* m_Splitter;
    
    MainController*             mMainController;
    ViewManager*                mViewManager;
    PreviewWindow*              pPreviewControl;
    Preview3DWindow*            pPreview3DControl;
    CircularDataWindow*         pCircularControl;
    CrawlerPluginsWindow*       pCrawlerPluginWindow;
    ColourCorrectionWindow*     pColourControl;
    
    Gwen::Controls::Label*      pStatusFPSLabel;
    Gwen::Controls::Label*      pStatusBuildLabel;
    SettingsPanel*              mSettingsControl;
        
    XmlTree                     mSettingsSaver;
    
    ci::gl::Fbo*                mPreviewFbo;
    string                      mRenderDate;
    
    
//    syphonServer                mSyphonClient;

};



