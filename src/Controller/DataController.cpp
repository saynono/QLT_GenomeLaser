//
//  DataController.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 22.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "DataController.h"

	
void DataController::setup(DataManager* dm, int amount){
	mDataManager = dm;
    
    GenomeData::ChromosomeDataSet cds = mDataManager->getChromosomeDataSet();
    
    for(int i=0;i<amount;i++){
        addCrawler(&cds);
//        timeline().apply( &mDataCrawler[mDataCrawler.size()-1].pos, rnd.nextFloat(0, 1), 10.0f, EaseOutSine() ).finishFn(std::bind( &DataController::resetCrawler , this ) );
//        float::Tween<float>* tweentween;
//        Tween<float>::Options tt;
        
//        TweenRef<int> tweenRef = timeline().apply( &mDataCrawler[mDataCrawler.size()-1].pos, Rand::randInt(0, cds.basePairsCount-1), Rand::randFloat(10, 100), EaseOutSine() );
//        tweenRef->setFinishFn( std::bind( &DataController::resetCrawler, this) );
//        tweenRef->setPingPong( true );
//        tweenRef->setLoop();
        
//        Tween<float> tweentween1 = ;
//        .finishFn( Say("Hallo") );
        
    }
    
    mTick = 0;
    mTickFrequency = 30;
    
    reset();

}

void DataController::addCrawler(GenomeData::ChromosomeDataSet* cds){
    DataCrawler d;
//    d.density = Rand::randFloat(150, 500);
    d.length = Rand::randInt(30, 100);
    d.pos = 0;
    d.speed = Rand::randInt(1, 100);
    d.crawlerID = mDataCrawler.size();
    mDataCrawler.push_back(d);
}

// ------------------------------------------------------------------------------------------------------------------


void DataController::reset(){
    
    const vector<GenomeData::ROIDataSet> roiMap = mDataManager->getRoiMap();
    mRoiMapVisited.clear();
    
    vector<GenomeData::ROIDataSet>::const_iterator it;
    for(it=roiMap.begin();it!=roiMap.end();++it){
        int roiID = (*it).roiId;
        mRoiMapVisited[roiID] = roiID;
    }
    
    vector<DataCrawler>::iterator it2;
    for(it2=mDataCrawler.begin();it2!=mDataCrawler.end();++it2){
        resetCrawler( &(*it2) );
    }
    
}

void DataController::resetCrawler(DataCrawler* crawler){
    int roiId = mRoiMapVisited[Rand::randInt(0,mRoiMapVisited.size()-1)];
    crawler->roiDataSetID = roiId;
    crawler->roiDataSet = mDataManager->getRoiByID(roiId);
    crawler->pos = crawler->roiDataSet.startPosition;
    crawler->lastUpdate = getElapsedSeconds();
    crawler->length = Rand::randInt(30, 100);
    crawler->speed = Rand::randInt(1,10);
    //TODO: remove
//    crawler->speed = 1;
//    console() << "RESET : crawler->roiDataSetID " << crawler->roiDataSetID << " >>>> start: " << crawler->roiDataSet.startPosition << "->" << crawler->roiDataSet.endPosition << "      len: " << crawler->roiDataSet.basePairsCount << std::endl;
}

// ------------------------------------------------------------------------------------------------------------------

void DataController::update(){
    
    int tick = (getElapsedSeconds()*mTickFrequency);
    if(tick != mTick){
//        console() << "TICK : " << tick << "     diff: " << (tick-mTick) << std::endl;
        mTick = tick;
    }
    
	vector<DataCrawler>::iterator it;
    for(it=mDataCrawler.begin();it!=mDataCrawler.end();++it){
        updateDataCrawler( &(*it) );
    }
}

void DataController::updateDataCrawler(DataCrawler* dataCrawler){
    
    if( dataCrawler->length == 0 ){
        // TODO: uncomment
        resetCrawler( dataCrawler );
    }
    mDataManager->updateDataCrawler( dataCrawler );    
}


// ------------------------------------------------------------------------------------------------------------------

DataManager* DataController::getDataManager(){
    return mDataManager;
}

vector<DataCrawler>* DataController::getCrawler(){
    return &mDataCrawler;
}