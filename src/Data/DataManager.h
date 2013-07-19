//
//  DataManager.h
//  QLT_GenomeLaser
//
//  Created by say nono on 11.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include <string>
#include <iostream>
#include <fstream>

#include "cinder/app/AppBasic.h"
#include "cinder/Buffer.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class DataManager{

public:
    
    typedef struct{
        string destription;
        string data;
    } fastaSequence;

    typedef struct{
        string destription;
        char* data;
        int length;
    } fastaSequenceBits;

	void setup();
    void loadData(string file);
    void addSequence( string descript, string data );
    fastaSequenceBits convertSequenceToBit(const fastaSequence& seq);
	void update();
    void draw();

    Buffer* getDataBuffer();
//    vector<string> getData(int pos, int len);
    char getNextData();

private:

    cinder::fs::path            mFilename;
    vector<fastaSequence>       mFastaData;
    vector<fastaSequenceBits>   mFastaDataBits;
    Buffer                      mDataBuffer;
    
    int                         mCurrentSequence;
    int                         mCurrentDataPosition;
};



