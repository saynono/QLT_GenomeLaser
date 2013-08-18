//
//  PluginUtils.h
//  QLT_GenomeLaser
//
//  Created by say nono on 14.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once

#include "cinder/app/AppBasic.h"
#include "cinder/CinderMath.h"
#include "cinder/Utilities.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class PluginUtils{

public:

    static Vec2f lerpLineDistortedSimple( Vec2f p, float diameter ){
        Vec2f res = p;
        res /= diameter;
        res *= math<float>::sin(res.length()*M_PI_2);
        return res;
    }
    
    static Vec2f lerpLineDistorted( Vec2f p1, Vec2f p2, Vec2f center, float val ){
        p1 -= center;
        p2 -= center;
        Vec2f res = lerp(p1,p2, val );
        float len = lerp(p1.length(),p2.length(), val );
        res = res.normalized() * len + center;
        return res;
        
//        float p1Len = p1.length()*2;
//        float p2Len = p2.length()*2;
//        
//        float angleZ1 = (float) asin(p1Len);
//        float angleZ2 = (float) asin(p2Len);
//        
//        float angleZRes = lerp(angleZ1,angleZ2,val);
//        float len = sin( angleZRes * M_PI ) / 2.0;
//        
//        Vec2f res = lerp(p1,p2, val );
//        res = res.normalized() * len + center;
//        return res;
    }
    
    static Vec2f lerpLineDistortedCorrect( Vec2f p1, Vec2f p2, Vec2f center, float val , float diameter){
        float p1Len = p1.length()/diameter;
        float p2Len = p2.length()/diameter;
        
        float angleXZ1 = (float) asin(p1Len);
        float angleXZ2 = (float) asin(p2Len);
        
        float angleXY1 = (float) atan2(-p1.x,p1.y);
        float angleXY2 = (float) atan2(-p2.x,p2.y);
        
        Vec3f p3d1 = Vec3f(0,0,-1);
        p3d1.rotateY( angleXZ1 );
        p3d1.rotateZ( angleXY1 );
        
        Vec3f p3d2 = Vec3f(0,0,-1);
        p3d2.rotateY( angleXZ2 );
        p3d2.rotateZ( angleXY2 );
        
        Vec3f pRes = lerp(p3d1,p3d2,val);
        pRes.normalize();
        pRes.rotateZ( M_PI_2 );
        return pRes.xy()*diameter;
        
    }

//    static Vec2f lerpLineDistortedCorrectSimple( Vec2f p1, Vec2f p2, Vec2f center, float val ){
//        float p1Len = p1.length()*2;
//        float p2Len = p2.length()*2;
//        
//        float angleXZ1 = (float) asin(p1Len);
//        float angleXZ2 = (float) asin(p2Len);
//        
//        float angleXY1 = (float) atan2(-p1.x,p1.y);
//        float angleXY2 = (float) atan2(-p2.x,p2.y);
//        
//        Vec3f p3d1 = Vec3f(0,0,-1);
//        p3d1.rotateY( angleXZ1 );
//        p3d1.rotateZ( angleXY1 );
//        
//        Vec3f p3d2 = Vec3f(0,0,-1);
//        p3d2.rotateY( angleXZ2 );
//        p3d2.rotateZ( angleXY2 );
//        
//        Vec2f p2dRes = lerp(p1,p2,val);
//        Vec3f pRes = lerp(p1,p2,val);
//        pRes.normalize();
//        pRes.rotateZ( M_PI_2 );
//        return pRes.xy()/2.0;
//        
//    }

    
    static Vec2f harshMaxDiameter( Vec2f p1, Vec2f center, float maxDia ){
        Vec2f res = p1 - center;
        float dia = min(res.length(),maxDia);
        res = res.normalized() * dia + center;
        return res;
    }

    static Vec2f softMaxDiameter( Vec2f p1, Vec2f center, float maxDia ){
        Vec2f res = p1 - center;
        float dia = min(res.length(),maxDia);
        res = res.normalized() * dia + center;
        return res;
    }

};