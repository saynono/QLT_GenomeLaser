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
    mDataManager->sOnDataStructureChange.connect(  boost::bind( &DataController::onDataStructureChange, this ) );
    
    GenomeData::ChromosomeDataSet cds = mDataManager->getChromosomeDataSet();
    
    for(int i=0;i<amount;i++){
        addCrawler(&cds);
    }
    
    reset();

}

void DataController::addCrawler(GenomeData::ChromosomeDataSet* cds){
    DataCrawler d;
//    d.density = Rand::randFloat(150, 500);
    d.length = Rand::randInt(30, 100);
    d.pos = 0;
    d.speed = 0;//Rand::randInt(1, 100);
    d.crawlerID = mDataCrawler.size();
    // only set the first one true
    d.isActive = mDataCrawler.size() == 0;
    mDataCrawler.push_back(d);
}

// ------------------------------------------------------------------------------------------------------------------


void DataController::reset(){
    
    console() << "DataController::reset()" << std::endl;
    
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
    crawler->length = Rand::randInt(60, 100);
    crawler->speed = Rand::randInt(1,10);
    // TODO: remove
    crawler->speed = 2;    
}

// ------------------------------------------------------------------------------------------------------------------

void DataController::update(){
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

void DataController::toggleCrawlerActivity(int id){
    if(id > mDataCrawler.size() || id < 0) return;
    mDataCrawler.at(id).isActive = !mDataCrawler.at(id).isActive;
}

void DataController::onDataStructureChange(){
    console() << "DataController::onDataStructureChange " << std::endl;;
    reset();
}



// ------------------------------------------------------------------------------------------------------------------

