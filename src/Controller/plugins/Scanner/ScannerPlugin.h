//
//  ScannerPlugin.h
//  QLT_GenomeLaser
//
//  Created by say nono on 17.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once

#include "cinder/app/AppBasic.h"
#include "cinder/Timeline.h"
#include "cinder/CinderMath.h"
#include "BasePlugin.h"
#include "Colors.h"


using namespace ci;
using namespace ci::app;
using namespace std;


class ScannerPlugin: public BasePlugin{
    
    
private:
    struct StarElement{
        Anim<float> liveTime;
        int         elementId;
        Vec2f       position;
        bool        isActive;
        int         lastDirPos;
        int         dataPos;
        int         liveTicker;
        char        basePair;
    };

public:
	
    ScannerPlugin();
	virtual void setup();
    //    virtual const string pluginID() { return "Bits";};
    virtual void dispose();
    virtual const map<string, OSCElement*>& getOSCMapping();
    virtual const ColouredShape2d& getShape( const GenomeData::BasePairDataSet& dataSet );
    virtual void onActivated();

    
private:
    
    Vec2f lerpLineDistorted( Vec2f p1, Vec2f p2, Vec2f center, float val );
    void drawWorm( float wormStart, float wormLength, int pos, Vec2f p, Vec2f pPrev);
    int getBasePairBit(char d);
    bool processElement(int pos, Vec2f vec, int dir, char basePair);
    void cleanupElements();
    void recreateElements( const GenomeData::BasePairDataSet& dataSet );
    void drawStarElement( ColouredShape2d* s, const StarElement& element );
    void drawElements();
    
    std::map<string, OSCElement*>   mOSCMap;
    ColouredShape2d                 mShape;
    ColouredShape2d                 mShapeTemp;
    
    Colors                          mColors;

    
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
    
    ColorAf                         mColorStart;
    ColorAf                         mColorEnd;
    int                             mLastDataSetID;
    Anim<float>                     mRotCounter;
    
    map<int,StarElement>            mStarElements;
    
};


