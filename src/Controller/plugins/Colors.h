//
//  Colors.h
//  QLT_GenomeLaser
//
//  Created by say nono on 27.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "cinder/app/AppBasic.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Colors{

public:
	
	void setup();
    ColorAf getColor( int column, float percent );	
    
private:
    
    vector<ColorAf> mBaseColors;
    
    
};



