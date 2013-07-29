//
//  LaserPreview3D.h
//  QLT_GenomeLaser
//
//  Created by say nono on 09.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "cinder/app/AppBasic.h"
#include "cinder/Camera.h"
#include "CinderIldaFrame.h"
#include "cinder/gl/Fbo.h"
#include "cinder/Quaternion.h"

#include "POV.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class LaserPreview3D{

public:
    
    
    struct {
        bool showFrame;
        bool showDotsOnGauze;
        bool showLinesOnGauze;
        bool showRays;
        bool showFans;
        float fansIntensity;
    } paramsView;

	
	void setup(int w, int h);
    void calculateDotsOnGauze( ciilda::Frame* frame);
	void update();
	void draw();
    
    void setCameraPosition(Vec3f vec);
    void setTargetPosition(Vec3f vec);
    Vec3f getCameraPosition();
    Vec3f getTargetPosition();
    
    void resetView();
    
    ci::gl::Fbo* getTexture();
    
    int getLaserAngle();
    void setLaserAngle(int a);
    
private:
    
    struct GauzeDots{
        Vec3f       vec;
        ColorAf     clr;
    };
    
    void                        drawLaserDotsOnGauze();
    void                        drawLaserLinesOnGauze(float alpha);
    void                        drawLaserRays(float alpha);
    void                        drawLaserFansTest(float alpha);
    void                        drawLaserFans(float alpha);
    void                        drawLaserFansTests();

    
    ci::CameraPersp				mCamera;
    ci::gl::Fbo                 mPreview3DFbo;
    
    POV                         mPov;


    Vec3f                       mCameraPosition;
	Vec3f                       mTargetPosition;
    Vec3f                       mUp;

    Matrix44f                   mTempRotation;
    Quatf                       mQuat;
    int                         mLaserAngle;
    vector<GauzeDots>           mGauzeDots;
	
};



