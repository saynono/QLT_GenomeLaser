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
    mFilename = getAssetPath("data/genome/fasta.19621_homo_sapiens.205_short");
//    mFilename = getAssetPath("data/genome/fasta.19621_homo_sapiens.205_short2");
//    mFilename = getAssetPath("data/genome/fasta.19621_homo_sapiens.205_shorter");
//    fstream inFile(filename.c_str());
    
//    std::ifstream myfile;
//    myfile.open( mFilename.c_str(), ifstream::in);
    
    
    Buffer b = Buffer( loadFile( mFilename ) );
    
    size_t size = b.getDataSize();
    console() << " DATA SIZE " << size << std::endl;

    bool descriptionStarts = false;
    
    char* datas = (char*)b.getData();
    string seqDescription = "";
    string seqData = "";
    
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
    
}

void DataManager::addSequence( string descript, string data ){
    if(data.size() > 0 && descript.size() > 0){
        console() << "New Sequence : " << descript << "     length: " << data.size() << std::endl << data << std::endl << std::endl;
//        struct fastaSequence seq;
        fastaSequence seq;
        seq.destription = descript;
        seq.data = data;
        mFastaData.push_back(seq);
//        fastaSequenceBits b = convertSequenceToBit(seq);
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

vector<string> DataManager::getData(int pos, int len){
    
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
