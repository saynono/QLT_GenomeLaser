//
//  DataManager.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 11.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//



#include "DataManager.h"


void DataManager::setup(){
    
    loadDataFile( "QLT_Genome_Data.xml" );
//    selectDataStructureById( 4 );
    mMainSpeed = 1;
    mBasePairCount = 0;
    
}


// ------------------------------------------------------------------------------------------------------------------------

void DataManager::loadDataFile( string path ){
    XmlTree doc( loadFile( getAssetPath(path) ) );
    DataSourceRef pathRef = loadAsset(path);
    XmlTree data( pathRef );
    parseData(data);
}

void DataManager::parseData( XmlTree d ){
    XmlTree data  = d.getChild( "QLT_Genome_Data" );
    string dataPath = data.getChild( "datapath" ).getValue();
    XmlTree sets = data.getChild( "datasets");
    for( XmlTree::Iter dataset = sets.begin(); dataset != sets.end(); ++dataset ){
        GenomeDataStructure gds;
        gds.id = dataset->getAttributeValue<int>("id");
        gds.name = dataset->getChild("title").getValue();
        gds.pathMap = dataPath+dataset->getChild("map").getValue();
        gds.pathBases = dataPath+dataset->getChild("bases").getValue();
        mDataStructure.push_back( gds );
        console() << " GenomeDataStructure : " << gds.name << "         " << gds.pathMap << "   " << gds.pathBases << std::endl;
    }
}

void DataManager::generateXmlFile(){
    XmlTree dataTree;
    dataTree.setTag("QLT_Genome_Data");

    dataTree.push_back(XmlTree("datapath","./data/exons/"));
    
    XmlTree datas("datasets","");
    for(int i=0;i<23;i++){
        XmlTree dataset("dataset","");
        dataset.setAttribute("id", i);
        dataset.push_back( XmlTree("title","Chromosome "+toString(i+1)) );
        dataset.push_back( XmlTree("map","exons."+toString(i+1)+".locations") );
        dataset.push_back( XmlTree("bases","exons."+toString(i+1)+".bases") );
        datas.push_back( dataset );
    }
    dataTree.push_back( datas );

    DataTargetPathRef f = writeFile( getAssetPath( "QLT_Genome_Data.xml" ), true );
    dataTree.write( f );
    
}

//void DataManager::loadChromosome(int chromsomeID){
//    
//    fs::path pathData = getAssetPath("data/new/exon.y.bin");
//    fs::path pathMap = getAssetPath("data/new/exon.y.locations");
//    
//    loadDataSet(pathData,pathMap);
//
//}

void DataManager::loadDataSet( GenomeDataStructure ds ){
    Buffer b = Buffer( loadFile( getAssetPath(ds.pathBases) ) );
    size_t size = b.getDataSize();
    mDataBuffer = b;

    mCurrentDataSet.basePairsCount = size;
    mCurrentDataSet.chromosomeDescription = ds.name;
    mCurrentDataSet.chromosomeID = ds.id;

    Buffer bmap = Buffer( loadFile( getAssetPath(ds.pathMap) ) );
    generateChromosomeMap( &bmap );
    
    vector<GenomeData::ROIDataSet>::const_iterator it;
    for(it=mRoiMap.begin();it!=mRoiMap.end();++it){
        int roiID = (*it).roiId;
        mRoiMapVisited[roiID] = roiID;
//        XXX
    }
    sOnDataStructureChange();
}

void DataManager::selectDataStructureById( int id ){
    vector<GenomeDataStructure>::iterator it;
    for(it=mDataStructure.begin();it!=mDataStructure.end();++it){
        if( (*it).id == id ){
            loadDataSet( (*it) );
            return;
        }
    }
    console() << "ERROR : DataManager::selectDataStructureById " << id << " not found!"<< std::endl;
}

void DataManager::selectDataStructure( string name ){
    vector<GenomeDataStructure>::iterator it;
    for(it=mDataStructure.begin();it!=mDataStructure.end();++it){
        if((*it).name.compare(name)==0){
            loadDataSet( (*it) );
            return;
        }
    }
    console() << "ERROR : DataManager::selectDataStructure " << name << " not found!"<< std::endl;
}

// ------------------------------------------------------------------------------------------------------------------------

void DataManager::generateChromosomeMap(Buffer* b){
    
    size_t size = b->getDataSize();
    char* datas = (char*)b->getData();
    
    int cnt = 0;
    int lineStart = 0;
    
    mRoiMap.clear();
    mRoiIdMap.clear();

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
    
    console() << "DataManager::generateChromosomeMap : done. Basepairs count : " << mBasePairCount << std::endl;
    
}

void DataManager::addRoi(char* datas, int len){
    string line;
    for(int i=0;i<len;++i){
        line += *(datas+i);
    }
    vector<string> tokens;
    boost::split(tokens,line,boost::is_any_of(","));

    int positionTotal = stoi(tokens[2]);
    int pairs = stoi(tokens[1]);
    int start = stoi(tokens[0]);
    int end = start+pairs;
    
    GenomeData::ROIDataSet roi;
    roi.chromosomeData = mCurrentDataSet;
    roi.basePairsCount = pairs;
    roi.startPosition = start;
    roi.endPosition = end;
    roi.positionTotal = positionTotal;
    roi.roiId = mRoiMap.size();
    roi.roiDescription = "ROI Element ID_" + toString(roi.roiId) + " " + toString(roi.positionTotal);
    mRoiMap.push_back(roi);
    mRoiIdMap[roi.roiId] = roi;
    mBasePairCount += pairs;
}

GenomeData::ROIDataSet DataManager::getNextRoi( DataCrawler* dataCrawler ){

    map<int, GenomeData::ROIDataSet>::iterator it;
    it = mRoiIdMap.find(dataCrawler->roiDataSet.roiId);
    if(it != mRoiIdMap.end()){
        it++;
        return (*it).second;
    }
    console() << "DataManager::getNextRoi :: NO NEXT ROI!!!" << std::endl;
    return dataCrawler->roiDataSet;
}

// ------------------------------------------------------------------------------------------------------------------------

const vector<DataManager::GenomeDataStructure>& DataManager::getDataStructure(){
    return mDataStructure;
}

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

float DataManager::getMainSpeed(){
    return mMainSpeed;
}

void DataManager::setMainSpeed( float s ){
    mMainSpeed = s;
}


// ------------------------------------------------------------------------------------------------------------------------


void DataManager::updateDataCrawler( DataCrawler* dataCrawler ){
        
    if(dataCrawler->length == 0) return;
    
    double time = getElapsedSeconds();
    double diff = time - dataCrawler->lastUpdate;

    float pos = dataCrawler->roiDataSet.startPosition + (diff * (float)dataCrawler->speed*mMainSpeed);
//    console() << "DataManager::updateDataCrawler!  pos "  h<< pos << " diff:" << diff << std::endl;
    dataCrawler->pos = pos;
    if( dataCrawler->roiDataSet.endPosition <= pos ){
        dataCrawler->roiDataSet = getNextRoi(dataCrawler);
        dataCrawler->roiDataSetID = dataCrawler->roiDataSet.roiId;
        dataCrawler->lastUpdate = getElapsedSeconds();
        dataCrawler->pos = dataCrawler->roiDataSet.startPosition;
        dataCrawler->speed = 2;//pow(Rand::randInt(1,4),2);
        sOnRoiChange();
        console() << "DataManager::updateDataCrawler::resetCrawler " << std::endl;
    }
//    int len = dataCrawler->length;
    int len = dataCrawler->roiDataSet.basePairsCount;
        
    char* datas = (char*)mDataBuffer.getData();
    int size = mDataBuffer.getDataSize();
    
    char d;
    string dataString = "";
    for(int i=dataCrawler->roiDataSet.startPosition;i<dataCrawler->roiDataSet.startPosition+len;i++){
        d = *(datas+min(i,size-1));        
        dataString += d;
    }
//    for(int i=start;i<end;i++){
//        
//        d = *(datas+min(i,size-1));
//        
//        dataString += d;
////        dataCharPos = (int)(cnt / 4);
////        dataBitPos = ((cnt%4)) * 2;
//        
//        // seems to be the fastest way to do it like this according to:
//        // http://stackoverflow.com/questions/6860525/c-what-is-faster-lookup-in-hashmap-or-switch-statement
//        //
//        switch(d){
//            case 'A':
////                rawData[dataCharPos] |= 0 << dataBitPos;
////                dataString += "A";
//                break;
//            case 'C':
////                rawData[dataCharPos] |= 1 << dataBitPos;
////                dataString += "C";
//                break;
//            case 'G':
////                rawData[dataCharPos] |= 2 << dataBitPos;
////                dataString += "G";
//                break;
//            case 'T':
////                dataString += "T";
////                rawData[dataCharPos] |= 3 << dataBitPos;
//                break;
//                
//        }
//        cnt++;
//    }
    
    dataCrawler->dataSet.dataBitsString = dataString;
    dataCrawler->dataSet.startPosition = pos;
    dataCrawler->dataSet.basePairsCount = len;
    dataCrawler->dataSet.chromosomeData = mCurrentDataSet;
    dataCrawler->dataSet.roi = dataCrawler->roiDataSet;
    dataCrawler->dataSet.percent = (dataCrawler->pos-dataCrawler->roiDataSet.startPosition) / (float)dataCrawler->roiDataSet.basePairsCount;

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

