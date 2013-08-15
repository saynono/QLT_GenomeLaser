//
//  DataCrawler.h
//  QLT_GenomeLaser
//
//  Created by say nono on 22.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#ifndef QLT_GenomeLaser_DataCrawler_h
#define QLT_GenomeLaser_DataCrawler_h


//#include "cinder/Timeline.h"
#include "GenomeData.h"

class DataCrawler{

public:
    
    int     crawlerID;
    // dataset id
    int     chromosomeID;
    // position
    float   pos;
    
    double lastUpdate;
    // in ticks per second
    float  speed;
    // in basePairs
    int    length;
    // density of data
    float  density;
    // active
    bool   isActive;
    // actual data
    GenomeData::BasePairDataSet dataSet;
    
    GenomeData::ROIDataSet roiDataSet;
    
    int     roiDataSetID;
//    bool    isVisible;
    
};


#endif
