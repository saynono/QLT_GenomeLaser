//
//  DataManager.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 11.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//



#include "DataManager.h"


void DataManager::setup(){
    
    mCurrentDataPosition = 0;
    mCurrentSequence = 0;
    
//    mFilename = getAssetPath("data/genome/fasta.19621_homo_sapiens.205");
//    mFilename = getAssetPath("data/genome/fasta.19621_homo_sapiens.205_short");
//    mFilename = getAssetPath("data/genome/fasta.19621_homo_sapiens.205_short2");
//    mFilename = getAssetPath("data/genome/fasta.19621_homo_sapiens.205_shorter");
    
    fs::path path1 = getAssetPath("data/genome/CM000663.1| Homo sapiens chromoso _ part.fasta");
    fs::path path2 = getAssetPath("data/genome/CCDS_exons.current.txt");
    
    loadChromosomeData(path1);
    loadExomeData(path2);
    
}

void DataManager::loadChromosomeData(cinder::fs::path path){
    mFilename = path;
    Buffer b = Buffer( loadFile( mFilename ) );
    size_t size = b.getDataSize();

    bool descriptionStarts = false;
    
    char* datas = (char*)b.getData();
    string seqDescription = "";
    string seqData = "";
    
    mDataBufferOffset = 0;
    
    if(*(datas) == '>'){
        for(int i=0;i<10000;i++){
            if(*(datas+i) == 10){
                mDataBufferOffset = i+1;
                break;
            }
        }
    }
    
    for(int i=0;i<10000;i++){
        
        char d = *(datas+i);
        if(d=='>'){
            addSequence(seqDescription,seqData);
            descriptionStarts = true;
            seqDescription = "";
            seqData = "";
        }else if(d==10){
            descriptionStarts = false;
        }
        
        if(d != 10){
            if(descriptionStarts){
                seqDescription += d;
            }else{
                seqData += d;
            }
        }
    }
    
    mDataBuffer = b;
    
//    int len = 10;
//    char dataBits[len/2];
//    createBitChain(20000,len,dataBits);

}

void DataManager::loadExomeData(cinder::fs::path path){
    mFilenameExome = path;
}






void DataManager::addSequence( string descript, string data ){
    if(data.size() > 0 && descript.size() > 0){
        fastaSequence seq;
        seq.destription = descript;
        seq.data = data;
        mFastaData.push_back(seq);
    }
}

//fastaSequenceBits DataManager::convertSequenceToBit(const fastaSequence& seq){
//    fastaSequenceBits b;
//    return b;
//}

void DataManager::update(){
	
}

void DataManager::draw(){
	
}

void DataManager::loadData(string file){
    
}

Buffer* DataManager::getDataBuffer(){
    return &mDataBuffer;
}

const GenomeData::BasePairDataSet DataManager::createBasePairDataSet(int pos, int len){
    GenomeData::BasePairDataSet dataSet;
    // Be sure that all the data is set to zero!
    char rawData[(int)ceil(len/4)];
    memset(rawData, 0, len/4);
    dataSet.dataBits = rawData;
    
    char* datas = (char*)mDataBuffer.getData();
    
    int start = pos + mDataBufferOffset;
    int end = start+len;
    char d;
    int cnt = 0;
    int dataCharPos = 0;
    int dataBitPos = 0;
    
    for(int i=start;i<end;i++){
        
        d = *(datas+i);
        dataCharPos = (int)(cnt / 4);
        dataBitPos = ((cnt%4)) * 2;
        
        // seems to be the fastest way to do it like this according to:
        // http://stackoverflow.com/questions/6860525/c-what-is-faster-lookup-in-hashmap-or-switch-statement
        //
        switch(d){
            case 'A':
                dataSet.dataBits[dataCharPos] |= 0 << dataBitPos;
                break;
            case 'C':
                dataSet.dataBits[dataCharPos] |= 1 << dataBitPos;
                break;
            case 'G':
                dataSet.dataBits[dataCharPos] |= 2 << dataBitPos;
                break;
            case 'T':
                dataSet.dataBits[dataCharPos] |= 3 << dataBitPos;
                break;
                
        }
        cnt++;
    }

    dataSet.startPosition = pos;
    dataSet.basePairsCount = len;
    
    return dataSet;
}

void DataManager::createBitChain(int pos, int len, char* data){
    
    // Be sure that all the data is set to zero!
    memset(data, 0, len/4);
    
    char* datas = (char*)mDataBuffer.getData();
    
    int start = pos + mDataBufferOffset;
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


char DataManager::getNextData(){
    
    if(mFastaData.size() == 0) return 'n';
    
    mCurrentDataPosition ++;
    
    if(mCurrentDataPosition >= mFastaData[mCurrentSequence].data.size()){
        mCurrentSequence ++;
        mCurrentSequence %= mFastaData.size();
        mCurrentDataPosition = 0;
        console() << "NEXT SEQUENCE : " << mFastaData[mCurrentSequence].destription << std::endl;
    }
    
    return mFastaData[mCurrentSequence].data.at(mCurrentDataPosition);
//    mDataPos ++;
//    mSeqPos ++;
}
