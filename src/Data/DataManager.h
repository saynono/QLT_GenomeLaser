//
//  DataManager.h
//  QLT_GenomeLaser
//
//  Created by say nono on 11.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#pragma once


#include "cinder/app/AppBasic.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace ci;
using namespace ci::app;
using namespace std;

class DataManager{

public:
    
    typedef struct{
        string destription;
        string data;
    } fastaSequence;
	
	void setup();
    void loadData(string file);
    void addSequence( string descript, string data );
	void update();
    void draw();

    vector<string> getData(int pos, int len);
    char getNextData();

private:

    cinder::fs::path            mFilename;
    vector<fastaSequence>       mFastaData;
    
    int                         mCurrentSequence;
    int                         mCurrentDataPosition;
};



