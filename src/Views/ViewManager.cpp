//
//  ViewManager.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "ViewManager.h"

	
void ViewManager::setup(MainController* mc){
    
    mMainController = mc;

    mLaserPreview3D.setup( 1024,1024 );

    mCircDataLayer.setup( 1024, 1024 );
    mCircDataLayer.setDataBuffer( mMainController->getDataManager()->getDataBuffer() );
    mCircDataLayer.setDataController( mMainController->getDataController() );
    mCircDataLayer.drawCircularDataStructure( 100, 10000 );



}

//----------------------------------------------------------------------------------------------------------------

LaserPreview3D* ViewManager::getLaserPreview3D(){
    return &mLaserPreview3D;
}

CircularDataLayer* ViewManager::getCircularDataLayer(){
    return &mCircDataLayer;
}

//----------------------------------------------------------------------------------------------------------------

void ViewManager::update(){
	mLaserPreview3D.calculateDotsOnGauze( mMainController->getFrameRef() ),
    mLaserPreview3D.update();
    mCircDataLayer.updateLayer();
    
    mLaserPreview3D.draw();

}


void ViewManager::draw(){
	
}

