//
//  DataConverter.h
//  QLT_GenomeLaser
//
//  Created by say nono on 20.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "cinder/app/AppBasic.h"
#include "cinder/Shape2d.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class DataConverter{

public:
	
	Shape2d convertBitChainToCircularShape(char* data, int len, float lineHeight, float circStartAngle, float circLength, float circDiameter);

	
};



