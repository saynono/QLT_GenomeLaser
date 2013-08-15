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
#include "cinder/Xml.h"

#include "GenomeData.h"
#include "DataCrawler.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class DataManager{
    
    
public:
    
    struct GenomeDataStructure{
        int id;
        string name;
        string pathMap;
        string pathBases;
    };
    
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
    
    void loadDataFile( string path );
    void parseData( XmlTree data );
    void generateXmlFile();
    
//    void loadChromosome(int chromsomeID);
    
    const vector<GenomeDataStructure>& getDataStructure();
    GenomeData::ChromosomeDataSet getChromosomeDataSet();
    const vector<GenomeData::ROIDataSet>& getRoiMap();
    GenomeData::ROIDataSet getRoiByID(int roiID);
    GenomeData::ROIDataSet getNextRoi( DataCrawler* dataCrawler );
    
    Buffer* getDataBuffer();
    
    void updateDataCrawler( DataCrawler* dataCrawler );
    
    void selectDataStructureById( int id );
    void selectDataStructure( string name );
    
    boost::signals2::signal<void(void)> sOnDataStructureChange;
    boost::signals2::signal<void(void)> sOnRoiChange;

    
private:
    
    void            generateChromosomeMap(Buffer* b);
    void            loadDataSet( GenomeDataStructure ds );
    void            addRoi(char* datas, int len);
    

    Buffer                              mDataBuffer;
    GenomeData::ChromosomeDataSet       mCurrentDataSet;
    vector<GenomeData::ROIDataSet>      mRoiMap;
    map<int, GenomeData::ROIDataSet>    mRoiIdMap;
    vector<GenomeDataStructure>         mDataStructure;
    map<int,int>                        mRoiMapVisited;

    
};



