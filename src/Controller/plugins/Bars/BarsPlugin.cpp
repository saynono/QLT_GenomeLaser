//
//  Bars.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 31.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "BarsPlugin.h"

BarsPlugin::BarsPlugin(): BasePlugin( "BarsPlugin" ){
}


void BarsPlugin::setup(){
    mBeamDiameter = .01f;
    mBeamDistance = .2f;
    mOSCMap.insert( make_pair( "BEAM_DIAMETER", new OSCElement( "BEAM_DIAMETER", this, &mBeamDiameter, OSCElement::FLOAT,.001, .1 )) );
    mOSCMap.insert( make_pair( "BEAM_DISTANCE", new OSCElement( "BEAM_DISTANCE", this, &mBeamDistance, OSCElement::FLOAT,.01, .5 )) );
    mOSCMap.insert( make_pair( "OFFSET", new OSCElement( "OFFSET", this, &mBeamOffset, OSCElement::INTEGER,0, 5 )) );
    //    //    mOSCMap.insert( make_pair( "WORM_SPEED", new OSCElement( "WORM_SPEED", this, &mWormSpeed, OSCElement::COLOR, -2.f, 2.0f )) );
    //
    //    mRotCounter = 6;
    //
    //    mLastDataSetID = 0;
    
    float detail = 50;
    float percent;
    float angle;
    for(float i=0;i<=detail;i++){
        percent = i/detail;
        angle = toRadians(360*percent);
        mBeam.push_back( Vec2f( sin(angle), cos(angle) ));
    }
    for(float i=0;i<4;i++){
        angle = toRadians(i*90);
        mDataLines.push_back( Vec2f( sin(angle), cos(angle) ));
    }
    
    
    mLastDataSetID = 0;
    mRoiTicker = 0;
}

void BarsPlugin::dispose(){
}


// ------------------------------------------------------------------------------------------------------

const map<string, OSCElement*>& BarsPlugin::getOSCMapping() {
    return mOSCMap;
}

const ColouredShape2d& BarsPlugin::getShape( const GenomeData::BasePairDataSet& dataSet ){
    
    
    if(mLastDataSetID != dataSet.roi.roiId){
        //        float val = mRotCounter+6.0f;
        console() << " NEW DATA SET "<< mRoiTicker << std::endl;
        mLastDataSetID = dataSet.roi.roiId;
        mCurrentDataSetDescription = toString(dataSet.roi.chromosomeData.chromosomeID) + " " + toString(dataSet.roi.roiId) + " " + toString(dataSet.roi.positionTotal);
        mRoiTicker = 0;
        //        console() << " mCurrentDataSetDescription : " << mCurrentDataSetDescription << std::endl;
        //        timeline().apply( &mRotCounter, val, 2.7f, EaseInOutQuad() );
        //        recreateElements(dataSet);
    }
    
    int pos = dataSet.percent * dataSet.basePairsCount;
    float clrVal = dataSet.percent/8.0f;
    clrVal += (dataSet.startPosition/10000000.0f) ;
    clrVal += dataSet.chromosomeData.chromosomeID/20.0f;
    clrVal = fmod(clrVal,1.0f);
    //    mColorStart = colors.getColor(0,clrVal);
    ColorAf clr = mColors.getColor(0,clrVal);
    clr = ColorAf::white();
    mColorStart = lerp(mColorStart,clr,.01);
    clrVal = fmod(clrVal+.3f,1.0f);
    //    mColorEnd = colors.getColor(1,clrVal);
    clr = mColors.getColor(1,clrVal);
    clr = ColorAf::white();
    mColorEnd = lerp(mColorEnd,clr,.01);
    
    char d = dataSet.dataBitsString[pos];
    int basePairBit = 0;
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
    
    bool rot = pos%2==1;
    //    console() << "  d  : " << d << std::endl;
    float dia = mBeamDiameter;//.02;
    float dist = mBeamDistance;//.2;
    //    //    console() << "(dataSet.startPosition/100000.0f) : " << (dataSet.startPosition/100000.0f) << std::endl;
    //
    mShape.clear();
    //    if(rot)
    //    else drawBeam(Vec2f(.5,.3),.1);
    
    mShape.color(mColorStart);
    //    mShape.moveTo(-(dist-dia),0);
    //    mShape.lineTo(-(dist-dia),0);
    //    mShape.lineTo((dist-dia),0);
    ////    mShape.color(mColorEnd);
    //    mShape.moveTo(0,-(dist-dia));
    //    mShape.lineTo(0,(dist-dia));
    
    if( (basePairBit & 1) == 1){
        //        mShape.color(mColorStart);
        drawBeam(Vec2f(-dist,0),dia);
    }
    
    if( ((basePairBit >> 1) & 1) == 1){
        //        mShape.color(mColorEnd);
        drawBeam(Vec2f(dist,0),dia);
    }
    
    clr = ColorAf::white();
    mShape.color(clr);
//    drawDescription( Vec2f::zero(), (dist-dia), mCurrentDataSetDescription, mRoiTicker++ / 2);
    
    MatrixAffine2f matr;
    if(rot){
        matr.rotate( toRadians(90.0f) );
        mShape.transform(matr);
        matr.setToIdentity();
    }
    matr.translate(Vec2f(.5,.5));
    mShape.transform(matr);
    matr.setToIdentity();
    matr.rotate( toRadians(45.0f) );
    mShape.transform(matr);
    
    //
    //    Vec2f p,pStart,pEnd,pPrev,pCenter;
    //    Vec2f pNorm(0,.5);
    //    Vec2f pOffset(.5,.5);
    //    float percent = 0;
    //
    //    int basePairs = dataSet.roi.basePairsCount;
    //
    //    float circDiameter = mCircDiameter;
    //    float lineHeight2 = mLineHeight/2.0;
    //    float circDiaLong = .4;
    //    float circDiaShort = .1;
    //    float rotStepPair = toRadians(360.0f/(float)basePairs);
    //
    //    int pos;
    //    pos = dataSet.percent ;
    //
    //    double tb = mTimeStamp;
    //    mTimeStamp = getElapsedSeconds();
    //
    //    pStart = Vec2f( 0,-circDiameter );
    //    pCenter = Vec2f( lerp(-circDiameter,circDiameter, (math<float>::sin(dataSet.percent*M_PI*2)+1.0f)/2.0f), 0 );
    //    //    pEnd = Vec2f( 0, lerp(0.0f,circDiameter, (math<float>::sin(dataSet.percent*M_PI*4)+1.0f)/2.0f) );
    //    pEnd = Vec2f( 0, circDiameter );
    //
    //    mShape.color(mColorStart);
    //    mShape.moveTo( pStart );
    //    int detail = 20;
    //    for(int i=0;i<detail;i++){
    //        percent = (i/(float)detail);
    //        p = PluginUtils::lerpLineDistortedCorrect(pStart,pCenter,Vec2f::zero(), percent, circDiameter );
    //        mShape.color( lerp(mColorStart,mColorEnd,percent/2.0) );
    //        mShape.lineTo( p );
    //    }
    //    for(int i=0;i<=detail;i++){
    //        percent = (i/(float)detail);
    //        p = PluginUtils::lerpLineDistortedCorrect(pCenter,pEnd,Vec2f::zero(), percent, circDiameter );
    //        mShape.color( lerp(mColorStart,mColorEnd,percent/2.0+.5) );
    //        mShape.lineTo( p );
    //    }
    //
    //    int dir = math<float>::fmod(dataSet.percent + .25f, 1.f) > .5 ? 1 : -1;
    //
    //    mShapeTemp = mShape;
    //    if(mShape.getNumContours()==1){
    //        Vec2f pWidth(.02*dir,0);
    //        Path2d path = mShape.getContour(0);
    //        for(int i=path.getNumPoints()-1;i>=0;i--){
    //            //            mShapeTemp.lineTo( path.getPoint(i)+pWidth);
    //        }
    //    }
    //
    //    mShape.moveTo( pEnd );
    //    mShape.moveTo( pStart );
    //
    //    char d;
    //    int basePairBit;
    //    int cnt = 0;
    //    int bitID;
    //    vector<Vec2f> stars;
    //    for(int i=0;i<basePairs;i++){
    //        d = dataSet.dataBitsString[i];
    //        pNorm.rotate( rotStepPair );
    //        p = pNorm;
    //        p.normalize();
    //        basePairBit = getBasePairBit(d);
    //        p *= lerp(circDiaShort,circDiaLong,basePairBit/3.0f);
    //
    //        bitID = dataSet.roi.startPosition + i;
    //        bool add = processElement( bitID , p, dir, d);
    //        //        if(add) stars.push_back( p );
    //        cnt++;
    //    }
    //
    //    //    if(mShape.getNumContours()>0){
    //    //        Path2d cont = mShape.getContour(mShape.getNumContours()-1);
    //    //        cont.removeSegment(cont.getNumSegments()-1);
    //    ////        mShape.getCurrentPoint()
    //    //    }
    //
    //    cleanupElements();
    //
    //    //    vector<Vec2f>::iterator it;
    //    //    for(it=stars.begin();it!=stars.end();++it){
    //    //        drawStarElement(&mShape, (*it).second );
    //    //    }
    //
    //    drawElements();
    //
    //
    //    MatrixAffine2f matr;
    //    matr.translate(Vec2f(.5,.5));
    //    matr.transformPoint( Vec2f(.5,.5) );
    //    matr.rotate(toRadians(mRotCounter));
    //    mShape.transform(matr);
    return mShape;
}


void BarsPlugin::drawBeam(Vec2f p, float dia){
    Vec2f pos;
    for(int i=0;i<=mBeam.size();i++){
        pos = mBeam[i%mBeam.size()]*dia + p;
        if(i==0) mShape.moveTo( pos );
        else mShape.lineTo(pos);
    }
}

void BarsPlugin::drawDescription( Vec2f pos, float len, string description, int descriptionPos ){
    int p = descriptionPos/2;
    if(p<description.size()){
        char c = description[p];
        int num = c & 0xff;
        int bitOffset = 0;
        if(descriptionPos%2==0) bitOffset = 4;
        for(int i=0;i<4;i++){
            bool l = ((num >> (i+bitOffset)) & 0x01) == 0;
            mShape.moveTo(pos+mDataLines[i]*len);
            if(l){
                mShape.lineTo(pos+mDataLines[i]*len/2.0);
            }else{
                mShape.lineTo(pos);
            }
        }
    }else{
        for(int i=0;i<4;i++){
            mShape.moveTo(pos);
            mShape.lineTo(pos+mDataLines[i]*len);
        }        
    }
}

// ------------------------------------------------------------------------------------------------------
