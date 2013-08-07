//
//  MainController.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "MainController.h"

	
void MainController::setup(){
    
    mAmountCrawlers = 2;
    
    mDataManager.setup();
    mDataController.setup(&mDataManager, mAmountCrawlers);
    mShapeConverter.setup();
    mPluginController.setup(mAmountCrawlers);
    
}
	
void MainController::update(){
    mDataController.update();
    mPluginController.update();
    createShapes();
}

//-----------------------------------------------------------------------------------------------------

ciilda::Frame* MainController::getFrameRef(){
    return &mIldaFrame;
}

const ciilda::Frame& MainController::getFrame() const{
    return mIldaFrame;
}

const ColouredShape2d& MainController::getShape() const{
    return mCurrentShape;
}


DataController* MainController::getDataController(){
    return &mDataController;
}

DataManager* MainController::getDataManager(){
    return &mDataManager;
}

PluginController* MainController::getPluginController(){
    return &mPluginController;
}

//-----------------------------------------------------------------------------------------------------

void MainController::createShapes(){
	mCurrentShape.clear();
    createTempDataBits();
    mIldaFrame.begin();
    mIldaFrame.addColouredShape2d( mCurrentShape );
    mIldaFrame.end();
}



void MainController::createTempDataBits(){
        
    for(int i=0;i<mAmountCrawlers;i++){
        
        // TODO check if plugin is visible and only then render shape
        
        const ColouredShape2d s = mPluginController.getShape(i, mDataController.getCrawler()->at(i).dataSet);
        mCurrentShape.appendColouredShape2d(s);
        
    }
    
}

//void MainController::displayLetters(){
//    float speed = 1.1f;
//    float sc = 1.0f;
//    float dc = (getElapsedSeconds() * speed);
//    if( (int)dc != mDataCounter){
//        mDataCounter = (int)dc;
//        char d = mDataManager.getNextData();
//        //        d = min('a',d);
//        Shape2d s = mShapeConverter.convertChar(d);
//        mIldaFrame.begin();
//        mIldaFrame.setColor( ColorA(.5,.4,.2,.7) );
//        mIldaFrame.moveTo(Vec2f(0.5,0));
//        float amount = 50;
//        for(int i=0;i<=amount;i++){
//            mIldaFrame.moveTo(Vec2f((sin(i/amount * M_PI * 2) * sc *.9+1)/2.0, (cos(i/amount * M_PI * 2) * sc *.9+1)/2.0));
//            mIldaFrame.lineTo(Vec2f((sin(i/amount * M_PI * 2) * sc+1)/2.0, (cos(i/amount * M_PI * 2) * sc+1)/2.0));
//        }
//        //        mIldaFrame.moveTo(Vec2f(.2,.2));
//        //        mIldaFrame.lineTo(Vec2f(.8,.2));
//        //        mIldaFrame.lineTo(Vec2f(.8,.8));
//        //        mIldaFrame.lineTo(Vec2f(.2,.8));
//        //        mIldaFrame.lineTo(Vec2f(.2,.2));
//        //        mIldaFrame.setColor( ColorA(1,1,1,1) );
//        mIldaFrame.setColor( ColorA(.5,.4,.2,.7) );
//        //        mIldaFrame.addShape2d( s );
//        mIldaFrame.end();
//        mLaserController->setPoints(mIldaFrame);
//        mLaserController->send();
//    }else{
//        if( dc-mDataCounter > .9 ){
//            //            char d = '_';
//            //            Shape2d s = mShapeConverter.convertChar(d);
//            //            mIldaFrame.begin();
//            //            mIldaFrame.addShape2d( s );
//            //            mIldaFrame.end();
//            //            mLaserController->setPoints(mIldaFrame);
//            //            mLaserController->send();
//        }
//    }
//}
