//
//  MainController.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "MainController.h"

	
void MainController::setup(){
    mDataManager.setup();
    mDataController.setup(&mDataManager);
    mShapeConverter.setup();
}
	
void MainController::update(){
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


//-----------------------------------------------------------------------------------------------------

void MainController::createShapes(){
	mCurrentShape.clear();
    createTempDataBits();
//    mIldaFrame.clear();
    mIldaFrame.begin();
    mIldaFrame.addColouredShape2d( mCurrentShape );
    mIldaFrame.end();
//    console() << " mCurrentShape : " << mCurrentShape.getNumContours() << std::endl;
}



void MainController::createTempDataBits(){
    
    //TODO need to fix the offset (20000)
    
    ColouredShape2d s1,s2;
    int len = 8*10;
    char dataBits[(int)ceil(len/4)];
    int dataOffset = 20000;//+getElapsedFrames();
    float startAngle = toRadians(-(float)getElapsedFrames()/10.0);
    //    float startAngle = toRadians(0.0f);
    
    mDataManager.createBitChain(dataOffset,len,dataBits);
    //    s1 = mDataConverter.convertBitChainToCircularShape(dataBits, len/2, .1, startAngle, toRadians(180.0), .92);
    s1 = mDataConverter.convertBitChainToShape(dataBits, len, .5, startAngle, toRadians(90.0), .5);
    
    int len2 = 20;
    char dataBits2[(int)ceil(len/4)];
    int dataOffset2 = 50000;//+getElapsedFrames();
    float startAngle2 = toRadians(-getElapsedSeconds());
    
    mDataManager.createBitChain(dataOffset2,len2,dataBits2);
    s2 = mDataConverter.convertBitChainToShape(dataBits2, len2, .1, startAngle2, toRadians(270.0), .65);
    
    mCurrentShape.appendColouredShape2d(s1);
    mCurrentShape.appendColouredShape2d(s2);
    
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
