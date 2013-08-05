//
//  PluginOSCController.cpp
//  QLT_GenomeLaser
//
//  Created by say nono on 31.07.13.
//  Copyright (c) 2013 http://say-nono.com. All rights reserved.
//

#include "PluginOSCController.h"

	
void PluginOSCController::setup(){
    mOscListener.setup( 1977 );
}

void PluginOSCController::dispose(){
//    map<string, vector<BasePlugin*> >::const_iterator itr;
//    for(itr = mPluginsDirectory.begin(); itr != mPluginsDirectory.end(); ++itr){
////        ????
//        (*itr).second.clear();
//    }
    mPluginsDirectory.clear();
}
	
void PluginOSCController::update(){
    while( mOscListener.hasWaitingMessages() ) {
		osc::Message message;
		mOscListener.getNextMessage( &message );
        processMessage( message );
	}
}

//------------------------------------------------------------------------------------------------------

void PluginOSCController::processMessage( const osc::Message& message ){
    string address = boost::to_upper_copy(message.getAddress());
    
    if( mPluginsOSCMapping.count(address) > 0 ){
        processPluginMessageDirect( message, mPluginsOSCMapping[address] );
        return;
    }
    
    return;

    // TODO fix the group function
    
    vector<string> tokens;
    boost::split(tokens,address,boost::is_any_of("/"));
    tokens.erase (tokens.begin(),tokens.begin()+1);

    bool isPluginMessage = false;
    string sig = boost::to_upper_copy(tokens[0]);
    map<string, vector<BasePlugin*> >::const_iterator itr;
    for(itr = mPluginsDirectory.begin(); itr != mPluginsDirectory.end(); ++itr){
//        console() << "Key: " << (*itr).first << " Value: " << (*itr).second.size();
        if(sig.compare( boost::to_upper_copy( (*itr).first )) == 0 ){
//            console() << " FOUND THE PLUGIN! " << std::endl;
            isPluginMessage = true;
            break;
        }
    }
    
    if(isPluginMessage){
        processPluginMessage( message, tokens );
    }else{
        processInteralMessage( message, tokens );
    }
    
}

//------------------------------------------------------------------------------------------------------

void PluginOSCController::processPluginMessageDirect( const osc::Message& message, OSCElement* oscElement ){
    
    cinder::osc::ArgType typeOsc = message.getArgType(0);
    OSCElement::OSCElementTypes typeVar = oscElement->type;
    
    if( typeOsc == osc::TYPE_INT32 && typeVar == OSCElement::OSCElementTypes::INTEGER ) {
        try {
//            int val = message.getArgAsInt32(0);
            int val = cinder::math<int>::clamp( message.getArgAsInt32(0), oscElement->minValue, oscElement->maxValue );
            *static_cast<int*>(oscElement->pointer) = val;
        }
        catch (...) {
            console() << "Exception reading argument as int32" << std::endl;
        }
    }
    else if( typeOsc == osc::TYPE_FLOAT && typeVar == OSCElement::OSCElementTypes::FLOAT  ) {
        try {
//            float val = message.getArgAsFloat(0);
            float val = cinder::math<float>::clamp( message.getArgAsFloat(0), oscElement->minValue, oscElement->maxValue );
            *(static_cast<float*>(oscElement->pointer)) = val;
        }
        catch (...) {
            console() << "Exception reading argument as float" << std::endl;
        }
    }
//    else if( message.getArgType(i) == osc::TYPE_STRING) {
//        try {
//            message.getArgAsString(i);
//        }
//        catch (...) {
//            console() << "Exception reading argument as string" << std::endl;
//        }
//    }
    
}

void PluginOSCController::processPluginMessage( const osc::Message& message, vector<string> tokens ){
    
    string pluginID = boost::to_upper_copy(tokens[0]);
    int size = mPluginsDirectory[ pluginID ].size();
    if( size > 0 ){
        int num = stoi(tokens[1]);
        if(num < 10){
            BasePlugin* plugin = mPluginsDirectory[pluginID].at(num);
            if(size>num) processPluginMessageSingle( message, plugin );
        }else{
            processPluginMessageGroup( message, &mPluginsDirectory[pluginID] );
        }
        
    }

}

void PluginOSCController::processPluginMessageGroup( const osc::Message& message, vector<BasePlugin*>* plugins){
    for(int i=0;i<plugins->size();i++){
        processPluginMessageSingle( message, plugins->at(i) );
    }
}

void PluginOSCController::processPluginMessageSingle( const osc::Message& message, BasePlugin* plugin ){
    plugin->processOSCMessage( message );
}


void PluginOSCController::processInteralMessage( const osc::Message& message, vector<string> tokens ){
    
    return;
    
    console() << "========= INTERNAL MESSAGE ==========" << std::endl;
    console() << "Num Arg: " << message.getNumArgs() << std::endl;
    for (int i = 0; i < message.getNumArgs(); i++) {
        console() << "-- Argument " << i << std::endl;
        console() << "---- type: " << message.getArgTypeName(i) << std::endl;
        if( message.getArgType(i) == osc::TYPE_INT32 ) {
            try {
                console() << "------ value: "<< message.getArgAsInt32(i) << std::endl;
            }
            catch (...) {
                console() << "Exception reading argument as int32" << std::endl;
            }
        }
        else if( message.getArgType(i) == osc::TYPE_FLOAT ) {
            try {
                console() << "------ value: " << message.getArgAsFloat(i) << std::endl;
            }
            catch (...) {
                console() << "Exception reading argument as float" << std::endl;
            }
        }
        else if( message.getArgType(i) == osc::TYPE_STRING) {
            try {
                console() << "------ value: " << message.getArgAsString(i).c_str() << std::endl;
            }
            catch (...) {
                console() << "Exception reading argument as string" << std::endl;
            }
        }
    }
    
}


//------------------------------------------------------------------------------------------------------


void PluginOSCController::registerPlugin( BasePlugin* plugin ){
    const map<string, OSCElement*> mapping = plugin->getOSCMapping();
    string pluginName = boost::to_upper_copy(plugin->pluginID());
    mPluginsDirectory[ pluginName ].push_back( plugin );

    int size = static_cast<int>(mPluginsDirectory[ pluginName ].size());
    string basePluginPath = "/"+pluginName+"/" + toString( size ) + "/" ;
    map<string, OSCElement*>::const_iterator itr;
    itr = mapping.begin();
    for( itr=mapping.begin(); itr!=mapping.end() ;++itr){
        string oscPath = boost::to_upper_copy( basePluginPath + (*itr).first );
        OSCElement* e = (*itr).second;
        mPluginsOSCMapping[oscPath] = e;//(*itr).second;
//        console() << "ADD => OSC_VAR : " << oscPath << "                 " << mPluginsOSCMapping[oscPath].plugin << "                 " << mPluginsOSCMapping[oscPath].plugin << std::endl;        
    }
    
}
