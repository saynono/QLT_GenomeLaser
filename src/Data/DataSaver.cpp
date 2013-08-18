//
//  DataSaver.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 10.08.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "DataSaver.h"

	
void DataSaver::setup(){
}

void DataSaver::update(){
    
}


// ------------------------------------------------------------------------------------

void DataSaver::saveAppSettings( string path ){
    console() << "saveAppSettings : " << path << std::endl;
    console() << "save ====> " << this << std::endl;
    XmlTree dataTree;
    dataTree.setTag("QLT_Settings");    
    map<string, DataElement>::iterator it;
    for(it=mDataElements.begin();it!=mDataElements.end();++it){
        string val;
        string type;
        DataElement::VarTypes t = (*it).second.type;
        void* p = (*it).second.pointer;
        if( t == DataElement::VarTypes::FLOAT){
            val = toString( *static_cast<float*>(p) );
            type = "FLOAT";
        }
        if( t == DataElement::VarTypes::INTEGER){
            val = toString( *static_cast<int*>(p) );
            type = "INTEGER";
        }
        if( t == DataElement::VarTypes::STRING){
            val = *static_cast<string*>(p);
            type = "STRING";
        }
        if( t == DataElement::VarTypes::BOOLEAN){
            val = toString( *static_cast<bool*>(p) );
            type = "BOOLEAN";
        }
        XmlTree tree( (*it).first, val );
        tree.setAttribute("type", type);
        dataTree.push_back( tree );
    }
    
    DataTargetPathRef f = writeFile( getAssetPath( path ), true );
    dataTree.write( f );
}


void DataSaver::loadAppSettings(string path){
    try {
        path = "QLT_Settings.xml";
        DataSourceRef pathRef = loadAsset(path);
        XmlTree data( pathRef );
        parseAppSettings(data);
    } catch (AssetLoadExc exc) {
        console() << "PATH NOT FOUND: " << path << std::endl;
        return;
    }
}

void DataSaver::parseAppSettings(XmlTree data){
    mXmlSettings = data.getChild( "QLT_Settings" );
    for( XmlTree::ConstIter varIt = mXmlSettings.begin(); varIt != mXmlSettings.end(); ++varIt ) {
        string tag = varIt->getTag();
        if( mDataElements.count(tag) ){
            string type = varIt->getAttribute("type").getValue();
            if(type.compare("FLOAT")==0){
                 *(static_cast<float*>(mDataElements[tag].pointer)) = getSettingFloat(tag);
            }
            if(type.compare("INTEGER")==0){
                 *(static_cast<int*>(mDataElements[tag].pointer)) = getSettingInteger(tag);
            }
            if(type.compare("BOOLEAN")==0){
                 *(static_cast<bool*>(mDataElements[tag].pointer)) = getSettingBoolean(tag);
            }
            if(type.compare("STRING")==0){
                 *(static_cast<string*>(mDataElements[tag].pointer)) = getSettingString(tag);
            }
        }
    }
    
    sOnLoadedSettings();
    
}


// ------------------------------------------------------------------------------------


void DataSaver::registerVariable(DataElement data){
    string name = boost::to_upper_copy(data.name);
    boost::replace_all(name, "/", ".");
    mDataElements[ name ] = data;
}


// ------------------------------------------------------------------------------------


int DataSaver::getSettingInteger(string id){
    return atoi(getSetting(id).c_str());
}

float DataSaver::getSettingFloat(string id, float default_val){
    string ret = getSetting(id);
    if(ret.compare("0") == 0) return default_val;
    return atof(ret.c_str());
}

string DataSaver::getSettingString(string id){
    return getSetting(id);
}

bool DataSaver::getSettingBoolean(string id, bool default_val){
    string ret = getSetting(id);
    if(ret.compare("0") == 0) return default_val;
    return !(atoi(ret.c_str()) == 0);
}

string DataSaver::getSetting(string id){
    if(!mXmlSettings.hasChild(id)) return "0";
    return mXmlSettings.getChild( id ).getValue();
}



