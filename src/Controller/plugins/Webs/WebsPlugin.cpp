//
//  WebsPlugin.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 11.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "WebsPlugin.h"

	
WebsPlugin::WebsPlugin(): BasePlugin( "WebsPlugin" ){
}

void WebsPlugin::setup(){
    
    mRadBasePair = toRadians(2.0f);
    mAmountBasePair = 10;
    mSpotSize = .01;
    
    mCircDiameter = .5;
    mLineHeight = .4;


    mOSCMap.insert( make_pair( "RAD_PER_BASEPAIR", new OSCElement( "RAD_PER_BASEPAIR", this, &mRadBasePair, OSCElement::FLOAT, toRadians(0.1f), toRadians(10.0f)  )) );
    mOSCMap.insert( make_pair( "AMOUNT_BASEPAIRS", new OSCElement( "AMOUNT_BASEPAIRS", this, &mAmountBasePair, OSCElement::INTEGER, 1, 50 )) );
    mOSCMap.insert( make_pair( "SPOT_SIZE", new OSCElement( "SPOT_SIZE", this, &mSpotSize, OSCElement::FLOAT, 0.001f, .1f )) );
    mOSCMap.insert( make_pair( "CIRC_DIAMETER", new OSCElement( "SPOT_SIZE", this, &mCircDiameter, OSCElement::FLOAT, 0.0f, 1.0f )) );
    mOSCMap.insert( make_pair( "LINE_HEIGHT", new OSCElement( "SPOT_SIZE", this, &mLineHeight, OSCElement::FLOAT, 0.0f, 1.0f )) );
    
    
    mColorDark = ColorAf(.3,0,0,1);
    mColorBright = ColorAf(0,.8,1,1);
    mCounter = 6;

}

void WebsPlugin::dispose(){
}


// ------------------------------------------------------------------------------------------------------

const map<string, OSCElement*>& WebsPlugin::getOSCMapping() {
    return mOSCMap;
}

// ------------------------------------------------------------------------------------------------------

const ColouredShape2d& WebsPlugin::getShape( const GenomeData::BasePairDataSet& dataSet ){
    mShape.clear();
    
    Vec2f p,pStart,pPrev;
    Vec2f pNorm(0,.5);
    Vec2f pOffset(.5,.5);
    
    int basePairs = min(mAmountBasePair,dataSet.basePairsCount);
        
    float circDiameter = mCircDiameter;
    float lineHeight = mLineHeight;
    float lineHeight2 = lineHeight/2.0;
    float circDiaLong = circDiameter + lineHeight2;
    float circDiaShort = circDiameter - lineHeight2;
    
    float rotStepPair = mRadBasePair;
    
    
    float wormLength = 0.3f;
    float wormStart = mCounter;
    
    console() << "----------------------------------------------"<< std::endl;
    
    pNorm.rotate(dataSet.startPosition*rotStepPair);
    p = pNorm;
    
    char d;
    int basePairBit;
    int bitOffset;
    float percent;
    mCounter+=.01;
    while(mCounter > 50) mCounter -= 50;
        
    for(int i=0;i<basePairs;i++){
        
        d = dataSet.dataBitsString[i];
        
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
        
        p = pNorm;
        p.rotate( i*rotStepPair );
        
        p *= lerp(circDiaShort,circDiaLong,basePairBit/3.0f);
        p += pOffset;
        
//        drawWorm(wormStart,wormLength,i,dataSet.startPosition,p,pPrev);
        
        
        mShape.color( mColorDark );
        if(i==0){
            pStart = p;
            mShape.moveTo( p );
        }else{
            mShape.lineTo( p );
        }
        
        mShape.color( mColorDark );
        mShape.moveTo( p );
        mShape.color( ColorAf(1,1,1,1) );
        addSpotShape( &mShape, p, mSpotSize );
        mShape.color( mColorDark );
        mShape.moveTo( p );
        
        pPrev = p;
        
//        if( (basePairBit & 1) == 1) drawLine( &mShape, p*circDiaShort+pOffset, p*circDiaLong+pOffset, percent );
//        //            drawLine( &s, p*circDiaShort+pOffset, p*circDiaLong+pOffset );
//        p.rotate(rotStepBit);
//        
//        if( (basePairBit & 2) == 2) drawLine( &mShape, p*circDiaShort+pOffset, p*circDiaLong+pOffset, percent );
//        //            drawLine( &s, p*circDiaShort+pOffset, p*circDiaLong+pOffset );
//        p.rotate(rotStepBit);
//        
//        p.rotate(rotStepPairDist);
        
    }
    if(basePairs > 0){
        mShape.color( ColorAf(0,0,0,0) );
        mShape.lineTo( pStart );
        mShape.moveTo( pStart );
        
        
    }
    
    
    
    return mShape;

    
}

// ------------------------------------------------------------------------------------------------------

void WebsPlugin::drawWorm( float wormStart, float wormLength, int pos, int offset, Vec2f p, Vec2f pPrev){
    
    if(pos == 0){
        mShape.color( mColorDark );
        mShape.moveTo( p );
        return;
    }
    offset = 0;
    float wormEnd = wormStart+wormLength;
    Vec2f pStep;
    float dist = (wormStart-((pos+offset)%50));
    
    float relationalStart = wormStart-(pos-1);
    float relationalEnd = relationalStart+wormLength;

    mShape.color( mColorDark );
    
//    float percentage = 
    
    
    bool isStart = false;
    bool isEnd = false;
    
    if(relationalStart > 0 && relationalStart < 1){
        isStart = true;
    }
    if(relationalEnd > 0 && relationalEnd < 1){
        isEnd = true;
    }
    
    
//    if(isStart==0&&isEnd==0){
//        
//    }else if(isStart){
//        
//    }else if(isEnd){
//        
//    }else if()
    
    
    mShape.lineTo(p);

    if( dist < 0 ){
        mShape.color( mColorDark );
        mShape.lineTo(p);
    }else if( dist < 1 ){
        
        pStep = lerp(pPrev,p,dist);
        mShape.color( mColorDark );
        mShape.lineTo(pStep);
        mShape.color( mColorBright );
        addSpotShape( &mShape,pStep,.02);
        mShape.color( mColorDark );
        mShape.lineTo(p);

//        pStep = lerp(pPrev,p,dist);
//        mShape.color( mColorDark );
//        mShape.lineTo(pStep);
//        for(float i=dist;i<min(1.0f,wormEnd);i+=.02){
//            pStep = lerp(pPrev,p,i);
//            mShape.color( mColorBright );
//            mShape.lineTo(pStep);
//        }
    }else if( (dist+1) < wormEnd ){
        for(float i=0;i<min(1.0f,wormEnd-dist);i+=.02){
            pStep = lerp(pPrev,p,i);
            mShape.color( mColorBright );
            mShape.lineTo(pStep);
        }
        
        
    }else{
        mShape.color( mColorDark );
        mShape.lineTo( p );
    }
    mShape.color( mColorDark );
//    if( (int)(mCounter-i) % 9 == 5) mShape.color( mColorBright );
//    else mShape.color( mColorDark );
}

void WebsPlugin::addSpotShape( ColouredShape2d* s, Vec2f center, float size ){
    float size2 = size/2.0f;
    Vec2f p;
    p.x = -size2;
    p.y = -size2;
    s->lineTo( center + p );
    p.x = size2;
    s->lineTo( center + p );
    p.y = size2;
    s->lineTo( center + p );
    p.x = -size2;
    s->lineTo( center + p );
    p.y = -size2;
    s->lineTo( center + p );
}

