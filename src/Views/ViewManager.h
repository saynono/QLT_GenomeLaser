//
//  ViewManager.h
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "cinder/app/AppBasic.h"

#include "MainController.h"
#include "LaserPreview3D.h"
#include "CircularDataLayer.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class ViewManager{

public:
	
	void setup( MainController* mc );
	void update();
	void draw();
	
    LaserPreview3D* getLaserPreview3D();
    CircularDataLayer* getCircularDataLayer();
    
private:
    
    MainController*     mMainController;
    LaserPreview3D      mLaserPreview3D;
    CircularDataLayer   mCircDataLayer;
    
};



