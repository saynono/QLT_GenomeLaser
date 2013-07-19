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
        
    Shape2d s = mFont.getGlyphShape( mFont.getGlyphChar(c));
    Rectf r;
    int h = r.getHeight();
    
    if(h != 0){
        float scale = 1.0/ (mFont.getSize() * 2);
        MatrixAffine2f matrix;
        matrix.setToIdentity();
        matrix.scale( Vec2f(scale,scale) );
        s.transform(matrix);
        r = s.calcBoundingBox();
        matrix.setToIdentity();
        matrix.translate( Vec2f(.5,.5) );
        matrix.translate( Vec2f(-r.getCenter().x,-r.getCenter().y) );
        s.transform(matrix);
    }
    
    return s;
}
