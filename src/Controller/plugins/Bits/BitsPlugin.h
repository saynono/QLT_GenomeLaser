//
//  BitsPlugin.h
//  QLT_GenomeLaser
//
//  Created by say nono on 14.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once

#include "cinder/app/AppBasic.h"

#include "BasePlugin.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BitsPlugin: public BasePlugin{
    
public:
	
    BitsPlugin();
	virtual void setup();
    virtual void dispose();
    virtual const map<string, OSCElement*>& getOSCMapping();
    virtual const ColouredShape2d& getShape( const GenomeData::BasePairDataSet& dataSet );
    
private:
    
    Vec2f lerpLineDistorted( Vec2f p1, Vec2f p2, Vec2f center, float val );
    void addSpotShape( ColouredShape2d* s, Vec2f center, float size );
    void drawWorm( float wormStart, float wormLength, int pos, Vec2f p, Vec2f pPrev);
    
    std::map<string, OSCElement*>   mOSCMap;
    ColouredShape2d                 mShape;
    
    float                           mRadBasePair;
    int                             mAmountBasePair;
    float                           mSpotSize;
    float                           mCircDiameter;
    float                           mLineHeight;
    float                           mWormLength;
    float                           mWormSpeed;
    float                           mSphereRotSpeed;
    float                           mSphereRotation;
    double                          mTimeStamp;
    
    
    ColorAf                         mColorDark;
    ColorAf                         mColorBright;
    float                           mCounter;
};






