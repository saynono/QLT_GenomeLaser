//
//  MainController.h
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "cinder/app/AppBasic.h"


#include "CinderIldaFrame.h"
#include "DataManager.h"
#include "DataController.h"
#include "DataConverter.h"
#include "DataToShapeConverter.h"

#include "ColouredShape2d.h"
#include "PluginController.h"



using namespace ci;
using namespace ci::app;
using namespace std;

class MainController{

public:
	
	void setup();
	void update();
    
    DataController* getDataController();
    DataManager* getDataManager();
    
	void createShapes();

    ciilda::Frame* getFrameRef();
    const ciilda::Frame& getFrame() const;
    const ColouredShape2d& getShape() const;

private:
    
    
    void                createTempDataBits();
    
    
    DataManager                 mDataManager;
    DataToShapeConverter        mShapeConverter;
    DataConverter               mDataConverter;
    DataController              mDataController;
    PluginController            mPluginController;
    
    
    
    ColouredShape2d             mCurrentShape;
    ciilda::Frame               mIldaFrame;
    
    float                       mAmountCrawlers;
    
};



