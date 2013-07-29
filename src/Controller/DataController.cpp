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
        d.length = toRadians( rnd.nextFloat(10, 50) );
        d.pos = rnd.nextFloat(0, 1);
        mDataCrawler.push_back(d);
//        timeline().apply( &mDataCrawler[mDataCrawler.size()-1].pos, rnd.nextFloat(0, 1), 10.0f, EaseOutSine() ).finishFn(std::bind( &DataController::resetCrawler , this ) );
//        float::Tween<float>* tweentween;
//        Tween<float>::Options tt;
        TweenRef<float> tweenRef = timeline().apply( &mDataCrawler[mDataCrawler.size()-1].pos, rnd.nextFloat(0, 1), rnd.nextFloat(10, 100), EaseOutSine() );
        tweenRef->setFinishFn( std::bind( &DataController::resetCrawler, this) );
        tweenRef->setPingPong( true );
        tweenRef->setLoop();
//        Tween<float> tweentween1 = ;
//        .finishFn( Say("Hallo") );
        
    }

}

void DataController::resetCrawler(){
    console() << "DataController::resetCrawler"<<std::endl;
}

void DataController::update(){
	
}

vector<DataCrawler>* DataController::getCrawler(){
    return &mDataCrawler;
}