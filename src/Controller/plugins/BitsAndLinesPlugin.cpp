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
    mLineHeight = Rand::randFloat(0.0,.4);
    mLinePosition = Rand::randFloat(mLineHeight/2.0,1-mLineHeight/2.0);
    mLength = toRadians(Rand::randFloat(0.0,1.0)*180);
    
    mClr1 = ColorAf(Rand::randFloat(.01, .7),.7,Rand::randFloat(.0, .9),1);
    mClr2 = ColorAf(Rand::randFloat(.3, .9),Rand::randFloat(.3, .9),Rand::randFloat(.3, .9),1);
    
    mOSCMap.insert( make_pair( "SPEED", OSCElement( this, &mSpeed, OSCElement::FLOAT )) );
    mOSCMap.insert( make_pair( "LINE_HEIGHT", OSCElement( this, &mLineHeight, OSCElement::FLOAT, 0, .1 )) );
    mOSCMap.insert( make_pair( "LINE_POSITION", OSCElement( this, &mLinePosition, OSCElement::FLOAT )) );
    mOSCMap.insert( make_pair( "LENGTH", OSCElement( this, &mLength, OSCElement::FLOAT )) );
    
}

void BitsAndLinesPlugin::dispose(){
}


//------------------------------------------------------------------------------------------------------

const map<string, OSCElement>& BitsAndLinesPlugin::getOSCMapping() {
    return mOSCMap;
}

//------------------------------------------------------------------------------------------------------

void BitsAndLinesPlugin::processOSCMessage( const osc::Message& message ) {
    for (int i = 0; i < message.getNumArgs(); i++) {
        if( message.getArgType(i) == osc::TYPE_INT32 ) {
            try {
                message.getArgAsInt32(i);
            }
            catch (...) {
                console() << "Exception reading argument as int32" << std::endl;
            }
        }
        else if( message.getArgType(i) == osc::TYPE_FLOAT ) {
            try {
                float val = message.getArgAsFloat(i);
                mLength = toRadians( val*360 );
                mLinePosition = val;
            }
            catch (...) {
                console() << "Exception reading argument as float" << std::endl;
            }
        }
        else if( message.getArgType(i) == osc::TYPE_STRING) {
            try {
                message.getArgAsString(i);
            }
            catch (...) {
                console() << "Exception reading argument as string" << std::endl;
            }
        }
    }
    
}


//------------------------------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------------------------------

void BitsAndLinesPlugin::drawLine(ColouredShape2d* s, Vec2f p1, Vec2f p2){
    s->color( lerp( mClr1, mClr2, mLineCounter/100.0) );
    if(mLineCounter%2==1){
        s->moveTo( p1 );
        s->lineTo( p2 );
    }else{
        s->moveTo( p2 );
        s->lineTo( p1 );
    }
    mLineCounter ++;
}