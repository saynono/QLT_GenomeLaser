//
//  DataToShapeConverter.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 11.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "DataToShapeConverter.h"

	
void DataToShapeConverter::setup(){
    mFont = Font( loadAsset("./fonts/pn_bold.ttf") , 100 );
}


	
Shape2d DataToShapeConverter::convertChar(char c){
    return mFont.getGlyphShape( mFont.getGlyphChar(c));
}
