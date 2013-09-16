//
//  Colors.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 27.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "Colors.h"

	
void Colors::setup(){
    mBaseColors.push_back( ColorAf(1,0,0,1) );
//    mBaseColors.push_back( ColorAf(.97,.2,.3,1) );
    mBaseColors.push_back( ColorAf(0.76,.3,.8,1) );
    mBaseColors.push_back( ColorAf(1,1,1,1) );
}

ColorAf Colors::getColor( int column, float percent ){
    if(mBaseColors.size() == 0) setup();
    ColorAf clr = mBaseColors[column%mBaseColors.size()];
    Vec3f c = rgbToHSV( clr );
    c.x = fmod(c.x+percent,1.0f);
    clr = hsvToRGB( c );
    return clr;
}