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
    
    mFilename = getAssetPath("data/genome/fasta.19621_homo_sapiens.205_shorter");
//    fstream inFile(filename.c_str());
    
    std::ifstream myfile;
    myfile.open( mFilename.c_str(), ifstream::in);
    
    string line;
    int cnt=0;
    string descript;
    string data = "";
    while (getline (myfile, line))
    {
        if(line.size() > 0){
            //        console() << cnt++ << " => " << line << std::endl;
            if(line.at(0) == '>'){
                addSequence(descript,data);
                descript = line;
            }else{
                data += line + '\n';
            }            
        }
    }
    
    addSequence(descript,data);    
    console() << "Sequences  found : " << mFastaData.size() << std::endl;

}

void DataManager::addSequence( string descript, string data ){
    if(data.size() > 0 && descript.size() > 0){
        console() << "New Sequence : " << descript << std::endl;
//        struct fastaSequence seq;
        fastaSequence seq;
        seq.destription = descript;
        seq.data = data;
        mFastaData.push_back(seq);
    }
}

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
