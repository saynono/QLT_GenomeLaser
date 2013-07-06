//
//  PreviewWindow.h
//  LaserGateway
//
//  Created by say nono on 18.03.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once


#include "Gwen/Controls/Base.h"

#include "cinder/Matrix44.h"
#include "cinder/Camera.h"
#include "cinder/gl/Fbo.h"

#include "CinderIldaFrame.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class PreviewWindow : public Gwen::Controls::Base {
    
public:
	PreviewWindow( Gwen::Controls::Base *parent );
	virtual ~PreviewWindow();
    
	virtual void Render( Gwen::Skin::Base* skin );
	virtual void RenderUnder( Gwen::Skin::Base* skin );
    
    void setPreviewFbo(ci::gl::Fbo* fbo);
    void setIldaFrame(ciilda::Frame* frame);
    
private:
    ci::Matrix44f		mCubeRotation;
	ci::CameraPersp		mCamera;
    ci::gl::Fbo*        mPreviewFbo;
    ciilda::Frame*      mIldaFrame;
    bool                bPreviewFboSet;
    bool                bIldaFrameSet;

};



