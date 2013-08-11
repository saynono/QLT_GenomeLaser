//
//  WebsPlugin.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 11.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "WebsPlugin.h"

	
WebsPlugin::WebsPlugin(): BasePlugin( "WebsPlugin" ){
}

void WebsPlugin::setup(){
    
    
//    mOSCMap.insert( make_pair( "SPEED", new OSCElement( "SPEED", this, &mSpeed, OSCElement::FLOAT, 0.1, 1.0  )) );
//    mOSCMap.insert( make_pair( "LINE_HEIGHT", new OSCElement( "LINE_HEIGHT", this, &mLineHeight, OSCElement::FLOAT, 0, .3 )) );
//    mOSCMap.insert( make_pair( "LINE_POSITION", new OSCElement( "LINE_POSITION", this, &mLinePosition, OSCElement::FLOAT, 0, 1  )) );
//    mOSCMap.insert( make_pair( "LENGTH", new OSCElement( "LENGTH", this, &mLength, OSCElement::FLOAT, 0, .4 )) );
    
}

void WebsPlugin::dispose(){
}


//------------------------------------------------------------------------------------------------------

const map<string, OSCElement*>& WebsPlugin::getOSCMapping() {
    return mOSCMap;
}

//------------------------------------------------------------------------------------------------------

const ColouredShape2d& WebsPlugin::getShape( const GenomeData::BasePairDataSet& dataSet ){
    mShape.clear();
    return mShape;
}