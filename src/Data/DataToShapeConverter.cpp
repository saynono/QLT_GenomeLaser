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
    
    console() << "DataToShapeConverter::convertChar : " << c << std::endl;
    
    Shape2d s = mFont.getGlyphShape( mFont.getGlyphChar(c));
    Rectf r = s.calcBoundingBox();
    int h = r.getHeight();
    
    if(h != 0){
        float scale = 1.0/ (mFont.getSize() * 2);
        MatrixAffine2f matrix;
        matrix.setToIdentity();
        matrix.scale( Vec2f(scale,scale) );
        s.transform(matrix);
        //        matrix.translate( -Vec2f(r.x1,40) );
        matrix.setToIdentity();
        matrix.translate( Vec2f(.5,-.5) );
        s.transform(matrix);
    }
    
    return s;
}
