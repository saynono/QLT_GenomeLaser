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
#include <boost/algorithm/string.hpp>

#include "cinder/app/AppBasic.h"
#include "cinder/Buffer.h"
#include "cinder/Utilities.h"

#include "GenomeData.h"
#include "DataCrawler.h"

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
    
    
public:

	void setup();
    
    
    void loadChromosome(int chromsomeID);
    
    GenomeData::ChromosomeDataSet getChromosomeDataSet();
    const vector<GenomeData::ROIDataSet>& getRoiMap();
    GenomeData::ROIDataSet getRoiByID(int roiID);
    Buffer* getDataBuffer();
    
    void updateDataCrawler( DataCrawler* dataCrawler );
    
//    void createBasePairDataSet(int pos, int len, GenomeData::BasePairDataSet* dataSet);
//    void createBitChain(int pos, int len, char* data);

private:
    
    void            generateChromosomeMap(Buffer* b);
    void            loadDataSet(cinder::fs::path pathData, cinder::fs::path pathMap);
    void            addRoi(char* datas, int len);
    

    Buffer                              mDataBuffer;
    GenomeData::ChromosomeDataSet       mCurrentDataSet;
    vector<GenomeData::ROIDataSet>     mRoiMap;
    map<int, const GenomeData::ROIDataSet&>    mRoiIdMap;
};



