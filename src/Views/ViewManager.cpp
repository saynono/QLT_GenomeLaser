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

    
    
    DataSaver* mDataSaver = mMainController->getDataSaver();
    mDataSaver->registerVariable( DataElement("LaserPreview3D.paramsView.fansIntensity",&mLaserPreview3D.paramsView.fansIntensity,DataElement::VarTypes::FLOAT) );
    mDataSaver->registerVariable( DataElement("LaserPreview3D.paramsView.showDotsOnGauze",&mLaserPreview3D.paramsView.showDotsOnGauze,DataElement::VarTypes::BOOLEAN) );
    mDataSaver->registerVariable( DataElement("LaserPreview3D.paramsView.showLinesOnGauze",&mLaserPreview3D.paramsView.showLinesOnGauze,DataElement::VarTypes::BOOLEAN) );
    mDataSaver->registerVariable( DataElement("LaserPreview3D.paramsView.showRays",&mLaserPreview3D.paramsView.showRays,DataElement::VarTypes::BOOLEAN) );
    mDataSaver->registerVariable( DataElement("LaserPreview3D.paramsView.showFans",&mLaserPreview3D.paramsView.showFans,DataElement::VarTypes::BOOLEAN) );
    mDataSaver->registerVariable( DataElement("LaserPreview3D.paramsView.showFrame",&mLaserPreview3D.paramsView.showFrame,DataElement::VarTypes::BOOLEAN) );
    

}

//----------------------------------------------------------------------------------------------------------------

void ViewManager::gatherApplicationData( map<string, string>* data ){
    console() << " ViewManager::gatherApplicationData " << std::endl;
//    map<string,string> result;
    
//    result["IldaFrame.params.output.targetPointCount"] = toString(mIldaFrame.params.output.targetPointCount);
//    result["IldaFrame.params.output.blankCount"] = toString(mIldaFrame.params.output.blankCount);
//    result["IldaFrame.params.output.endCount"] = toString(mIldaFrame.params.output.endCount);
//    result["IldaFrame.params.output.transform.scale.x"] = toString(mIldaFrame.params.output.transform.scale.x);
//    result["IldaFrame.params.output.transform.scale.y"] = toString(mIldaFrame.params.output.transform.scale.y);
//    
//    result["IldaFrame.params.draw.lines"] = toString(mIldaFrame.params.draw.lines);
//    result["IldaFrame.params.draw.points"] = toString(mIldaFrame.params.draw.points);
//    result["LaserPreview3D.paramsView.showFrame"] = toString(mIldaFrame.params.draw.lines);
//    result["LaserController.setPPS(( int ) pSlider->GetFloatValue());
//    result["LaserPreview3D.setLaserAngle( ( int ) pSlider->GetFloatValue() );
    //        float scale = pSlider->GetFloatValue()/100.0f;
//    data->operator[]("LaserPreview3D.paramsView.fansIntensity") = toString(mLaserPreview3D.paramsView.fansIntensity);
//    data->operator[]("LaserPreview3D.paramsView.showDotsOnGauze") = toString(mLaserPreview3D.paramsView.showDotsOnGauze);
//    data->operator[]("LaserPreview3D.paramsView.showLinesOnGauze") = toString(mLaserPreview3D.paramsView.showLinesOnGauze);
//    data->operator[]("LaserPreview3D.paramsView.showRays") = toString(mLaserPreview3D.paramsView.showRays);
//    data->operator[]("LaserPreview3D.paramsView.showFans") = toString(mLaserPreview3D.paramsView.showFans);
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

