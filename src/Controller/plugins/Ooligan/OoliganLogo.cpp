//
//  OoliganLogo.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 28.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "OoliganLogo.h"

	
OoliganLogo::OoliganLogo(): BasePlugin( "OoliganLogo" ){
}

void OoliganLogo::setup(){

    mStarScale = .02;
    mStarWidth = .1;
    
//    mOSCMap.insert( make_pair( "RAD_PER_BASEPAIR", new OSCElement( "RAD_PER_BASEPAIR", this, &mRadBasePair, OSCElement::FLOAT, toRadians(0.1f), toRadians(60.0f)  )) );
//    mOSCMap.insert( make_pair( "AMOUNT_BASEPAIRS_PERCENT", new OSCElement( "AMOUNT_BASEPAIRS_PERCENT", this, &mAmountBasePair, OSCElement::INTEGER, 1, 50 )) );
//    mOSCMap.insert( make_pair( "SPOT_SIZE", new OSCElement( "SPOT_SIZE", this, &mSpotSize, OSCElement::FLOAT, 0.001f, .1f )) );
//    mOSCMap.insert( make_pair( "CIRC_DIAMETER", new OSCElement( "SPOT_SIZE", this, &mCircDiameter, OSCElement::FLOAT, 0.0f, 1.0f )) );
//    mOSCMap.insert( make_pair( "LINE_HEIGHT", new OSCElement( "SPOT_SIZE", this, &mLineHeight, OSCElement::FLOAT, 0.0f, 1.0f )) );
//    mOSCMap.insert( make_pair( "WORM_LENGTH", new OSCElement( "WORM_LENGTH", this, &mWormLength, OSCElement::FLOAT, 0.1f, 20.0f )) );
//    mOSCMap.insert( make_pair( "WORM_SPEED", new OSCElement( "WORM_SPEED", this, &mWormSpeed, OSCElement::FLOAT, -2.f, 2.0f )) );
    mOSCMap.insert( make_pair( "STARSCALE", new OSCElement( "STARSCALE", this, &mStarScale, OSCElement::FLOAT, .01f, .2f )) );
    mOSCMap.insert( make_pair( "WIDTH", new OSCElement( "WIDTH", this, &mStarWidth, OSCElement::FLOAT, .01f, .2f )) );
    
    mColorStart = ColorAf(.3,0,0,1);
    mColorEnd = ColorAf(0,.8,1,1);
    
    int peaks = 5;
    float angle = 0;
    float angleAdd = toRadians( 360.0 / (float)(peaks*2.0));
    for(int i=0;i<peaks*2;i++){
        Vec2f p(0,-.5);
        angle = toRadians( i/(float)peaks*2.0f );
        p.rotate( angleAdd * i );
        mStarVec.push_back( p );
    }
    
    line l;
    l.p1 = Vec2f(.5-.2,.56);
    l.p2 = Vec2f(.5+.2,.56);
    mLines.push_back(l);
    l.p1 = Vec2f(.5+.17,.54);
    l.p2 = Vec2f(.5-.17,.54);
    mLines.push_back(l);
    l.p1 = Vec2f(.5-.14,.52);
    l.p2 = Vec2f(.5+.14,.52);
    mLines.push_back(l);
    
}

void OoliganLogo::dispose(){
}


// ------------------------------------------------------------------------------------------------------

const map<string, OSCElement*>& OoliganLogo::getOSCMapping() {
    return mOSCMap;
}

// ------------------------------------------------------------------------------------------------------

const ColouredShape2d& OoliganLogo::getShape( const GenomeData::BasePairDataSet& dataSet ){
    
    mShape.clear();    
    
    float clrVal = dataSet.percent/8.0f;
    clrVal += (dataSet.startPosition/10000000.0f) ;
    clrVal += dataSet.chromosomeData.chromosomeID/20.0f;
    clrVal = fmod(clrVal,1.0f);
    mColorStart = lerp(mColorStart,mColors.getColor(0,clrVal),.03);
    clrVal = fmod(clrVal+.1f,1.0f);
    mColorEnd = lerp(mColorEnd,mColors.getColor(1,clrVal),.03);
    
    mShape.color(mColorStart);
    addStar( &mShape, Vec2f(0.5+mStarWidth,0.65), mStarScale);
    mShape.color( lerp(mColorStart,mColorEnd,.5) );
    addStar( &mShape, Vec2f(0.5,0.68), mStarScale);
    mShape.color(mColorEnd);
    addStar( &mShape, Vec2f(0.5-mStarWidth,0.65), mStarScale);
    
    
    addLine( &mShape, mLines[0].p1, mLines[0].p2 );
    addLine( &mShape, mLines[1].p1, mLines[1].p2 );
    addLine( &mShape, mLines[2].p1, mLines[2].p2 );
    
    return mShape;
    
}

void OoliganLogo::addLine( ColouredShape2d* shape, Vec2f p1, Vec2f p2 ){
    shape->moveTo(p1);
    shape->lineTo(p2);
}

void OoliganLogo::addStar( ColouredShape2d* shape, Vec2f pos, float scale){
    
    shape->moveTo(mStarVec[0]*scale+pos);
    float in = 1;
    for(int i=1;i<mStarVec.size();i++){
        if(i%2==1) in = .5;
        else in = 1.0;
        shape->lineTo(mStarVec[i]*scale * in+pos);
    }
    shape->lineTo(mStarVec[0]*scale+pos);
}