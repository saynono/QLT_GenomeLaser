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
    
    mCircDiameter = .4;
    mLineHeight = .3;
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
        timeline().apply( &mRotCounter, val, 2.7f, EaseInOutQuad() );
        recreateElements(dataSet);
    }
    
    mShape.clear();
    
    Vec2f p,pStart,pEnd,pPrev,pCenter;
    Vec2f pNorm(0,.5);
    Vec2f pOffset(.5,.5);
    float percent = 0;
    
    int basePairs = dataSet.roi.basePairsCount;
    
    float circDiameter = mCircDiameter;
    float lineHeight2 = mLineHeight/2.0;
    float circDiaLong = .4;
    float circDiaShort = .1;
    float rotStepPair = toRadians(360.0f/(float)basePairs);
                        
    int pos;
    pos = dataSet.percent ;
    
    double tb = mTimeStamp;
    mTimeStamp = getElapsedSeconds();
    
    pStart = Vec2f( 0,-circDiameter );
    pCenter = Vec2f( lerp(-circDiameter,circDiameter, (math<float>::sin(dataSet.percent*M_PI*2)+1.0f)/2.0f), 0 );
//    pEnd = Vec2f( 0, lerp(0.0f,circDiameter, (math<float>::sin(dataSet.percent*M_PI*4)+1.0f)/2.0f) );
    pEnd = Vec2f( 0, circDiameter );
    
    mShape.color(mColorStart);
    mShape.moveTo( pStart );    
    int detail = 20;
    for(int i=0;i<detail;i++){
        percent = (i/(float)detail);
        p = PluginUtils::lerpLineDistortedCorrect(pStart,pCenter,Vec2f::zero(), percent, circDiameter );
        mShape.color( lerp(mColorStart,mColorEnd,percent/2.0) );
        mShape.lineTo( p );
    }
    for(int i=0;i<=detail;i++){
        percent = (i/(float)detail);
        p = PluginUtils::lerpLineDistortedCorrect(pCenter,pEnd,Vec2f::zero(), percent, circDiameter );
        mShape.color( lerp(mColorStart,mColorEnd,percent/2.0+.5) );
        mShape.lineTo( p );
    }
    
    int dir = math<float>::fmod(dataSet.percent + .25f, 1.f) > .5 ? 1 : -1;

    mShapeTemp = mShape;
    if(mShape.getNumContours()==1){
        Vec2f pWidth(.02*dir,0);
        Path2d path = mShape.getContour(0);
        for(int i=path.getNumPoints()-1;i>=0;i--){
            mShapeTemp.lineTo( path.getPoint(i)+pWidth);
        }
    }
    
    mShape.moveTo( pEnd );
    mShape.moveTo( pStart );
    
    char d;
    int basePairBit;
    int cnt = 0;
    int bitID;
    vector<Vec2f> stars;
    for(int i=0;i<basePairs;i++){
        d = dataSet.dataBitsString[i];
        pNorm.rotate( rotStepPair );
        p = pNorm;
        p.normalize();
        basePairBit = getBasePairBit(d);
        p *= lerp(circDiaShort,circDiaLong,basePairBit/3.0f);
        
        bitID = dataSet.roi.startPosition + i;
        bool add = processElement( bitID , p, dir);
//        if(add) stars.push_back( p );
        cnt++;
    }
    
//    if(mShape.getNumContours()>0){
//        Path2d cont = mShape.getContour(mShape.getNumContours()-1);
//        cont.removeSegment(cont.getNumSegments()-1);
////        mShape.getCurrentPoint()
//    }
    
    cleanupElements();
    
//    vector<Vec2f>::iterator it;
//    for(it=stars.begin();it!=stars.end();++it){
//        drawStarElement(&mShape, (*it).second );
//    }
    
    drawElements();
    
    
    MatrixAffine2f matr;
    matr.translate(Vec2f(.5,.5));
    matr.transformPoint( Vec2f(.5,.5) );
    matr.rotate(toRadians(mRotCounter));
    mShape.transform(matr);
    return mShape;
    
}


// ------------------------------------------------------------------------------------------------------


bool ScannerPlugin::processElement(int elementId, Vec2f vec, int dir){
//        console() << i << " => " << p.x << "  " << p.y << "     rotStepPair : "  << toDegrees(rotStepPair) << std::endl;
    bool add = false;
    if( dir == 1 && mShapeTemp.contains(vec)){
        add = true;
    }else if( dir == -1 && !mShapeTemp.contains(vec)){
        add = true;
    }
    
    add = mShapeTemp.contains(vec);
    
    
    if(add){
        if( mStarElements.size() < 10 && mStarElements.count(elementId) == 0 ){
            StarElement element;
            element.elementId = elementId;
            element.liveTime = 1;
            element.position = vec;
            element.isActive = true;
            element.lastDirPos = dir;
//            timeline().apply( &mAnimationColor, ColorA( 1.,1.,1.,0. ), 1.f, EaseOutSine() )
//            .finishFn( std::bind( &FlightDateDestination::reachedAnimationEnd , this ) );            
            mStarElements[elementId] = element;
            timeline().apply( &mStarElements[elementId].liveTime, 0.0f, 2.7f, EaseOutQuad() );            
        }else if(mStarElements[elementId].lastDirPos != dir){
            timeline().removeTarget(&mStarElements[elementId].liveTime);
            mStarElements[elementId].liveTime = 1.0f;
            mStarElements[elementId].lastDirPos = dir;
            timeline().apply( &mStarElements[elementId].liveTime, 0.0f, 2.7f, EaseOutQuad() );
        }
    }
    return add;
}

void  ScannerPlugin::cleanupElements(){
    vector<int> removeItemIds;
    int elId;
    map<int,StarElement> ::iterator it;
    for( it=mStarElements.begin();it!=mStarElements.end();++it){
//        if((*it).first != (*it).second.elementId){
//            console() << " SOMETHING FISHY HERE! " << (*it).second.elementId << std::endl;
//        }
        if((*it).second.liveTime == 0 || (*it).first != (*it).second.elementId){
            elId = (*it).first;
            removeItemIds.push_back(elId);
        }
    }
    if( removeItemIds.size() == 0) return;
    vector<int>::iterator itDel;
    for(itDel=removeItemIds.begin();itDel!=removeItemIds.end();++itDel){
        mStarElements.erase( (*itDel) );
    }
}

void ScannerPlugin::recreateElements( const GenomeData::BasePairDataSet& dataSet ){
//    
//    return;
//    mStarElements.clear();
//    
//    int l = dataSet.roi.basePairsCount;
//    for(int i=0;i<l;i++){
//        int elementId = dataSet.roi.startPosition + i;
//        StarElement element;
//        element.elementId = elementId;
//        element.liveTime = 1; 
////        element.position = vec;
//        element.isActive = true;
////        element.lastDirPos = dir;
//        //            timeline().apply( &mAnimationColor, ColorA( 1.,1.,1.,0. ), 1.f, EaseOutSine() )
//        //            .finishFn( std::bind( &FlightDateDestination::reachedAnimationEnd , this ) );
////        mStarElements[elementId] = element;
//    }
}

void ScannerPlugin::drawElements(){
    int cnt = 0;
//    console()  << std::endl;
    map<int,StarElement> ::iterator itDraw;
    for( itDraw=mStarElements.begin();itDraw!=mStarElements.end();++itDraw){
        if((*itDraw).second.liveTime > 0){
            if((*itDraw).second.position.length()==0) console() << "  " << (*itDraw).first << " ? " << (*itDraw).second.elementId << "( "<< (*itDraw).second.position.x << "  " << (*itDraw).second.position.y << ") " <<std::endl;
            drawStarElement( &mShape, (*itDraw).second );
            cnt++;
        }
    }
//    console() << " DRAW ELEMENTS TOTAL : " << cnt << std::endl;
    
}


// ------------------------------------------------------------------------------------------------------


void ScannerPlugin::drawStarElement( ColouredShape2d* s, const StarElement& element ){
    
    //    ColorAf clr( 1,1,1,element.liveTime );
    Vec2f center = element.position;
//    console() << "DRAW STAR " << element.elementId << "     percent : " << element.liveTime << std::endl;
    ColorAf clr( element.liveTime,element.liveTime,element.liveTime,element.liveTime );
    s->color( clr );
    s->moveTo( center );
    s->lineTo( center );
//    float size2 = .05f * element.liveTime;
//    Vec2f p;
//    p.x = -size2;
//    p.y = -size2;
//    s->moveTo( center + p );
//    s->lineTo( center + p );
//    p.x = size2;
//    s->lineTo( center + p );
//    p.y = size2;
//    s->lineTo( center + p );
//    p.x = -size2;
//    s->lineTo( center + p );
//    p.y = -size2;
//    s->lineTo( center + p );
//    s->moveTo( center + p );
}




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


// ------------------------------------------------------------------------------------------------------


int ScannerPlugin::getBasePairBit(char d){
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
    return basePairBit;
}

