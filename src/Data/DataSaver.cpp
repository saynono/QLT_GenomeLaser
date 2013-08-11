//
//  DataSaver.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 10.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "DataSaver.h"

	
void DataSaver::setup(){
    bDoSaveAppSettings = false;
    saveAppSettings("QLT_Settings.xml");
    
    console() << "====================== new datasaver =====================" << std::endl;
    console() << " ====> " << this << std::endl;
    //    gatherAppSettings();
}

void DataSaver::update(){
    
}


// ------------------------------------------------------------------------------------

void DataSaver::saveAppSettings(string path){
    console() << "saveAppSettings : " << path << std::endl;
    console() << "save ====> " << this << std::endl;
    XmlTree data;
    data.setTag("QLT_Settings");
    gatherAppSettings(&data);
    DataTargetPathRef f = writeFile( getAssetPath( "QLT_Settings.xml" ), true );
    data.write( f );
}

void DataSaver::loadAppSettings(string path){
    try {
        DataSourceRef pathRef = loadAsset(path);
        XmlTree data( pathRef );
        parseAppSettings(data);
    } catch (AssetLoadExc exc) {
        console() << "PATH NOT FOUND: " << path << std::endl;
        return;
    }
}

void DataSaver::parseAppSettings(XmlTree data){
    
}

void DataSaver::gatherAppSettings(XmlTree* data){
    console() << "DataSaver::gatherAppSettings "<< std::endl;
//    boost::optional<int> result = sGetApplicationData();
    boost::optional< map<string,string> > res = sGetApplicationData();
    map<string,string> result = res.get();
//    console() <<  " result :: " << result.get() << std::endl;
    map<string,string>::iterator it;
    for(it=result.begin();it!=result.end();++it){
        data->push_back( XmlTree( (*it).first, (*it).second ) );
        console() << "GATHERING     " << (*it).first << "   => " << (*it).second << std::endl;
    }
//    return result;
    
/*
 
 
    void SettingsPanel::onSliderLaserOutput( Gwen::Controls::Base* pControl ){
        Gwen::Controls::Label* label = mLabelsMap[pControl];
        Gwen::Controls::Slider* pSlider = ( Gwen::Controls::Slider* ) pControl;
        label->SetValue( toString(( int ) pSlider->GetFloatValue()));
        
            mIldaFrame->params.output.targetPointCount = ( int ) pSlider->GetFloatValue();
            mIldaFrame->params.output.blankCount = ( int ) pSlider->GetFloatValue();
            mIldaFrame->params.output.endCount = ( int ) pSlider->GetFloatValue();
            mLaserController->setPPS(( int ) pSlider->GetFloatValue());
            mLaserPreview3D->setLaserAngle( ( int ) pSlider->GetFloatValue() );
            float scale = pSlider->GetFloatValue()/100.0f;
            mIldaFrame->params.output.transform.scale.x = scale;
            mIldaFrame->params.output.transform.scale.y = scale;
            mLaserPreview3D->paramsView.fansIntensity = ( float ) pSlider->GetFloatValue() / 100.0;
        
    }
    
    void SettingsPanel::onCheckBoxLaserOutput( Gwen::Controls::Base* pControl ){
        
        Gwen::Controls::CheckBox* pCheckBox = ( Gwen::Controls::CheckBox* ) pControl;
        string controlName = pControl->GetName().c_str();
        console() << controlName << " : " << pCheckBox->GetValue().c_str() << std::endl;
        if (controlName.compare("Draw Lines") == 0){
            mIldaFrame->params.draw.lines = pCheckBox->IsChecked() == 1;
            mLaserPreview3D->paramsView.showFrame = pCheckBox->IsChecked() == 1;
            mIldaFrame->params.draw.points = pCheckBox->IsChecked() == 1;
            mLaserPreview3D->paramsView.showDotsOnGauze = pCheckBox->IsChecked() == 1;
            mLaserPreview3D->paramsView.showLinesOnGauze = pCheckBox->IsChecked() == 1;
            mLaserPreview3D->paramsView.showRays = pCheckBox->IsChecked() == 1;
            mLaserPreview3D->paramsView.showFans = pCheckBox->IsChecked() == 1;
*/
}

// ------------------------------------------------------------------------------------


void DataSaver::savePluginSettings(string path){
    XmlTree data;
    data.setTag("Hallo!");
    data.setValue("und guten Abend!");
    DataTargetPathRef f = writeFile( getAssetPath( path ), true );
    data.write( f );
}

void DataSaver::loadPluginSettings(string path){
    try {
        DataSourceRef pathRef = loadAsset(path);
        XmlTree data( pathRef );
        parseAppSettings(data);
    } catch (AssetLoadExc exc) {
        console() << "PATH NOT FOUND: " << path << std::endl;
        return;
    }
}






