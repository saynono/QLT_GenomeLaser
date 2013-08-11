//
//  BitsAndLinesPlugin.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "BitsAndLinesPlugin.h"

BitsAndLinesPlugin::BitsAndLinesPlugin(): BasePlugin( "BitsAndLinesPlugin" ){
}
	
void BitsAndLinesPlugin::setup(){
    
    mStartAngle = Rand::randFloat(-M_PI,M_PI);
    mSpeed = Rand::randFloat(-M_PI,M_PI);
    mLineHeight = Rand::randFloat(0.0,.3);
    mLinePosition = Rand::randFloat(mLineHeight/2.0,1-mLineHeight/2.0);
//    mLinePosition = 1-mLineHeight/2.0;
    mLength = toRadians(Rand::randFloat(0.0,1.0)*180);
    
    mPairRadLength = toRadians( Rand::randFloat(0.1,5.0) );
    
    mClr1 = ColorAf(Rand::randFloat(.01, .7),.7,Rand::randFloat(.0, .9),1);
    mClr2 = ColorAf(Rand::randFloat(.3, .9),Rand::randFloat(.3, .9),Rand::randFloat(.3, .9),1);
    
    mOSCMap.insert( make_pair( "SPEED", new OSCElement( "SPEED", this, &mSpeed, OSCElement::FLOAT, 0.1, 1.0  )) );
    mOSCMap.insert( make_pair( "LINE_HEIGHT", new OSCElement( "LINE_HEIGHT", this, &mLineHeight, OSCElement::FLOAT, 0, .3 )) );
    mOSCMap.insert( make_pair( "LINE_POSITION", new OSCElement( "LINE_POSITION", this, &mLinePosition, OSCElement::FLOAT, 0, 1  )) );
    mOSCMap.insert( make_pair( "LENGTH", new OSCElement( "LENGTH", this, &mLength, OSCElement::FLOAT, 0, .4 )) );

}

void BitsAndLinesPlugin::dispose(){
}


//------------------------------------------------------------------------------------------------------

const map<string, OSCElement*>& BitsAndLinesPlugin::getOSCMapping() {
    return mOSCMap;
}

//------------------------------------------------------------------------------------------------------

const ColouredShape2d& BitsAndLinesPlugin::getShape( const GenomeData::BasePairDataSet& dataSet ){

    float p = dataSet.startPosition*mPairRadLength;
    float startAngle = p;//toRadians(-(float)dataSet.startPosition)*mPairRadLength + mStartAngle;

    convertBitChainToShape( dataSet.dataBitsString.c_str(), dataSet.basePairsCount, mLineHeight, startAngle, mPairRadLength, mLinePosition);
    return mShape;
}

void BitsAndLinesPlugin::convertBitChainToShape(const char* data, int len, float lineHeight, float circStartAngle, float pairRadLength, float circDiameter){
    
    Vec2f p;
    Vec2f pNorm(0,.5);
    Vec2f pOffset(.5,.5);
    
    int basePairs = len;
    
    float lineHeight2 = lineHeight/2.0;
    float circDiaLong = circDiameter + lineHeight2;
    float circDiaShort = circDiameter - lineHeight2;
    
    float rotStepPair = pairRadLength;//circLength / (float) (basePairs);
    float rotStepPairDist = (rotStepPair*.5);
    float rotStepBit = (rotStepPair-rotStepPairDist)/2.0;
    
    pNorm.rotate(circStartAngle+rotStepPairDist/2.0);
    p = pNorm;
    
    char d;
    int basePairBit;
    int bitOffset;
    float percent;
//    float hPercent;
    
    mLineCounter = 0;
    
    mShape.clear();
    
    for(int i=0;i<basePairs;i++){
        
        d = data[i];
        percent = mLineCounter / static_cast<float>(basePairs);
        
        switch(d){
            case 'A':
                basePairBit = 0;
                break;
            case 'C':
                basePairBit = 1;
                break;
            case 'G':
                basePairBit = 2;
                break;
            case 'T':
                basePairBit = 3;
                break;
        }
        if( (basePairBit & 1) == 1) drawLine( &mShape, p*circDiaShort+pOffset, p*circDiaLong+pOffset, percent );
            //            drawLine( &s, p*circDiaShort+pOffset, p*circDiaLong+pOffset );
        p.rotate(rotStepBit);
            
        if( (basePairBit & 2) == 2) drawLine( &mShape, p*circDiaShort+pOffset, p*circDiaLong+pOffset, percent );
        //            drawLine( &s, p*circDiaShort+pOffset, p*circDiaLong+pOffset );
        p.rotate(rotStepBit);
            
        p.rotate(rotStepPairDist);
            
    }
    
}

//------------------------------------------------------------------------------------------------------

void BitsAndLinesPlugin::drawLine(ColouredShape2d* s, Vec2f p1, Vec2f p2, float percent){
    
    s->color( lerp( mClr1, mClr2, percent) * max(0.0,sin(percent*M_PI)) );
    
    if(mLineCounter%2==1){
        s->moveTo( p1 );
        s->lineTo( p2 );
    }else{
        s->moveTo( p2 );
        s->lineTo( p1 );
    }
    mLineCounter ++;
}