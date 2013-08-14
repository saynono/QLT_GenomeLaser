//
//  GenomeData.h
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once

#include "cinder/app/AppBasic.h"

namespace GenomeData{

    struct ChromosomeDataSet{
        std::string chromosomeDescription;
        int chromosomeID;
        int basePairsCount;
    };
    
    struct ROIDataSet{
        int roiId;
        std::string roiDescription;
        int startPosition;
        int endPosition;
        int basePairsCount;
        ChromosomeDataSet chromosomeData;
    };

    struct BasePairDataSet{
        int startPosition;
        int basePairsCount;
        ChromosomeDataSet chromosomeData;
        std::string dataBits;
        std::string dataBitsString;
        ROIDataSet roi;
    };
    
}





