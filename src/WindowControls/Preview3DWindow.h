//
//  Preview3DWindow.h
//  QLT_GenomeLaser
//
//  Created by say nono on 08.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
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

class Preview3DWindow : public Gwen::Controls::Base {
    
public:
	Preview3DWindow( Gwen::Controls::Base *parent );
	virtual ~Preview3DWindow();
    
	virtual void Render( Gwen::Skin::Base* skin );
	virtual void RenderUnder( Gwen::Skin::Base* skin );
    
    void setPreviewFbo(ci::gl::Fbo* fbo);
    void onMousePress(int x, int y, bool bDown);
    
    Gwen::Event::Caller	onPress;
    
private:
    ci::Matrix44f		mCubeRotation;
	ci::CameraPersp		mCamera;
    ci::gl::Fbo*        mPreview3DFbo;
    bool                bPreviewFboSet;
    bool                bIldaFrameSet;
    
    gl::Texture         mImageTemp;
    ci::gl::Fbo         mFboTemp;
};
