//
//  MainController.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 29.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "MainController.h"

	
void MainController::setup(){
    
    mAmountCrawlers = 4;
    
    mDataSaver.setup();
    mDataManager.setup();
    mDataController.setup(&mDataManager, mAmountCrawlers);
    mShapeConverter.setup();
    mPluginController.setup( mDataController.getCrawler(), &mDataSaver );
    
    mDataSaver.registerVariable( DataElement("IldaFrame.params.output.targetPointCount",&mIldaFrame.params.output.targetPointCount,DataElement::VarTypes::INTEGER) );
    mDataSaver.registerVariable( DataElement("IldaFrame.params.output.blankCount",&mIldaFrame.params.output.blankCount,DataElement::VarTypes::INTEGER) );
    mDataSaver.registerVariable( DataElement("IldaFrame.params.output.endCount",&mIldaFrame.params.output.endCount,DataElement::VarTypes::INTEGER) );
    mDataSaver.registerVariable( DataElement("IldaFrame.params.output.transform.scale.x",&mIldaFrame.params.output.transform.scale.x,DataElement::VarTypes::FLOAT) );
    mDataSaver.registerVariable( DataElement("IldaFrame.params.output.transform.scale.y",&mIldaFrame.params.output.transform.scale.y,DataElement::VarTypes::FLOAT) );
    mDataSaver.registerVariable( DataElement("IldaFrame.params.draw.lines",&mIldaFrame.params.draw.lines,DataElement::VarTypes::BOOLEAN) );
    mDataSaver.registerVariable( DataElement("IldaFrame.params.draw.points",&mIldaFrame.params.draw.points,DataElement::VarTypes::BOOLEAN) );
    
}
	
void MainController::update(){
    mDataController.update();
    mPluginController.update();
    mDataSaver.update();
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

DataSaver* MainController::getDataSaver(){
    return &mDataSaver;
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
    int cnt = 0;
    for(int i=0;i<mAmountCrawlers;i++){
        if(mDataController.getCrawler()->at(i).isActive){
            mCurrentShape.appendColouredShape2d( mPluginController.getShape( &mDataController.getCrawler()->at(i) ) );
            cnt++;
        }
    }
}

void MainController::gatherApplicationData(map<string,string>* data){
    
//    data->operator[]("IldaFrame.params.output.targetPointCount") = toString(mIldaFrame.params.output.targetPointCount);
//    data->operator[]("IldaFrame.params.output.blankCount") = toString(mIldaFrame.params.output.blankCount);
//    data->operator[]("IldaFrame.params.output.endCount") = toString(mIldaFrame.params.output.endCount);
//    data->operator[]("IldaFrame.params.output.transform.scale.x") = toString(mIldaFrame.params.output.transform.scale.x);
//    data->operator[]("IldaFrame.params.output.transform.scale.y") = toString(mIldaFrame.params.output.transform.scale.y);
//    
//    data->operator[]("IldaFrame.params.draw.lines") = toString(mIldaFrame.params.draw.lines);
//    data->operator[]("IldaFrame.params.draw.points") = toString(mIldaFrame.params.draw.points);
//    data->operator[]("LaserPreview3D.paramsView.showFrame") = toString(mIldaFrame.params.draw.lines);
    
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
