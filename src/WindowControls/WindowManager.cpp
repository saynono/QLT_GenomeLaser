//
//  WindowManager.cpp
//  LaserGateway
//
//  Created by say nono on 18.03.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "WindowManager.h"

	
void WindowManager::setup(){
    mRenderDate = "BUILD " + toString(__DATE__) + "  |  " + toString(__TIME__);
    createMainControls();
    addSettingsList();
    addPreviewWindow();
    addPreview3DWindow();
    addColourCorrectionWindow();
}
	
void WindowManager::update(){
	mSettingsControl->update();
    pStatusFPSLabel->SetText( toString((int)getFrameRate()) + " FPS        ");
}

void WindowManager::draw(){
    mCanvas->RenderCanvas();
}

void WindowManager::createMainControls(){
    
	getWindow()->setTitle( "QLT GenomeLaser v1" );
        
	mRenderer = new cigwen::GwenRendererGl();
	mRenderer->Init();
    
	Gwen::Skin::TexturedBase* skin = new Gwen::Skin::TexturedBase( mRenderer );
    //	skin->Init( "DefaultSkin.png" );
    //	skin->Init( "obscureskin.png" );
	skin->Init( "NonoSkin.png" );
    
	mCanvas = new Gwen::Controls::Canvas( skin );
	mCanvas->SetSize( getWindowWidth(), getWindowHeight() - 24 );
	mCanvas->SetDrawBackground( true );
	mCanvas->SetBackgroundColor( cigwen::toGwen( Color::gray( 0.2 ) ) );
    
	mGwenInput = cigwen::GwenInput::create( mCanvas );
    
    
    
//    Dock( Pos::Fill );
    Gwen::Controls::StatusBar* pStatus = new Gwen::Controls::StatusBar( mCanvas );
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
}

void WindowManager::addSettingsList(){
    
    mSettingsControl = new SettingsPanel( mCanvas );
    mSettingsControl->setup();

}

void WindowManager::addColourCorrectionWindow(){
	auto window = new Gwen::Controls::WindowControl( mCanvas );
	window->SetTitle( "COLOUR CORRECTION" );
	window->SetSize( 280, 300 );
//	window->SetPos( 200, 100 );
	window->SetPos( getWindowWidth() - window->GetBounds().w - window->GetBounds().x - 480, 0 );
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
    
    int px = mSettingsControl->GetRenderBounds().x + mSettingsControl->GetRenderBounds().w;
    
	auto window = new Gwen::Controls::WindowControl( mCanvas );
	window->SetTitle( "PREVIEW" );
	window->SetSize( 480, 500 );
//	window->SetPos( getWindowWidth() - window->GetBounds().w, 0 );
	window->SetPos( px, 0 );
    window->SetPadding(Gwen::Padding(0,0,0,0));
	window->SetDeleteOnClose( true );
    window->SetClosable(false);
//    window->DragAndDrop_SetPackage(false);
//    window->DisableResizing();
    
	PreviewWindow *control = new PreviewWindow( window );
	control->SetPos( 0, 0 );
    control->SetPadding(Gwen::Padding(0,0,0,0));
	control->Dock( Gwen::Pos::Fill );
//    window->DisableResizing();
    pPreviewControl = control;
    
}

void WindowManager::addPreview3DWindow(){
    
	auto window = new Gwen::Controls::WindowControl( mCanvas );
	window->SetTitle( "PREVIEW 3D" );
	window->SetSize( 480, 500 );
	window->SetPos( getWindowWidth() - window->GetBounds().w, 0 );
    window->SetPadding(Gwen::Padding(0,0,0,0));
	window->SetDeleteOnClose( true );
    window->SetClosable(false);
    
	Preview3DWindow *control = new Preview3DWindow( window );
	control->SetPos( 0, 0 );
    control->SetPadding(Gwen::Padding(0,0,0,0));
	control->Dock( Gwen::Pos::Fill );
    //    window->DisableResizing();
    pPreview3DControl = control;
    
}

void WindowManager::setPreviewFbo(ci::gl::Fbo* fbo){
    pPreview3DControl->setPreviewFbo(fbo);
}

void WindowManager::setIldaFrame(ciilda::Frame* frame){
    pPreviewControl->setIldaFrame(frame);
    mSettingsControl->setIldaFrame(frame);
}

void WindowManager::setLaserController(ciilda::LaserController* controller){
    mSettingsControl->setLaserController(controller);
}


void WindowManager::saveSettings(){
    
}

ColourCorrectionWindow* WindowManager::getColorValueController(){
    return pColourControl;
}
