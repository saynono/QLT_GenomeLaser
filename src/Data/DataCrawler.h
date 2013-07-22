//
//  DataCrawler.h
//  QLT_GenomeLaser
//
//  Created by say nono on 22.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#ifndef QLT_GenomeLaser_DataCrawler_h
#define QLT_GenomeLaser_DataCrawler_h

#include "cinder/Timeline.h"


class DataCrawler{

public:
    // dataset id
    int     chromosomeID;
    // position in 0.0-1.0
    Anim<float>   pos;
    //      in radians
    float   length;
    //      density of data
    float   density;
    // active
    bool    isActive;

    
};


#endif
