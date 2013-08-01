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
    string address = message.getAddress();
    
    console() << "New message received" << std::endl;
    console() << "Address: " << message.getAddress() << std::endl;
    
    vector<string> tokens;
    boost::split(tokens,address,boost::is_any_of("/"));
    tokens.erase (tokens.begin(),tokens.begin()+1);
    
//    console() << "=========" << std::endl;
//    for(int i=0;i<tokens.size();i++){
//        console() << i << " => " << tokens[i] << std::endl;
//    }
//    console() << "=========" << std::endl;
    
    
    bool isPluginMessage = false;
    string sig = boost::to_upper_copy(tokens[0]);
    map<string, vector<BasePlugin*> >::const_iterator itr;
    for(itr = mPluginsDirectory.begin(); itr != mPluginsDirectory.end(); ++itr){
        console() << "Key: " << (*itr).first << " Value: " << (*itr).second.size();
        if(sig.compare( boost::to_upper_copy( (*itr).first )) == 0 ){
            console() << " FOUND THE PLUGIN! " << std::endl;
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
    mPluginsDirectory[ boost::to_upper_copy(plugin->pluginID()) ].push_back( plugin );
    
}
