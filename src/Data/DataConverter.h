//
//  DataConverter.h
//  QLT_GenomeLaser
//
//  Created by say nono on 20.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "cinder/app/AppBasic.h"
#include "ColouredShape2d.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class DataConverter{

public:
	
	ColouredShape2d convertBitChainToShape(char* data, int len, float lineHeight, float circStartAngle, float circLength, float circDiameter);

private:
    
    void drawLine(ColouredShape2d* s, Vec2f p1, Vec2f p2);

    int mLineCounter;

    
};



