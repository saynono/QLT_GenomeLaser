/*
 *  ParticlePlugin.cpp
 *
 *  Copyright (c) 2013, Neil Mendoza, http://www.neilmendoza.com
 *  All rights reserved. 
 *  
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions are met: 
 *  
 *  * Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer. 
 *  * Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 *  * Neither the name of Neil Mendoza nor the names of its contributors may be used 
 *    to endorse or promote products derived from this software without 
 *    specific prior written permission. 
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE 
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 *  POSSIBILITY OF SUCH DAMAGE. 
 *
 */
#include "ParticlePlugin.h"

ParticlePlugin::ParticlePlugin(): BasePlugin( "ParticlePlugin" ){
    
}

void ParticlePlugin::setup(){
    
    /*mStartAngle = Rand::randFloat(-M_PI,M_PI);
    mSpeed = Rand::randFloat(-M_PI,M_PI);
    mLineHeight = Rand::randFloat(0.0,.3);
    mLinePosition = Rand::randFloat(mLineHeight/2.0,1-mLineHeight/2.0);
    //    mLinePosition = 1-mLineHeight/2.0;
    mLength = toRadians(Rand::randFloat(0.0,1.0)*180);
    
    mPairRadLength = toRadians( Rand::randFloat(0.1,5.0) );
    
    mClr1 = ColorAf(Rand::randFloat(.01, .7),.7,Rand::randFloat(.0, .9),1);
    mClr2 = ColorAf(Rand::randFloat(.3, .9),Rand::randFloat(.3, .9),Rand::randFloat(.3, .9),1);
    
    mOSCMap.insert( make_pair( "SPEED", new OSCElement( this, &mSpeed, OSCElement::FLOAT, 1, 10  )) );
    mOSCMap.insert( make_pair( "LINE_HEIGHT", new OSCElement( this, &mLineHeight, OSCElement::FLOAT, 0, .1 )) );
    mOSCMap.insert( make_pair( "LINE_POSITION", new OSCElement( this, &mLinePosition, OSCElement::FLOAT, 0, 1  )) );
    mOSCMap.insert( make_pair( "LENGTH", new OSCElement( this, &mLength, OSCElement::FLOAT, 0, .4 )) );
    
    
    console() << " SPEED  element->pointer : " << &mSpeed << std::endl;
    console() << " LINE_HEIGHT  element->pointer : " << &mLineHeight << std::endl;
    console() << " LINE_POSITION  element->pointer : " << &mLinePosition << std::endl;
    console() << " LENGTH  element->pointer : " << &mLength << std::endl;
    */
}

void ParticlePlugin::dispose(){
}


//------------------------------------------------------------------------------------------------------

const map<string, OSCElement*>& ParticlePlugin::getOSCMapping() {
    return mOSCMap;
}

//------------------------------------------------------------------------------------------------------

void ParticlePlugin::processOSCMessage( const osc::Message& message ) {
    /*for (int i = 0; i < message.getNumArgs(); i++) {
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
    */
}


//------------------------------------------------------------------------------------------------------

const ColouredShape2d& ParticlePlugin::getShape( const GenomeData::BasePairDataSet& dataSet ){
   
    particle.zeroForce();
    
    switch(dataSet.dataBitsString[0])
    {
        case 'A':
            particle.addForce(Vec2f(-2, 0));
            break;
        case 'C':
            particle.addForce(Vec2f(2, 0));
            break;
        case 'G':
            particle.addForce(Vec2f(0, -2));
            break;
        case 'T':
            particle.addForce(Vec2f(0, 2));
            break;
    }
    
    particle.update();
    
    trail.push_back(particle.getPos());
    while (trail.size() > 200) trail.pop_front();
    
    mShape.clear();
    
    if (trail.size() > 1)
    {
        mShape.moveTo(trail[0]);
        for (unsigned i = 1; i < trail.size(); ++i)
        {
            mShape.color(hsvToRGB(Vec3f(i / (float)trail.size(), 1.f, 1.f)));
            mShape.lineTo(trail[i]);
        }
    }
    return mShape;
}

/*
void ParticlePlugin::convertBitChainToShape(const char* data, int len, float lineHeight, float circStartAngle, float pairRadLength, float circDiameter){
    
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
    
    
    //    console() << "CALC " << dataBitsString << std::endl;
    
}

//------------------------------------------------------------------------------------------------------

void ParticlePlugin::drawLine(ColouredShape2d* s, Vec2f p1, Vec2f p2, float percent){
    
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
*/