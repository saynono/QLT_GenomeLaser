//
//  Swirl.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 16.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "SwirlPlugin.h"

	
SwirlPlugin::SwirlPlugin(): BasePlugin( "SwirlPlugin" ){
}

void SwirlPlugin::setup(){
    
    mTimeStamp = getElapsedSeconds();
    
    
    mRadBasePair = toRadians(2.0f);
    mAmountBasePair = 10;
    mSpotSize = .01;
    
    mCircDiameter = .5;
    mLineHeight = .4;
    mWormLength = 8.0f;
    mWormSpeed = .01;
    mSphereRotSpeed = .1;
    mSphereRotation = 0;
    
    mOSCMap.insert( make_pair( "RAD_PER_BASEPAIR", new OSCElement( "RAD_PER_BASEPAIR", this, &mRadBasePair, OSCElement::FLOAT, toRadians(0.1f), toRadians(60.0f)  )) );
    mOSCMap.insert( make_pair( "AMOUNT_BASEPAIRS_PERCENT", new OSCElement( "AMOUNT_BASEPAIRS_PERCENT", this, &mAmountBasePair, OSCElement::INTEGER, 1, 50 )) );
    mOSCMap.insert( make_pair( "SPOT_SIZE", new OSCElement( "SPOT_SIZE", this, &mSpotSize, OSCElement::FLOAT, 0.001f, .1f )) );
    mOSCMap.insert( make_pair( "CIRC_DIAMETER", new OSCElement( "SPOT_SIZE", this, &mCircDiameter, OSCElement::FLOAT, 0.0f, .5f )) );
    mOSCMap.insert( make_pair( "LINE_HEIGHT", new OSCElement( "SPOT_SIZE", this, &mLineHeight, OSCElement::FLOAT, 0.0f, 1.0f )) );
    mOSCMap.insert( make_pair( "SPHERE_ROT_SPEED", new OSCElement( "SPHERE_ROT_SPEED", this, &mSphereRotSpeed, OSCElement::FLOAT, -.2f, .2f )) );
    mOSCMap.insert( make_pair( "WORM_LENGTH", new OSCElement( "WORM_LENGTH", this, &mWormLength, OSCElement::FLOAT, 0.1f, 50.0f )) );
    mOSCMap.insert( make_pair( "WORM_COLOR", new OSCElement( "WORM_COLOR", this, &mColorDark, OSCElement::COLOR )) );
    //    mOSCMap.insert( make_pair( "WORM_SPEED", new OSCElement( "WORM_SPEED", this, &mWormSpeed, OSCElement::COLOR, -2.f, 2.0f )) );
    
    mColorDark = ColorAf(.4,1,0,1);
    mColorBright = ColorAf(0.1,.8,.8,1);
    mCounter = 6;
    
}

void SwirlPlugin::dispose(){
}


// ------------------------------------------------------------------------------------------------------

const map<string, OSCElement*>& SwirlPlugin::getOSCMapping() {
    return mOSCMap;
}

// ------------------------------------------------------------------------------------------------------

const ColouredShape2d& SwirlPlugin::getShape( const GenomeData::BasePairDataSet& dataSet ){
    
    mShape.clear();
    
    Vec2f p,pStart,pPrev;
    Vec2f pNorm(0,.5);
    Vec2f pOffset(.5,.5);
    
    int basePairs = dataSet.roi.basePairsCount;
    
    float circDiameter = mCircDiameter;
    float lineHeight = mLineHeight*circDiameter;
    float lineHeight2 = lineHeight/2.0;
    float circDiaLong = circDiameter;
    float circDiaShort = circDiameter-lineHeight;
    
    float rotStepPair = toRadians(6.0f);// mRadBasePair;
    
    //    mWormSpaceLength = 100;
    mCounter+=mWormSpeed;
    
    int pos;
    pos = dataSet.roi.startPosition;
    pos = dataSet.percent ;
    float wormLength = mWormLength;
    float wormStart = dataSet.percent*(float)basePairs;
    //        console() << dataSet.percent << " wormStart : " << wormStart << "          pos : " << pos << " (l:"<<basePairs<<")         [ " << dataSet.roi.startPosition << " - " << (dataSet.roi.endPosition) << " ]" << std::endl;
    if(mWormSpeed < 0){
        if( wormStart < pos - mWormLength) mCounter = pos + basePairs;
    }else{
        //            if( wormStart > pos + basePairs + mWoBitsPluginrmLength) console() << " ----> wormStart : " << wormStart << "          mWormLength : " << mWormLength << std::endl;
        if( wormStart > pos + basePairs + mWormLength) mCounter = pos - mWormLength;
    }
    
    double tb = mTimeStamp;
    mTimeStamp = getElapsedSeconds();
    mSphereRotation += mSphereRotSpeed * (mTimeStamp-tb);
    float rot = dataSet.roi.startPosition*rotStepPair;
    rot += mSphereRotation;
    //        console() << " mSphereRotSpeed : " << mSphereRotSpeed << "          => " << (mSphereRotSpeed * (mTimeStamp-timeBefore)) << std::endl;
    
    pNorm.rotate(rot);
    p = pNorm;
    pPrev = p;
    
    char d;
    int basePairBit;
    int cnt = 0;
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
        
        //            mColorBright = ColorAf::white();
        //            mColorDark = ColorAf::white();
        
        p = pPrev;
        p.normalize();
        p *= lerp(circDiaShort,circDiaLong,basePairBit/3.0f);
        //            mShape.color( mColorBright );
//        if(i==0) mShape.moveTo( p+pOffset );
        //            else mShape.lineTo( p+pOffset );
        pos = cnt++;//dataSet.roi.startPosition - dataSet.roi.startPosition + cnt++;
        drawWorm(wormStart,wormLength,pos,p+pOffset,pPrev+pOffset);
        
        pPrev = p;
        p.rotate( rotStepPair );
        
        pos = cnt++;
        drawWorm(wormStart,wormLength,pos,p+pOffset,pPrev+pOffset);
        
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

void SwirlPlugin::drawWorm( float wormStart, float wormLength, int pos, Vec2f p, Vec2f pPrev){
    
    if(pos==0){
        return;
    }
    
    
//    float distStart = wormStart - (pos-1);
//    float distEnd = (wormStart-wormLength) - (pos-1);
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
    //    Vec2f pCompStart = lerp(pPrev,p, percentLineStart );
    //    Vec2f pCompEnd = lerp(pPrev,p, percentLineEnd );
    Vec2f pComp;
    
    ColorA clrStart = lerp( mColorBright, mColorDark, percentMixStart );
    ColorA clrEnd = lerp( mColorBright, mColorDark, percentMixEnd );
    ColorA clr;
    
    float clrMixValue;
    
//    mShape.getNumContours()
    mShape.color(clrStart);
//    console() << "mShape.getNumContours() : " << mShape.getNumContours() <<  std::endl;
//    if(percentLineEnd != 0) console() << "counter : " << mShape.getNumContours() << std::endl;
//    if(percentLineEnd != 0)
    if( mShape.getNumContours() == 0) mShape.moveTo(pCompStart);
    mShape.lineTo(pCompStart);
    //    for(float i=percentLineEnd;i<percentLineStart;i+=.02){
    
//    float step = 1.0f/((pCompStart-pCompEnd).length() / .02);
//    
//    for(float i=percentLineStart;i<percentLineEnd;i+=step){
//        clrMixValue = ci::math<float>::clamp((i-percentLineStart)/(percentLineEnd-percentLineStart));
//        clr = lerp( clrStart, clrEnd, clrMixValue );
//        //        pComp = lerp( pPrev, p, i );
//        pComp = PluginUtils::lerpLineDistorted(pPrev,p,center,i);
//        mShape.color(clr);
//        mShape.lineTo(pComp);
//    }
    mShape.color(clrEnd);
    mShape.lineTo(pCompEnd);
    
}



void SwirlPlugin::addSpotShape( ColouredShape2d* s, Vec2f center, float size ){
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
