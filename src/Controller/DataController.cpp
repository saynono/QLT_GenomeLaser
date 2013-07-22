//
//  DataController.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 22.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "DataController.h"

	
void DataController::setup(DataManager* dm){
	mDataManager = dm;
    
    Rand rnd;
    int amount = 5;
    
    for(int i=0;i<amount;i++){
        DataCrawler d;
        d.density = rnd.nextFloat(150, 500);
        d.length = rnd.nextFloat(10, 50);
        d.pos = rnd.nextFloat(0, 1);
        mDataCrawler.push_back(d);
        timeline().apply( &mDataCrawler[mDataCrawler.size()-1].pos, rnd.nextFloat(0, 1), 100.0f, EaseOutSine() );
        
    }

}

void DataController::update(){
	
}

vector<DataCrawler>* DataController::getCrawler(){
    return &mDataCrawler;
}