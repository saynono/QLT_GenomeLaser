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
#include "DataToShapeConverter.h"

#include "ColouredShape2d.h"
#include "PluginController.h"
#include "DataSaver.h"



using namespace ci;
using namespace ci::app;
using namespace std;

class MainController{

public:
	
	void setup();
	void update();
    
    void toggleLaser();
    void enableLaser();
    void disableLaser();
    bool isLaserEnabled();
    
    PluginController* getPluginController();
    DataController* getDataController();
    DataManager* getDataManager();
    DataSaver* getDataSaver();
    void  gatherApplicationData( map<string, string>* data );

	void createShapes();

    ciilda::Frame* getFrameRef();
    const ciilda::Frame& getFrame() const;
    const ColouredShape2d& getShape() const;
    
    boost::signals2::signal<void(void)> sOnEnableLaser;
    boost::signals2::signal<void(void)> sOnDisableLaser;

private:
    
    
    void                createTempDataBits();
    
    
    DataManager                 mDataManager;
    DataToShapeConverter        mShapeConverter;
    DataController              mDataController;
    PluginController            mPluginController;
    DataSaver                   mDataSaver;
    
    
    
    ColouredShape2d             mCurrentShape;
    ciilda::Frame               mIldaFrame;
    
    float                       mAmountCrawlers;
    
    bool                        bIsLaserEnabled;
    
};



