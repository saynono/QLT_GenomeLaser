//
//  DataConverter.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 20.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "DataConverter.h"


ColouredShape2d DataConverter::convertBitChainToShape(char* data, int len, float lineHeight, float circStartAngle, float circLength, float circDiameter){
    
    ColouredShape2d s;
    Vec2f p;
    Vec2f pNorm(0,.5);
    Vec2f pOffset(.5,.5);
    
    int basePairs = len;
    
    float circDiaLong = circDiameter + lineHeight/2.0;
    float circDiaShort = circDiameter - lineHeight/2.0;
    
    float rotStepPair = circLength / (float) (basePairs);
    float rotStepPairDist = (rotStepPair*.5);
    float rotStepBit = (rotStepPair-rotStepPairDist)/2.0;
    
    pNorm.rotate(circStartAngle+rotStepPairDist/2.0);
    p = pNorm;
    
    char d;
    int basePairBit;
    int bitOffset;
    
    mLineCounter = 0;
    
    drawLine( &s, p*circDiaShort+pOffset, p*circDiaLong+pOffset );
    
    for(int i=0;i<basePairs/4;i++){
        
        d = data[i/4];
        
        
        for(int j=0;j<4;j++){

            bitOffset = j*2;
            
            basePairBit = (d>>(bitOffset)) & 3;
            
            switch(basePairBit){
                case 0:
//                    console() << "A";
                    break;
                case 1:
//                    console() << "C";
                    break;
                case 2:
//                    console() << "G";
                    break;
                case 3:
//                    console() << "T";
                    break;
            }
            
            if( (basePairBit & 1) == 1) drawLine( &s, p*circDiaShort+pOffset, p*circDiaLong+pOffset );
//            drawLine( &s, p*circDiaShort+pOffset, p*circDiaLong+pOffset );
            p.rotate(rotStepBit);
            
            if( (basePairBit & 2) == 2) drawLine( &s, p*circDiaShort+pOffset, p*circDiaLong+pOffset );
//            drawLine( &s, p*circDiaShort+pOffset, p*circDiaLong+pOffset );
            p.rotate(rotStepBit);
            
            p.rotate(rotStepPairDist);

        }
        
        drawLine( &s, p*circDiaShort+pOffset, p*circDiaLong+pOffset );
        
    }
    return s;
}

void DataConverter::drawLine(ColouredShape2d* s, Vec2f p1, Vec2f p2){
    s->color( lerp( ColorAf(1,.7,.1,1), ColorAf(.5,0,1,1), mLineCounter/100.0) );
    if(mLineCounter%2==1){
        s->moveTo( p1 );
        s->lineTo( p2 );
    }else{
        s->moveTo( p2 );
        s->lineTo( p1 );
    }
    mLineCounter ++;
}
