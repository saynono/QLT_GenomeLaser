//
//  DataManager.h
//  QLT_GenomeLaser
//
//  Created by say nono on 11.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

/*
 
 
 
 The nucleic acid codes are:
 
 A --> adenosine           M --> A C (amino)
 C --> cytidine            S --> G C (strong)
 G --> guanine             W --> A T (weak)
 T --> thymidine           B --> G T C
 U --> uridine             D --> G A T
 R --> G A (purine)        H --> A C T
 Y --> T C (pyrimidine)    V --> G C A
 K --> G T (keto)          N --> A G C T (any)
 
 
 
 
 
 */


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

    
//    CG
//    AT
//    GC
//    TA
    
//    A --> adenosine           0001
#define BASE_A                  0;
//    C --> cytidine            0010
#define BASE_C                  1;
//    G --> guanine             0100
#define BASE_G                  2;
//    T --> thymidine           1000
#define BASE_T                  3;
    
////    R --> G A (purine)        0101
//#define BASEGA                  5
//#define AG                      5
//    
////    Y --> T C (pyrimidine)    1010
//#define TC                      10
//#define CT                      10
//    
////    K --> G T (keto)
//#define GT                      12
//#define TG                      12
//
////    M --> A C (amino)
//#define AC                      3
//#define CA                      3
//    
////    S --> G C (strong)
//#define GT                      6
//#define TG                      6
//    
////    W --> A T (weak)
//#define AT                      9
//#define TA                      9
//
//    
    
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
    
    void loadExomeData(cinder::fs::path path);
    void loadChromosomeData(cinder::fs::path path);

    void addSequence( string descript, string data );
    fastaSequenceBits convertSequenceToBit(const fastaSequence& seq);
	void update();
    void draw();

    Buffer* getDataBuffer();
//    vector<string> getData(int pos, int len);
    char getNextData();
    void createBitChain(int pos, int len, char* data);

private:

    cinder::fs::path            mFilename;
    cinder::fs::path            mFilenameExome;
    vector<fastaSequence>       mFastaData;
    vector<fastaSequenceBits>   mFastaDataBits;
    Buffer                      mDataBuffer;
    
    int                         mCurrentSequence;
    int                         mCurrentDataPosition;
    int                         mDataBufferOffset;
};



