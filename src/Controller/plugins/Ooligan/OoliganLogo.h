//
//  OoliganLogo.h
//  QLT_GenomeLaser
//
//  Created by say nono on 28.08.13.
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


class OoliganLogo: public BasePlugin{

public:
    
    OoliganLogo();
	
	virtual void setup();
    //    virtual const string pluginID() { return "Bits";};
    virtual void dispose();
    virtual const map<string, OSCElement*>& getOSCMapping();
    virtual const ColouredShape2d& getShape( const GenomeData::BasePairDataSet& dataSet );

private:
    
    struct line{
        Vec2f p1;
        Vec2f p2;
    };

    
    void addStar( ColouredShape2d* shape, Vec2f pos, float scale);
    void addLine( ColouredShape2d* shape, Vec2f p1, Vec2f p2 );
    
    vector<line>                    mLines;
    vector<Vec2f>                   mStarVec;
    ColorAf                         mColorStart;
    ColorAf                         mColorEnd;
	
    std::map<string, OSCElement*>   mOSCMap;
    ColouredShape2d                 mShape;
    
    Colors                          mColors;
    
    float                           mStarWidth;
    float                           mStarScale;

};



