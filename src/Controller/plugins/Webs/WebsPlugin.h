//
//  WebsPlugin.h
//  QLT_GenomeLaser
//
//  Created by say nono on 11.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once

#include "cinder/app/AppBasic.h"

#include "BasePlugin.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class WebsPlugin: public BasePlugin{

public:
	
    WebsPlugin();
	virtual void setup();
    virtual const string pluginID() { return "Webs";};
    virtual void dispose();
    virtual const map<string, OSCElement*>& getOSCMapping();
    virtual const ColouredShape2d& getShape( const GenomeData::BasePairDataSet& dataSet );

private:

    void addSpotShape( ColouredShape2d* s, Vec2f center, float size );
    void drawWorm( float wormStart, float wormLength, int pos, int offset, Vec2f p, Vec2f pPrev);
    
    std::map<string, OSCElement*>   mOSCMap;
    ColouredShape2d                 mShape;
    
    float                           mRadBasePair;
    int                             mAmountBasePair;
    float                           mSpotSize;
    float                           mCircDiameter;
    float                           mLineHeight;

    
    ColorAf                         mColorDark;
    ColorAf                         mColorBright;
    float                           mCounter;
};




