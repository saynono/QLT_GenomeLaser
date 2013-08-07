//
//  CircularDataWindow.h
//  QLT_GenomeLaser
//
//  Created by say nono on 18.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "Gwen/Controls/Base.h"
#include "Gwen/Controls/Label.h"
#include "cinder/gl/Fbo.h"

#include "CircularDataLayer.h"
#include "DataController.h"

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
    void setDataController( DataController* d );
    
    void drawArc( Vec2f center, float dia, float angleStart, float angleEnd );
    void drawPerdArcLine( Vec2f center, float angleStart, float diaMin, float diaMax );
    
public:
    
    Gwen::Event::Caller	onPress;

private:
    
    bool                        bLayerSet;
    bool                        bDataControllerSet;
    DataController*             mDataController;

    CircularDataLayer*                  mDataLayer;
    vector<Gwen::Controls::Label*>      mCrawlerLabels;
	
};



