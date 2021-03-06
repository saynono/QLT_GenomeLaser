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

const Vec2f ParticlePlugin::CENTRE = Vec2f(.5, .5);

ParticlePlugin::ParticlePlugin(): BasePlugin( "ParticlePlugin" ), maxDistance(0.2)
{
}

void ParticlePlugin::setup()
{
    mOSCMap.insert( make_pair( "MAX_DISTANCE", new OSCElement( "MAX_DISTANCE", this, &maxDistance, OSCElement::FLOAT, 0.2, 0.5  )) );
    
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
    //mOSCMap.insert( make_pair( "CENTRE_ATTRACT", new OSCElement( this, &mSpeed, OSCElement::FLOAT, 1, 10  )) );
}

void ParticlePlugin::dispose(){
}


//------------------------------------------------------------------------------------------------------

const map<string, OSCElement*>& ParticlePlugin::getOSCMapping() {
    return mOSCMap;
}

//------------------------------------------------------------------------------------------------------

const ColouredShape2d& ParticlePlugin::getShape( const GenomeData::BasePairDataSet& dataSet ){
   
    particle.zeroForce();
    
    Vec2f pCenter(.5,.5);
    
    switch(dataSet.dataBitsString[dataSet.basePairsCount * dataSet.percent])
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
    
    // keep them in the centre
    Vec2f dirToCenter = CENTRE - particle.getPos();
    float distToCenter = dirToCenter.length();
    
    //static const float maxDistance = 0.2f;
    
    if( distToCenter > maxDistance )
    {
        dirToCenter.normalize();
        float pullStrength = 10.f;
        Vec2f force = dirToCenter * ( ( distToCenter - maxDistance ) * pullStrength );
        //cout << force << endl;
        particle.addForce(force);
    }
    
    particle.update();
    
    trail.push_back(particle.getPos());
    while (trail.size() > 200) trail.pop_front();
    
    mShape.clear();
    
    if (trail.size() > 1)
    {
        mShape.moveTo( PluginUtils::harshMaxDiameter(trail[0],pCenter,.5f) );
        for (unsigned i = 1; i < trail.size(); ++i)
        {
            mShape.color(hsvToRGB(Vec3f(i / ((float)trail.size()*10), 1.f, 1.f)));
            mShape.lineTo( PluginUtils::harshMaxDiameter(trail[i],pCenter,.5f) );
        }
    }
    return mShape;
}
