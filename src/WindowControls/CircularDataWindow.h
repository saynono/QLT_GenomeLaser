//
//  CircularDataWindow.h
//  QLT_GenomeLaser
//
//  Created by say nono on 18.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "Gwen/Controls/Base.h"
#include "cinder/gl/Fbo.h"

#include "CircularDataLayer.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CircularDataWindow : public Gwen::Controls::Base {
    
public:
	CircularDataWindow( Gwen::Controls::Base *parent );
	virtual ~CircularDataWindow();
    
	virtual void Render( Gwen::Skin::Base* skin );
//	virtual void RenderUnder( Gwen::Skin::Base* skin );
    
    void update();
    
    void setCircularDataLayer( CircularDataLayer* layer );
    
//    virtual void OnMouseMoved( int x, int y, int deltaX, int deltaY );
//    virtual void OnMouseClickLeft( int x, int y, bool bDown );
//    virtual void OnMouseEnter();
//    virtual void OnMouseLeave();
//    virtual void OnMouseDoubleClickLeft( int x, int y );
    
public:
    
    Gwen::Event::Caller	onPress;

private:
    
    bool                        bLayerSet;
    CircularDataLayer*          mDataLayer;
	
};



