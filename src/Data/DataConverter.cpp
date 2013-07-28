//
//  DataConverter.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 20.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "DataConverter.h"


Shape2d DataConverter::convertBitChainToCircularShape(char* data, int len, float lineHeight, float circStartAngle, float circLength, float circDiameter){
    
    Shape2d s;
    Vec2f p;
    Vec2f pNorm(0,.5);
    Vec2f pOffset(.5,.5);
    
    int pairs = len*2;
    
    float circDiaLong = circDiameter + lineHeight/2.0;
    float circDiaShort = circDiameter - lineHeight/2.0;
    
    float rotStepPair = circLength / (float) (len*2);
    float rotStepPairDist = (rotStepPair*.5);
    float rotStepBit = (rotStepPair*.5)/3.0;
    
    pNorm.rotate(circStartAngle-rotStepPairDist/2.0);
    p = pNorm;
    
    char d;
    int bitOffset;
    int lineCounter = 0;
    
    s.moveTo( p*circDiaLong+pOffset );
    
    for(int i=0;i<pairs;i++){
        
        d = data[i/2];
        bitOffset = (i%2)*4;
        for(int j=0;j<4;j++){
            if( ((d>>(bitOffset+j)) & 1) ==1 ){
                
                // TO AVOID LONG BLANK DISTANCES
                if(lineCounter%2==1){
                    s.moveTo( p*circDiaShort+pOffset );
                    s.lineTo( p*circDiaLong+pOffset );
                }else{
                    s.moveTo( p*circDiaLong+pOffset );
                    s.lineTo( p*circDiaShort+pOffset );
                }
                lineCounter++;
            }
            p.rotate(rotStepBit);
        }
        p.rotate(rotStepPair);
        
    }
    
//    for(int j=0;j<len;j++){
//        for(int i = 7; i >= 0; i--)
//        {
//            d = data[j];
//            std::cout << ((d >> i) & 1);
//        }
//        std::cout <<  "  ";
//        if(j%4==3) std::cout << std::endl;
//    }
    
    return s;
}

//bool DataConverter::addLines(Shape2d* shape, char c){
//    
//}

