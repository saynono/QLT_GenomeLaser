//
//  PluginUtils.h
//  QLT_GenomeLaser
//
//  Created by say nono on 14.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once

#include "cinder/app/AppBasic.h"
#include "cinder/Utilities.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class PluginUtils{

public:
    
    static Vec2f lerpLineDistorted( Vec2f p1, Vec2f p2, Vec2f center, float val ){
        p1 -= center;
        p2 -= center;
        Vec2f res = lerp(p1,p2, val );
        float len = lerp(p1.length(),p2.length(), val );
        res = res.normalized() * len + center;
        return res;
    }

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