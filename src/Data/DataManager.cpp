//
//  DataManager.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 11.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//



#include "DataManager.h"


void DataManager::setup(){
    
//    fs::path path1 = getAssetPath("data/genome/CM000663.1| Homo sapiens chromoso _ part.fasta");
//    fs::path path2 = getAssetPath("data/genome/CCDS_exons.current.txt");
    
    loadChromosome( 4 );
}


// ------------------------------------------------------------------------------------------------------------------------

void DataManager::loadChromosome(int chromsomeID){
    
    fs::path pathData = getAssetPath("data/new/exon.y.bin");
    fs::path pathMap = getAssetPath("data/new/exon.y.locations");
    
    loadDataSet(pathData,pathMap);

}

void DataManager::loadDataSet(cinder::fs::path pathData, cinder::fs::path pathMap){


    Buffer b = Buffer( loadFile( pathData ) );
    size_t size = b.getDataSize();
    mDataBuffer = b;

    mCurrentDataSet.basePairsCount = size;
    mCurrentDataSet.chromosomeDescription = "Dummy Chromosome 18";
    mCurrentDataSet.chromosomeID = 18;

    Buffer bmap = Buffer( loadFile( pathMap ) );
    generateChromosomeMap( &bmap );
    
}

// ------------------------------------------------------------------------------------------------------------------------

void DataManager::generateChromosomeMap(Buffer* b){
    
    size_t size = b->getDataSize();
    char* datas = (char*)b->getData();
    
    int cnt = 0;
    int lineStart = 0;
//    char d;
//    string line;
    while(cnt<size){
//        d = *(datas+i);
        if(*(datas+cnt) == '\n'){
            addRoi( (datas+lineStart), cnt-lineStart );
            lineStart = cnt+1;
        }
        ++cnt;
    }
    
//  ROIDataSet
    
    console() << "DataManager::generateChromosomeMap : done"<< std::endl;
    
}

void DataManager::addRoi(char* datas, int len){
    string line;
    for(int i=0;i<len;++i){
        line += *(datas+i);
    }
    vector<string> tokens;
    boost::split(tokens,line,boost::is_any_of(","));

    int pairs = stoi(tokens[1]);
    int start = stoi(tokens[0]);
    int end = start+pairs;
    
    GenomeData::ROIDataSet roi;
    roi.chromosomeData = mCurrentDataSet;
    roi.basePairsCount = pairs;
    roi.startPosition = start;
    roi.endPosition = end;
    roi.roiId = mRoiMap.size();
    roi.roiDescription = "ROI Element ID_" + toString(roi.roiId);
    mRoiMap.push_back(roi);
//    mRoiIdMap[roi.roiId] = roi;
    
}

// ------------------------------------------------------------------------------------------------------------------------

GenomeData::ChromosomeDataSet DataManager::getChromosomeDataSet(){
    return mCurrentDataSet;
}

const vector<GenomeData::ROIDataSet>& DataManager::getRoiMap(){
    return mRoiMap;
}

GenomeData::ROIDataSet DataManager::getRoiByID(int roiID){
    return mRoiMap[roiID];
}

Buffer* DataManager::getDataBuffer(){
    return &mDataBuffer;
}


// ------------------------------------------------------------------------------------------------------------------------


void DataManager::updateDataCrawler( DataCrawler* dataCrawler ){
    
    if(dataCrawler->length == 0) return;
    
    double time = getElapsedSeconds();
    double diff = time - dataCrawler->lastUpdate;

    int pos = dataCrawler->roiDataSet.startPosition + (diff * (float)dataCrawler->speed);
    dataCrawler->pos = pos;
    dataCrawler->length = max(0, min(dataCrawler->length, dataCrawler->roiDataSet.endPosition-pos) );
    int len = dataCrawler->length;
    
//    console() << dataCrawler->crawlerID << " >> " << dataCrawler->pos << " : " << dataCrawler->roiDataSet.endPosition << "      len: " << dataCrawler->roiDataSet.basePairsCount << std::endl;
    
//    if( dataCrawler->roiDataSet.endPosition-pos < 0 ){
//        console() << " CRAWLER REQUESTS NEW ROI! -> " << dataCrawler->crawlerID << "      pointer: " << dataCrawler << std::endl;
//    }
    
    char* datas = (char*)mDataBuffer.getData();
    
    int start = pos;
    int end = start+len;
    char d;
    int cnt = 0;
//    int dataCharPos = 0;
//    int dataBitPos = 0;
    string dataString = "";
    
    for(int i=start;i<end;i++){
        
        d = *(datas+i);
        
        dataString += d;
//        dataCharPos = (int)(cnt / 4);
//        dataBitPos = ((cnt%4)) * 2;
        
        // seems to be the fastest way to do it like this according to:
        // http://stackoverflow.com/questions/6860525/c-what-is-faster-lookup-in-hashmap-or-switch-statement
        //
        switch(d){
            case 'A':
//                rawData[dataCharPos] |= 0 << dataBitPos;
//                dataString += "A";
                break;
            case 'C':
//                rawData[dataCharPos] |= 1 << dataBitPos;
//                dataString += "C";
                break;
            case 'G':
//                rawData[dataCharPos] |= 2 << dataBitPos;
//                dataString += "G";
                break;
            case 'T':
//                dataString += "T";
//                rawData[dataCharPos] |= 3 << dataBitPos;
                break;
                
        }
        cnt++;
    }
//    dataCrawler->dataSet.dataBits = rawData;
    dataCrawler->dataSet.dataBitsString = dataString;
    dataCrawler->dataSet.startPosition = pos;
    dataCrawler->dataSet.basePairsCount = len;
    dataCrawler->dataSet.chromosomeData = mCurrentDataSet;
    
}

/*
void DataManager::createBasePairDataSet(int pos, int len, GenomeData::BasePairDataSet* dataSet){
    // Be sure that all the data is set to zero!
    char rawData[(int)ceil(len/4)];
    memset(rawData, 0, len/4);
    dataSet->dataBits = rawData;
    
    char* datas = (char*)mDataBuffer.getData();
    
    int start = pos;
    int end = start+len;
    char d;
    int cnt = 0;
    int dataCharPos = 0;
    int dataBitPos = 0;
    
    console() << "start : " << start << "   end: "<< end << std::endl;
    
    for(int i=start;i<end;i++){
        
        d = *(datas+i);
        dataCharPos = (int)(cnt / 4);
        dataBitPos = ((cnt%4)) * 2;
        
        // seems to be the fastest way to do it like this according to:
        // http://stackoverflow.com/questions/6860525/c-what-is-faster-lookup-in-hashmap-or-switch-statement
        //
        switch(d){
            case 'A':
                dataSet->dataBits[dataCharPos] |= 0 << dataBitPos;
                break;
            case 'C':
                dataSet->dataBits[dataCharPos] |= 1 << dataBitPos;
                break;
            case 'G':
                dataSet->dataBits[dataCharPos] |= 2 << dataBitPos;
                break;
            case 'T':
                dataSet->dataBits[dataCharPos] |= 3 << dataBitPos;
                break;
                
        }
        cnt++;
    }

    dataSet->startPosition = pos;
    dataSet->basePairsCount = len;
    
}

void DataManager::createBitChain(int pos, int len, char* data){
    
    // Be sure that all the data is set to zero!
    memset(data, 0, len/4);
    
    char* datas = (char*)mDataBuffer.getData();
    
    int start = pos;
    int end = start+len;
    char d;
    int cnt = 0;
    int dataCharPos = 0;
    int dataBitPos = 0;
//    for(int i=start;i<end;i+=2){
//        d = *(datas+i);
//        data[dataCharPos];
//        
//        dataCharPos = (int)(cnt / 4);
//        dataBitPos = cnt%4;
//        cnt++;
//    }

    
//    datas[start+0] = 'A';
//    datas[start+1] = 'C';
//    datas[start+2] = 'G';
//    datas[start+3] = 'T';
//    datas[start+4] = 'A';
//    datas[start+5] = 'A';
//    datas[start+6] = 'A';
//    datas[start+7] = 'C';
    
    for(int i=start;i<end;i++){
        
        d = *(datas+i);
        dataCharPos = (int)(cnt / 4);
        dataBitPos = ((cnt%4)) * 2;

        // seems to be the fastest way to do it like this according to:
        // http://stackoverflow.com/questions/6860525/c-what-is-faster-lookup-in-hashmap-or-switch-statement
        //
        switch(d){
            case 'A':
                data[dataCharPos] |= 0 << dataBitPos;
                break;
            case 'C':
                data[dataCharPos] |= 1 << dataBitPos;
                break;
            case 'G':
                data[dataCharPos] |= 2 << dataBitPos;
                break;
            case 'T':
                data[dataCharPos] |= 3 << dataBitPos;
                break;
            
        }
        cnt++;
    }
    
//    for(int j=0;j<len/4;j++){
//        for(int i = 7; i >= 0; i--)
//        {
//            d = data[j];
//            std::cout << ((d >> i) & 1);
//        }
//        std::cout <<  "  ";
//        if(j%4==3) std::cout << std::endl;
//    }
//    std::cout << std::endl;    

}
 
 */

