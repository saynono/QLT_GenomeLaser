//
//  BitsAndLinesPlugin.h
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "cinder/app/AppBasic.h"

#include "BasePlugin.h"
#include "DataConverterUtil.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BitsAndLinesPlugin: public BasePlugin{

public:
	
    BitsAndLinesPlugin();
	virtual void setup();
    virtual const string pluginID() { return "BitsAndLinesPlugin";};
    virtual void dispose();
    virtual const map<string, OSCElement*>& getOSCMapping();
    virtual const ColouredShape2d& getShape( const GenomeData::BasePairDataSet& dataSet );
    
private:

    void    convertBitChainToShape(const char* data, int len, float lineHeight, float circStartAngle, float circLength, float circDiameter);
    void    drawLine(ColouredShape2d* s, Vec2f p1, Vec2f p2, float percent);
    
    ColouredShape2d     mShape;
    int                 mLineCounter;
    
    float               mStartAngle;
    float               mSpeed;
    float               mLineHeight;
    float               mLinePosition;
    float               mLength;
    float               mPairRadLength;
    
    ColorAf             mClr1;
    ColorAf             mClr2;
    
    std::map<string, OSCElement*> mOSCMap;

    
};



