//
//  BasePlugin.h
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"

#include "GenomeData.h"
#include "ColouredShape2d.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BasePlugin{

public:
	
	virtual void setup();
    virtual void dispose();
//	virtual void update();
    virtual const ColouredShape2d& getShape(const GenomeData::BasePairDataSet& dataSet);
	
protected:
    
    Rand                mRandom;

};



