//
//  DataController.h
//  QLT_GenomeLaser
//
//  Created by say nono on 22.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "cinder/app/AppBasic.h"
#include "cinder/Timeline.h"
#include "cinder/Rand.h"

#include "DataManager.h"
#include "DataCrawler.h"
#include "GenomeData.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class DataController{
    
    
    struct Say { // Simple functor to print stuff to the console
        Say( std::string message ) : mMessage( message ) {}
        void operator()(){ app::console() << mMessage << std::endl; }
            
            std::string mMessage;
            };
    
public:
	
	void setup(DataManager* dm);
	void update();
	vector<DataCrawler>* getCrawler();
    void resetCrawler();

private:
    
    DataManager*            mDataManager;
    
    vector<DataCrawler>     mDataCrawler;
	
};



