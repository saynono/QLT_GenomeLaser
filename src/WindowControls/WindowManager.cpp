//
//  WindowManager.cpp
//  LaserGateway
//
//  Created by say nono on 18.03.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "WindowManager.h"

	
void WindowManager::setup(){
    createMainControls();
    addSettingsList();
    addPreviewWindow();
    addColourCorrectionWindow();
}
	
void WindowManager::update(){
	
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
}

void WindowManager::addSettingsList(){
    
//    mCanvas->GetDock()->GetLeft
    Gwen::Controls::DockBase* dock = new Gwen::Controls::DockBase( mCanvas );
    dock->Dock( Gwen::Pos::Fill );
    Gwen::Controls::CollapsibleList* pList = new Gwen::Controls::CollapsibleList( dock );
    pList->SetHeight(300);
//    mCanvas->
    Gwen::Controls::TabControl* tabControl = dock->GetLeft()->GetTabControl();
	tabControl->AddPage( "Settings", pList );
	dock->GetLeft()->SetWidth( 250 );
    
    Gwen::Controls::CollapsibleCategory* cat = pList->Add( "Basic" );
    
//    Gwen::Controls::Button* pButton = cat->Add("Normal Window");//new Gwen::Controls::Button( cat );
////    pButton->SetPos( 0, 0 );
//    
//    pColourControl = new ColourCorrectionWindow(cat);
////	pColourControl->SetPos( 0, 40 );
//    pColourControl->SetPadding(Gwen::Padding(0,0,0,0));
////    pColourControl->SetSize(240, 250);
////    pColourControl->SetHeight(150);
//	pColourControl->Dock( Gwen::Pos::Fill );
//    
//    
//    auto window = new Gwen::Controls::WindowControl( cat );
//	window->SetTitle( "PREVIEW" );
//	window->SetSize( 480, 500 );
//	window->SetPos( 400, 100 );
//    window->SetPadding(Gwen::Padding(0,0,0,0));
//	window->SetDeleteOnClose( true );
//    window->SetClosable(false);
////	tabControl->AddPage( "lala", window );
//    
//    

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
    
	auto window = new Gwen::Controls::WindowControl( mCanvas );
	window->SetTitle( "PREVIEW" );
	window->SetSize( 480, 500 );
	window->SetPos( getWindowWidth() - window->GetBounds().w, 0 );
    window->SetPadding(Gwen::Padding(0,0,0,0));
	window->SetDeleteOnClose( true );
    window->SetClosable(false);
//    window->DragAndDrop_SetPackage(false);
//    window->DisableResizing();
    
	PreviewWindow *control = new PreviewWindow( window );
	control->SetPos( 0, 0 );
    control->SetPadding(Gwen::Padding(0,0,0,0));
	control->Dock( Gwen::Pos::Fill );
    pPreviewControl = control;
    
}


void WindowManager::saveSettings(){
    
}

ColourCorrectionWindow* WindowManager::getColorValueController(){
    return pColourControl;
}
