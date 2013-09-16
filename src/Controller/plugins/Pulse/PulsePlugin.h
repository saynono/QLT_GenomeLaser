//
//  PulsePlugin.h
//  QLT_GenomeLaser
//
//  Created by say nono on 29.08.13.
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


class PulsePlugin: public BasePlugin{

public:
    
    PulsePlugin();
	virtual void setup();
    //    virtual const string pluginID() { return "Bits";};
    virtual void dispose();
    virtual const map<string, OSCElement*>& getOSCMapping();
    virtual const ColouredShape2d& getShape( const GenomeData::BasePairDataSet& dataSet );

private:
    
    void                            drawBeam(Vec2f p, float dia);
    void                            drawDescription( Vec2f pos, float len, string description, int descriptionPos );
    
    ColorAf                         mColorStart;
    ColorAf                         mColorEnd;
    ColouredShape2d                 mShape;
    
    Colors                          mColors;

    std::map<string, OSCElement*>   mOSCMap;
    
    vector<Vec2f>                   mBeam;
    vector<Vec2f>                   mDataLines;
    float                           mBeamDiameter;
    float                           mBeamDistance;
    int                             mBeamOffset;
    
    int                             mLastDataSetID;
    string                          mCurrentDataSetDescription;
    int                             mRoiTicker;
    
  
};



