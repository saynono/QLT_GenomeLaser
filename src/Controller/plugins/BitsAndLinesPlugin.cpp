//
//  BitsAndLinesPlugin.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "BitsAndLinesPlugin.h"

	
void BitsAndLinesPlugin::setup(){
    
    mStartAngle = Rand::randFloat(-M_PI,M_PI);
    mSpeed = Rand::randFloat(-M_PI,M_PI);
    mLineHeight = Rand::randFloat(0.0,.2);
    mLinePosition = Rand::randFloat(mLineHeight/2.0,1-mLineHeight/2.0);
    mLength = toRadians(Rand::randFloat(0.0,1.0)*180);
    
    console() << "mLinePosition : " << mLinePosition << "    this: " << mLineHeight << "   mSpeed: " << mSpeed << std::endl;
    
}

void BitsAndLinesPlugin::dispose(){
    
}

const ColouredShape2d& BitsAndLinesPlugin::getShape( const GenomeData::BasePairDataSet& dataSet ){

    
//    int len = 8*10;
//    char dataBits[(int)ceil(len/4)];
//    int dataOffset = 20000;//+getElapsedFrames();
    float startAngle = toRadians(-(float)getElapsedFrames()*mSpeed) + mStartAngle;
    convertBitChainToShape( dataSet.dataBits.c_str(), dataSet.basePairsCount, mLineHeight, startAngle, mLength, mLinePosition);
    
    return mShape;
}

void BitsAndLinesPlugin::convertBitChainToShape(const char* data, int len, float lineHeight, float circStartAngle, float circLength, float circDiameter){
    
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
    
    mShape.clear();
    
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
            
            if( (basePairBit & 1) == 1) drawLine( &mShape, p*circDiaShort+pOffset, p*circDiaLong+pOffset );
            //            drawLine( &s, p*circDiaShort+pOffset, p*circDiaLong+pOffset );
            p.rotate(rotStepBit);
            
            if( (basePairBit & 2) == 2) drawLine( &mShape, p*circDiaShort+pOffset, p*circDiaLong+pOffset );
            //            drawLine( &s, p*circDiaShort+pOffset, p*circDiaLong+pOffset );
            p.rotate(rotStepBit);
            
            p.rotate(rotStepPairDist);
            
        }
        
    }
}

void BitsAndLinesPlugin::drawLine(ColouredShape2d* s, Vec2f p1, Vec2f p2){
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