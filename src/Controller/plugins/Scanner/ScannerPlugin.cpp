//
//  ScannerPlugin.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 17.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "ScannerPlugin.h"



ScannerPlugin::ScannerPlugin(): BasePlugin( "ScannerPlugin" ){
}

void ScannerPlugin::setup(){
    
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
    
    mColorStart = ColorAf(.4,.8,.3,1);
    mColorEnd = ColorAf(0.76,.3,.8,1);

    
    mOSCMap.insert( make_pair( "RAD_PER_BASEPAIR", new OSCElement( "RAD_PER_BASEPAIR", this, &mRadBasePair, OSCElement::FLOAT, toRadians(0.1f), toRadians(60.0f)  )) );
    mOSCMap.insert( make_pair( "AMOUNT_BASEPAIRS_PERCENT", new OSCElement( "AMOUNT_BASEPAIRS_PERCENT", this, &mAmountBasePair, OSCElement::INTEGER, 1, 50 )) );
    mOSCMap.insert( make_pair( "SPOT_SIZE", new OSCElement( "SPOT_SIZE", this, &mSpotSize, OSCElement::FLOAT, 0.001f, .1f )) );
    mOSCMap.insert( make_pair( "CIRC_DIAMETER", new OSCElement( "SPOT_SIZE", this, &mCircDiameter, OSCElement::FLOAT, 0.0f, .5f )) );
    mOSCMap.insert( make_pair( "LINE_HEIGHT", new OSCElement( "SPOT_SIZE", this, &mLineHeight, OSCElement::FLOAT, 0.0f, 1.0f )) );
    mOSCMap.insert( make_pair( "SPHERE_ROT_SPEED", new OSCElement( "SPHERE_ROT_SPEED", this, &mSphereRotSpeed, OSCElement::FLOAT, -1.f, 1.f )) );
    mOSCMap.insert( make_pair( "WORM_LENGTH", new OSCElement( "WORM_LENGTH", this, &mWormLength, OSCElement::FLOAT, 0.1f, 20.0f )) );
    mOSCMap.insert( make_pair( "WORM_COLOR_START", new OSCElement( "WORM_COLOR_START", this, &mColorStart, OSCElement::COLOR )) );
    mOSCMap.insert( make_pair( "WORM_COLOR_END", new OSCElement( "WORM_COLOR_END", this, &mColorEnd, OSCElement::COLOR )) );
    //    mOSCMap.insert( make_pair( "WORM_SPEED", new OSCElement( "WORM_SPEED", this, &mWormSpeed, OSCElement::COLOR, -2.f, 2.0f )) );
    
    mRotCounter = 6;
    
    mLastDataSetID = 0;

}

void ScannerPlugin::dispose(){
}


// ------------------------------------------------------------------------------------------------------

const map<string, OSCElement*>& ScannerPlugin::getOSCMapping() {
    return mOSCMap;
}

// ------------------------------------------------------------------------------------------------------

const ColouredShape2d& ScannerPlugin::getShape( const GenomeData::BasePairDataSet& dataSet ){
    
    
    if(mLastDataSetID != dataSet.roi.roiId){
        float val = mRotCounter+6.0f;
        mLastDataSetID = dataSet.roi.roiId;
//        timeline().apply( &mAnimationColor, ColorA( 1.,1.,1.,0. ), 1.f, EaseOutSine() )
//        .finishFn( std::bind( &FlightDateDestination::reachedAnimationEnd , this ) );
        timeline().apply( &mRotCounter, val, .7f, EaseOutQuad() );
    }
    
    mShape.clear();
    
    Vec2f p,pStart,pEnd,pPrev,pCenter;
    Vec2f pNorm(0,.5);
    Vec2f pOffset(.5,.5);
    float percent = 0;
    
    int basePairs = dataSet.roi.basePairsCount;
    
    float circDiameter = mCircDiameter;
        
    int pos;
    pos = dataSet.percent ;
    
    double tb = mTimeStamp;
    mTimeStamp = getElapsedSeconds();
    
    pStart = Vec2f( 0,-circDiameter );
    pCenter = Vec2f( lerp(-circDiameter,circDiameter, (float)sin(dataSet.percent*M_PI)), 0 );
    pEnd = Vec2f( 0, circDiameter );
    
//    pStart.rotate( toRadians(mRotCounter) );
//    pCenter.rotate( toRadians(mRotCounter) );
//    pEnd.rotate( toRadians(mRotCounter) );
    
    mShape.color(mColorStart);
    mShape.moveTo( pStart );
    int detail = 20;
    for(int i=0;i<detail;i++){
        percent = (i/(float)detail);
        p = PluginUtils::lerpLineDistortedCorrect(pStart,pCenter,Vec2f::zero(), percent );
        mShape.color( lerp(mColorStart,mColorEnd,percent/2.0) );
        mShape.lineTo( p );
    }
//    mShape.lineTo( pCenter );
    for(int i=0;i<=detail;i++){
        percent = (i/(float)detail);
        p = PluginUtils::lerpLineDistortedCorrect(pCenter,pEnd,Vec2f::zero(), percent );
        mShape.color( lerp(mColorStart,mColorEnd,percent/2.0+.5) );
        mShape.lineTo( p );
    }
    
    
    
    mShape.color(mColorEnd);
    mShape.lineTo( pEnd );
    MatrixAffine2f matr;
    matr.translate(Vec2f(.5,.5));
    matr.transformPoint( Vec2f(.5,.5) );
    matr.rotate(toRadians(mRotCounter));
    mShape.transform(matr);
//    matr.translate(pOffset);
//    mShape.transform(matr);
//    Vec2f pCompStart = PluginUtils::lerpLineDistorted(pStart,p,center,percentLineStart);
//    Vec2f pCompCenter = PluginUtils::lerpLineDistorted(pPrev,p,center,percentLineStart);
//    Vec2f pCompEnd = PluginUtils::lerpLineDistorted(pEnd,p,center,percentLineEnd);

    
    
//    pNorm.rotate(rot);
//    p = pNorm;
//    pPrev = p;
//    
//    char d;
//    int basePairBit;
//    int cnt = 0;
//    for(int i=0;i<basePairs;i++){
//        
//        d = dataSet.dataBitsString[i];
//        
//        switch(d){
//            case 'A':
//                basePairBit = 0;
//                break;
//            case 'C':
//                basePairBit = 1;
//                break;
//            case 'G':
//                basePairBit = 2;
//                break;
//            case 'T':
//                basePairBit = 3;
//                break;
//        }
//        
//        //            mColorBright = ColorAf::white();
//        //            mColorDark = ColorAf::white();
//        
//        p = pPrev;
//        p.normalize();
//        p *= lerp(circDiaShort,circDiaLong,basePairBit/3.0f);
//        //            mShape.color( mColorBright );
//        if(i==0) mShape.moveTo( p+pOffset );
//        //            else mShape.lineTo( p+pOffset );
//        pos = cnt++;//dataSet.roi.startPosition - dataSet.roi.startPosition + cnt++;
//        drawWorm(wormStart,wormLength,pos,p+pOffset,pPrev+pOffset);
//        
//        pPrev = p;
//        p.rotate( rotStepPair );
//        
//        pos = cnt++;
//        drawWorm(wormStart,wormLength,pos,p+pOffset,pPrev+pOffset);
//        
//        pPrev = p;
//        
//    }
    
    return mShape;
    
}

// ------------------------------------------------------------------------------------------------------

void ScannerPlugin::drawWorm( float wormStart, float wormLength, int pos, Vec2f p, Vec2f pPrev){
    
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
    
    ColorA clrStart = lerp( mColorStart, mColorEnd, percentMixStart );
    ColorA clrEnd = lerp( mColorStart, mColorEnd, percentMixEnd );
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



void ScannerPlugin::addSpotShape( ColouredShape2d* s, Vec2f center, float size ){
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
