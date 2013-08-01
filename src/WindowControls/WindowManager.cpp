//
//  WindowManager.cpp
//  LaserGateway
//
//  Created by say nono on 18.03.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "WindowManager.h"

	
void WindowManager::setup( MainController* mc, ViewManager* vm ){
    mRenderDate = "BUILD " + toString(__DATE__) + " " + toString(__TIME__) + "  CINDER VERSION " + CINDER_VERSION_STR;
    createMainControls();
    addSettingsList();
    addPreviewWindow();
    addPreview3DWindow();
//    addColourCorrectionWindow();
    addCircularDataWindow();
    
    setMainController( mc );
    setViewManager( vm );
}

//---------------------------------------------------------------------------------------------------------

void WindowManager::setMainController( MainController* mc ){
    mMainController = mc;
    setDataController( mMainController->getDataController() );
    setIldaFrameRef( mMainController->getFrameRef() );
}

void WindowManager::setViewManager( ViewManager* vm ){
    mViewManager = vm;
    mViewManager->getLaserPreview3D()->getTexture();
    setPreviewFbo( mViewManager->getLaserPreview3D()->getTexture() );
    setLaserPreview3d( mViewManager->getLaserPreview3D() );
    setCircularDataLayer( mViewManager->getCircularDataLayer() );
}


//---------------------------------------------------------------------------------------------------------

void WindowManager::update(){
	mSettingsControl->update();
    pPreview3DControl->update();
    pStatusFPSLabel->SetText( toString((int)getFrameRate()) + " FPS        ");
}

void WindowManager::draw(){
    mCanvas->RenderCanvas();
}

//---------------------------------------------------------------------------------------------------------

void WindowManager::createMainControls(){
    
	getWindow()->setTitle( "QLT GenomeLaser v1.1" );
    
	mRenderer = new cigwen::GwenRendererGl();
	mRenderer->Init();
    
	Gwen::Skin::TexturedBase* skin = new Gwen::Skin::TexturedBase( mRenderer );
//    skin->Init( "DefaultSkin.png" );
//    skin->Init( "obscureskin.png" );
    skin->Init( "skins/GenomeLaserSkin.png" );
    
	mCanvas = new Gwen::Controls::Canvas( skin );
	mCanvas->SetSize( getWindowWidth(), getWindowHeight() - 24 );
	mCanvas->SetDrawBackground( true );
	mCanvas->SetBackgroundColor( cigwen::toGwen( ci::Color( 0x26/255.f,0x27/255.f,0x26/255.f ) ) );
    mCanvas->Dock( Gwen::Pos::Fill );
        
	mGwenInput = cigwen::GwenInput::create( mCanvas );
    
    mTotalWindowArea = new Gwen::Controls::DockBase( mCanvas );
    mTotalWindowArea->Dock( Gwen::Pos::Fill );
    
    setupMainArea();

    
//    Dock( Pos::Fill );
    Gwen::Controls::StatusBar* pStatus = new Gwen::Controls::StatusBar( mTotalWindowArea );
    pStatusBuildLabel = new Gwen::Controls::Label( pStatus );
    pStatusBuildLabel->SetText( mRenderDate );
    pStatusBuildLabel->SetWidth(300);
    pStatusFPSLabel = new Gwen::Controls::Label( pStatus );
    pStatusFPSLabel->SetText( "000 FPS" );
    pStatusFPSLabel->SetWidth(300);
    pStatusFPSLabel->SetAlignment( Gwen::Pos::Right );
    pStatus->SetPadding(Gwen::Padding( 10,5,10,5 ));
    pStatus->AddControl( pStatusBuildLabel, false );
    pStatus->SetPadding( Gwen::Padding( 10,5,10,5 ));
    pStatus->AddControl( pStatusFPSLabel, true );
    pStatus->SendToBack();
}

void WindowManager::setupMainArea(){
    
    mMainArea = new Gwen::Controls::Base( mTotalWindowArea );
	Gwen::Controls::Layout::Center* pCenter = new Gwen::Controls::Layout::Center( mTotalWindowArea );
	pCenter->Dock( Gwen::Pos::Fill );
    
    m_Splitter = new Gwen::Controls::CrossSplitter( pCenter );
    m_Splitter->SetPos( 0, 0 );
    m_Splitter->Dock( Gwen::Pos::Fill );
    m_Splitter->SetSplitterSize(2);
    {
        Gwen::Controls::Label* testButton =  new Gwen::Controls::Label( m_Splitter );
        testButton->SetText( "BOTTOMRIGHT" );
        m_Splitter->SetPanel( 3, testButton );
    }
    {
        Gwen::Controls::Label* testButton =  new Gwen::Controls::Label( m_Splitter );
        testButton->SetText( "BOTTOMLEFT" );
        m_Splitter->SetPanel( 2, testButton );
    }
    //Status bar to hold unit testing buttons
    Gwen::Controls::StatusBar* pStatus = new Gwen::Controls::StatusBar( pCenter );
    pStatus->Dock( Gwen::Pos::Bottom );
    {
        Gwen::Controls::Button* pButton = new Gwen::Controls::Button( pStatus );
        Gwen::Event::Packet packet( 0 );
//        packet.Integer = 0;
//        packet.String = "Hallosolo";
        pButton->SetText( "Preview" );
        pButton->onPress.Add( this, &WindowManager::zoomToPanel, packet );
        pButton->AddAccelerator( "1" );
        pStatus->AddControl( pButton, false );
    }
    {
        Gwen::Controls::Button* pButton = new Gwen::Controls::Button( pStatus );
        pButton->SetText( "Preview3D" );
        pButton->onPress.Add( this, &WindowManager::zoomToPanel );
        pButton->AddAccelerator( "2" );
        pStatus->AddControl( pButton, false );
    }
    {
        Gwen::Controls::Button* pButton = new Gwen::Controls::Button( pStatus );
        pButton->SetText( "Data Layer" );
        pButton->onPress.Add( this, &WindowManager::zoomToPanel );
        pButton->AddAccelerator( "3" );
        pStatus->AddControl( pButton, false );
    }
    {
        Gwen::Controls::Button* pButton = new Gwen::Controls::Button( pStatus );
        pButton->SetText( "Show All Panels" );
        pButton->onPress.Add( this, &WindowManager::showAllPanels );
        pButton->AddAccelerator( "0" );
        pStatus->AddControl( pButton, true );
    }    
}

void WindowManager::addSettingsList(){
        
    mSettingsControl = new SettingsPanel();
    mSettingsControl->setup( mTotalWindowArea  );

}

void WindowManager::addColourCorrectionWindow(){
	auto window = new Gwen::Controls::WindowControl( mCanvas );
	window->SetTitle( "COLOUR CORRECTION" );
	window->SetSize( 180, 200 );
//	window->SetPos( 200, 100 );
	window->SetPos( 20, 600 );
    window->SetPadding(Gwen::Padding(0,0,0,0));
	window->SetDeleteOnClose( true );
    window->SetClosable(false);
    //    window->DragAndDrop_SetPackage(false);
    //    window->DisableResizing();
    
	ColourCorrectionWindow *control = new ColourCorrectionWindow( window );
    control->setup();
	control->SetPos( 0, 0 );
    control->SetPadding(Gwen::Padding(0,0,0,0));
	control->Dock( Gwen::Pos::Fill );
    pColourControl = control;
}

void WindowManager::addPreviewWindow(){
    
    int panelId = 0;
    Gwen::Controls::Base* panel = m_Splitter->GetPanel(panelId);
    
//    Gwen::Controls::WindowControl* pWindow = new Gwen::Controls::WindowControl( panel );
//    pWindow->SetTitle( "PREVIEW" );
//    pWindow->SetSize( 200 + rand() % 100, 200 + rand() % 100 );
//    pWindow->SetPos( rand() % 700, rand() % 400 );
//    pWindow->SetDeleteOnClose( true );
    
    
	PreviewWindow *control = new PreviewWindow( panel );
    control->SetPadding(Gwen::Padding(0,0,0,0));
	control->Dock( Gwen::Pos::Fill );
    pPreviewControl = control;
    m_Splitter->SetPanel( panelId, control );
    
    Gwen::Controls::Label* label =  new Gwen::Controls::Label( control );
    label->SetText( "PREVIEW" );
    label->SetPos(10, 10);
    
}

void WindowManager::addPreview3DWindow(){
    
    int panelId = 1;
    Gwen::Controls::Base* panel = m_Splitter->GetPanel(panelId);
    
	Preview3DWindow *control = new Preview3DWindow( panel );
    control->SetPadding(Gwen::Padding(0,0,0,0));
	control->Dock( Gwen::Pos::Fill );
    pPreview3DControl = control;
    m_Splitter->SetPanel( panelId, control );

    Gwen::Controls::Label* label =  new Gwen::Controls::Label( control );
    label->SetText( "PREVIEW 3D" );
    label->SetPos(10, 10);
}

void WindowManager::addCircularDataWindow(){

    int panelId = 2;
    Gwen::Controls::Base* panel = m_Splitter->GetPanel(panelId);
    
	CircularDataWindow *control = new CircularDataWindow( panel );
    control->SetPadding(Gwen::Padding(0,0,0,0));
	control->Dock( Gwen::Pos::Fill );
    pCircularControl = control;
    m_Splitter->SetPanel( panelId, control );
    
    Gwen::Controls::Label* label =  new Gwen::Controls::Label( control );
    label->SetText( "DATA LAYER" );
    label->SetPos(10, 10);
}

void WindowManager::setPreviewFbo(ci::gl::Fbo* fbo){
    pPreview3DControl->setPreviewFbo(fbo);
}

void WindowManager::setIldaFrameRef( ciilda::Frame* frame ){
    pPreviewControl->setIldaFrame( frame );
    mSettingsControl->setIldaFrame( frame );
}

void WindowManager::setLaserController(ciilda::LaserController* controller){
    mSettingsControl->setLaserController(controller);
}

void WindowManager::setLaserPreview3d( LaserPreview3D* laserPreview3D ){
    mSettingsControl->setLaserPreview3d( laserPreview3D );
    pPreview3DControl->setLaserPreview3d( laserPreview3D );
}

void WindowManager::setCircularDataLayer( CircularDataLayer* circularDataLaser ){
    pCircularControl->setCircularDataLayer( circularDataLaser );
}

void WindowManager::setDataController(DataController* d){
    pCircularControl->setDataController( d );
}

void WindowManager::saveSettings(){
    
}

ColourCorrectionWindow* WindowManager::getColorValueController(){
    return pColourControl;
}

void WindowManager::showAllPanels( Gwen::Controls::Base* pFromPanel )
{
    m_Splitter->UnZoom();
}

void WindowManager::zoomToPanel( Gwen::Event::Info info ){
    
    int panelID = 0;
    string name = info.Control->GetValue().c_str();
    if(name.compare("Preview3D") == 0){
        panelID = 1;
    }
    else if(name.compare("Preview") == 0){
        panelID = 0;
    }
    else if(name.compare("Data Layer") == 0){
        panelID = 2;
    }
    m_Splitter->Zoom( panelID );
}



