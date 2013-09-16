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
    mWormLength = 4.0f;
    mWormSpeed = .03;
    
    mWormSpaceLength = 20;


    mOSCMap.insert( make_pair( "RAD_PER_BASEPAIR", new OSCElement( "RAD_PER_BASEPAIR", this, &mRadBasePair, OSCElement::FLOAT, toRadians(0.1f), toRadians(60.0f)  )) );
    mOSCMap.insert( make_pair( "AMOUNT_BASEPAIRS_PERCENT", new OSCElement( "AMOUNT_BASEPAIRS_PERCENT", this, &mAmountBasePair, OSCElement::INTEGER, 1, 50 )) );
    mOSCMap.insert( make_pair( "SPOT_SIZE", new OSCElement( "SPOT_SIZE", this, &mSpotSize, OSCElement::FLOAT, 0.001f, .1f )) );
    mOSCMap.insert( make_pair( "CIRC_DIAMETER", new OSCElement( "SPOT_SIZE", this, &mCircDiameter, OSCElement::FLOAT, 0.0f, 1.0f )) );
    mOSCMap.insert( make_pair( "LINE_HEIGHT", new OSCElement( "SPOT_SIZE", this, &mLineHeight, OSCElement::FLOAT, 0.0f, 1.0f )) );
    mOSCMap.insert( make_pair( "WORM_LENGTH", new OSCElement( "WORM_LENGTH", this, &mWormLength, OSCElement::FLOAT, 0.1f, 20.0f )) );
    mOSCMap.insert( make_pair( "WORM_SPEED", new OSCElement( "WORM_SPEED", this, &mWormSpeed, OSCElement::FLOAT, -2.f, 2.0f )) );
    mOSCMap.insert( make_pair( "WORM_COLOR", new OSCElement( "WORM_COLOR", this, &mColorDark, OSCElement::COLOR )) );
//    mOSCMap.insert( make_pair( "WORM_SPEED", new OSCElement( "WORM_SPEED", this, &mWormSpeed, OSCElement::COLOR, -2.f, 2.0f )) );
    
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
    
    int basePairs = dataSet.basePairsCount;
        
    float circDiameter = mCircDiameter;
    float lineHeight = mLineHeight;
    float lineHeight2 = lineHeight/2.0;
    float circDiaLong = circDiameter + lineHeight2;
    float circDiaShort = circDiameter - lineHeight2;
    
    float rotStepPair = mRadBasePair;
    
    
    float clrVal = dataSet.percent/4.0f;
    clrVal += (dataSet.startPosition/100000.0f) ;
    clrVal = fmod(clrVal,1.0f);
    mColorDark = lerp(mColorDark,mColors.getColor(0,clrVal),.01);
    clrVal = fmod(clrVal+.3f,1.0f);
    mColorBright = lerp(mColorBright,mColors.getColor(1,clrVal),.01);

//    mWormSpaceLength = 100;
    mCounter+=mWormSpeed;
//    mCounter += mWormSpaceLength;
//    while(mCounter > mWormSpaceLength) mCounter -= mWormSpaceLength;
    
    int pos;
    pos = dataSet.startPosition - dataSet.roi.startPosition;
    float wormLength = mWormLength;
    float wormStart = mCounter;
    
//    console() << " wormStart : " << wormStart << "          pos : " << pos << " (l:"<<basePairs<<")         [ " << dataSet.roi.startPosition << " - " << (dataSet.roi.endPosition) << " ]" << std::endl;
    if(mWormSpeed < 0){
        if( wormStart < pos - mWormLength) mCounter = pos + basePairs;
    }else{
        if( wormStart > pos + basePairs + mWormLength) console() << " ----> wormStart : " << wormStart << "          mWormLength : " << mWormLength << std::endl;
        if( wormStart > pos + basePairs + mWormLength) mCounter = pos - mWormLength;
    }
    
    
    
    pNorm.rotate(dataSet.startPosition*rotStepPair);
    p = pNorm;
    
    char d;
    int basePairBit;
    int bitOffset;
    float percent;
    
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
        
        p = PluginUtils::harshMaxDiameter(p,pOffset,.5f);

        if(i==0){
            pStart = p;
//            mShape.color( ColorAf(0,0,0,0) );
//            mShape.moveTo( pStart );
        }else{
            pos = dataSet.startPosition - dataSet.roi.startPosition + i;
            drawWorm(wormStart,wormLength,pos,p,pPrev);            
        }
        
//        mShape.color( mColorDark );
//        mShape.moveTo( p );
//        mShape.color( ColorAf(1,1,1,1) );
//        addSpotShape( &mShape, p, mSpotSize );
//        mShape.color( mColorDark );
//        mShape.moveTo( p );
        
        pPrev = p;
        
    }

    if(basePairs > 0){
//        mShape.color( ColorAf(0,0,0,0) );
//        mShape.lineTo( pStart );
//        mShape.moveTo( pStart );
    }
    
    return mShape;

}

// ------------------------------------------------------------------------------------------------------
/*
void WebsPlugin::drawWorm( float wormStart, float wormLength, int pos, Vec2f p, Vec2f pPrev){

//    if(pos == 0){
//        mShape.color( mColorDark );
//        mShape.moveTo( p );
//        return;
//    }

    if(pos==0){
        return;
    }
    
//    pos += offset;
//    pos +=
    
    float distStart = wormStart - (pos-1);
    float distEnd = (wormStart-wormLength) - (pos-1);
    
    if(distEnd > 1){
        
//        mShape.color(mColorDark);
//        mShape.moveTo(pPrev);
//        mShape.lineTo(p);
        
        return;
    }else if(distStart < 0){
        
//        mShape.color(mColorDark);
//        mShape.moveTo(pPrev);
//        mShape.lineTo(p);
        
        return;
    }
    
    float percentStart = distStart/wormLength;
    float percentEnd = distEnd/wormLength;
    
    float percentLineStart = ci::math<float>::clamp(distStart);
    float percentLineEnd = ci::math<float>::clamp(distEnd);
    
    float percentMixStart = (distStart-percentLineStart) / wormLength;
    float percentMixEnd = (distStart-percentLineEnd) / wormLength;
    
    
    Vec2f center(.5,.5);
    
    Vec2f pCompStart = PluginUtils::lerpLineDistorted(pPrev,p,center,percentLineStart);
    Vec2f pCompEnd = PluginUtils::lerpLineDistorted(pPrev,p,center,percentLineEnd);
//    Vec2f pCompStart = lerp(pPrev,p, percentLineStart );
//    Vec2f pCompEnd = lerp(pPrev,p, percentLineEnd );
    Vec2f pComp;
    
    ColorA clrStart = lerp( mColorBright, mColorDark, percentMixStart );
    ColorA clrEnd = lerp( mColorBright, mColorDark, percentMixEnd );
    ColorA clr;
    
    float clrMixValue;
    
    mShape.color(clrStart);
    mShape.moveTo(pCompStart);
    mShape.lineTo(pCompStart);
//    for(float i=percentLineEnd;i<percentLineStart;i+=.02){
    for(float i=percentLineStart;i<percentLineEnd;i+=.02){
        clrMixValue = ci::math<float>::clamp((i-percentLineStart)/(percentLineEnd-percentLineStart));
        clr = lerp( clrStart, clrEnd, clrMixValue );
//        pComp = lerp( pPrev, p, i );
        pComp = PluginUtils::lerpLineDistorted(pPrev,p,center,i);
        mShape.color(clr);
        mShape.lineTo(pComp);
    }
    mShape.color(clrEnd);
    mShape.lineTo(pCompEnd);

}
*/


void WebsPlugin::drawWorm( float wormStart, float wormLength, int pos, Vec2f p, Vec2f pPrev){
    
    if(pos==0){
        return;
    }
    
    float distEnd = wormStart - (pos-1);
    float distStart = (wormStart-wormLength) - (pos-1);
    
    if(distStart > 1){
        return;
    }else if(distEnd < 0){
        return;
    }
    
    float percentStart = distStart/wormLength;
    float percentEnd = distEnd/wormLength;
    
    float percentLineStart = ci::math<float>::clamp(distStart);
    float percentLineEnd = ci::math<float>::clamp(distEnd);
    
    float percentMixEnd = (distEnd-percentLineStart) / wormLength;
    float percentMixStart = (distEnd-percentLineEnd) / wormLength;
    
    Vec2f center(.5,.5);
    
    Vec2f pCompStart = PluginUtils::lerpLineDistorted(pPrev,p,center,percentLineStart);
    Vec2f pCompEnd = PluginUtils::lerpLineDistorted(pPrev,p,center,percentLineEnd);
    Vec2f pComp;
    
    ColorA clrStart = lerp( mColorBright, mColorDark, percentMixStart );
    ColorA clrEnd = lerp( mColorBright, mColorDark, percentMixEnd );
    ColorA clr;
    
    float clrMixValue;
    
    mShape.color(clrStart);
    if( mShape.getNumContours() == 0) mShape.moveTo(pCompStart);
    mShape.lineTo(pCompStart);
    mShape.color(clrEnd);
    mShape.lineTo(pCompEnd);
    
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

