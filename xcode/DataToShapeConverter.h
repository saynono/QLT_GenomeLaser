//
//  DataToShapeConverter.h
//  QLT_GenomeLaser
//
//  Created by say nono on 11.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "cinder/app/AppBasic.h"
#include "cinder/Shape2d.h"
#include "cinder/Font.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class DataToShapeConverter{

public:
	
	void setup();
    Shape2d convertChar(char c);
    
private:
    
	Font    mFont;
    
    
};



