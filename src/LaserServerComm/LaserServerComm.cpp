//
//  LaserServerComm.cpp
//  LaserTrails
//
//  Created by say nono on 25.02.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "LaserServerComm.h"

#include <assert.h>
namespace nono {
    namespace laser {
    
    LaserServerComm::LaserServerComm(){
        mSend_socket = NULL;
        mListen_socket = NULL;
        mThread = NULL;
        mListenSocketHasShutdown = false;
        mHasDataPackageWaiting = false;
    }
    
    LaserServerComm::~LaserServerComm(){
        shutdown();
    }
    
    void LaserServerComm::setup( std::string hostnameServer, int portServer, int portListen, bool multicast )
    {
        shutdown();
        
        string path = getAssetPath("laserserver").string();
        mStartScript = std::auto_ptr<StartScript>(new StartScript());

        mStartScript->runScriptThreaded("DYLD_LIBRARY_PATH="+path+" "+path+"/server "+to_string(portServer));
        mSend_socket = new UdpTransmitSocket( IpEndpointName(hostnameServer.c_str(), portServer), multicast );
        mListen_socket = new UdpListeningReceiveSocket(IpEndpointName(IpEndpointName::ANY_ADDRESS, portListen), this);        
        mThread = std::shared_ptr<std::thread>( new std::thread( &LaserServerComm::threadSocket, this ) );
        console() << "Listening to port : " << portListen << "      sending to port : " << portServer << std::endl;

        mColorTableRed.resize(256);
        mColorTableGreen.resize(256);
        mColorTableBlue.resize(256);
        mColorTableIntensity.resize(256);

        for(int i=0;i<256;i++){
            mColorTableRed[i] = i;
            mColorTableGreen[i] = i;
            mColorTableBlue[i] = i;
            mColorTableIntensity[i] = i;
        }
        
        sendBlank();
        
    }
    
    void LaserServerComm::shutdown(){
        if (mSend_socket){
            sendBlank();
            ci::sleep( 400 );
            shutDownLaserServer();
            delete mSend_socket;
        }
        mSend_socket = NULL;
        if (mListen_socket){
            mListen_socket->AsynchronousBreak();
            while( ! mListenSocketHasShutdown ) {
                ci::sleep( 1 );
            }
            mThread->join();
            delete mListen_socket;
        }
        mListen_socket = NULL;
        if(mStartScript.get()) mStartScript->stopScriptThread();
        
    }
        
    void LaserServerComm::shutDownLaserServer(){
        
        static const int OUTPUT_BUFFER_SIZE = 32768;
        char buffer[OUTPUT_BUFFER_SIZE];
        ::osc::OutboundPacketStream p(buffer, OUTPUT_BUFFER_SIZE);
        p << 'x';
        mSend_socket->Send(p.Data(), p.Size());
    }
        
    void LaserServerComm::threadSocket(){
        ThreadSetup threadSetup;        
        mListen_socket->Run();
        mListenSocketHasShutdown = true;        
    }
        
    void LaserServerComm::ProcessPacket( const char *data, int size,
                                        const IpEndpointName& remoteEndpoint ){
        std::lock_guard<mutex> lock( mMutex );
//        if(mStartScript->isThreadRunning()) mSend_socket->Send(data, size);
        
        if(size > 1){
            if(data[size-1] == 'S'){
                size -= 3;
                if(mStartScript->isThreadRunning()) mSend_socket->Send(data+size, 3);
            }
            if(data[size-1] == 'F' || data[size-1] == 'N'){
                size -= 1;
                mDataPack.data = data;
                mDataPack.size = size;
                mHasDataPackageWaiting = true;
                if(mStartScript->isThreadRunning()){
                    char* dataAdjusted = new char[size+1];
                    memcpy(dataAdjusted, data, size);
                    adjustColors(dataAdjusted, size);
                    dataAdjusted[size] = 'F';
                    mSend_socket->Send(dataAdjusted, size+1);
                }
            }
//            else console() << "Last char : " << data[size-1] << std::endl;
        }
    }
        
//        void LaserServerComm::ProcessPacket( const char *data, int size,
//                                            const IpEndpointName& remoteEndpoint ){
//            std::lock_guard<mutex> lock( mMutex );
//            if(mStartScript->isThreadRunning()) mSend_socket->Send(data, size);
//            
//            if(size > 1){
//                if(data[size-1] == 'S') size -= 3;
//                if(data[size-1] == 'F' || data[size-1] == 'N'){
//                    size -= 1;
//                    mDataPack.data = data;
//                    mDataPack.size = size;
//                    mHasDataPackageWaiting = true;
//                    
//                    //                if(mStartScript->isThreadRunning()){
//                    //                    char* dataAdjusted = new char[size];
//                    //                    adjustColors(data, dataAdjusted, size);
//                    //                    mSend_socket->Send(data, size);
//                    //                }
//                    
//                }
//            }
//        }
        
        void LaserServerComm::adjustColors(char* data, int size){
            
            int sizePaket = sizeof(LaserPoint);
            int length = size / sizePaket;
            int pos;
            for(int i=0;i<length;i++){
                pos = i*sizePaket;
                data[pos+4] = mColorTableRed[(unsigned char)data[pos+4]];
                data[pos+5] = mColorTableGreen[(unsigned char)data[pos+5]];
                data[pos+6] = mColorTableBlue[(unsigned char)data[pos+6]];
                data[pos+7] = mColorTableIntensity[(unsigned char)data[pos+7]];
            }
        }

        
    void LaserServerComm::convertDataPackage(dataPackage dp){
        vector<LaserPoint> laserPointsTemp(10000);
        char* dataNew = reinterpret_cast<char*>(laserPointsTemp.data());
        memset(dataNew, 0, dp.size);
        memcpy(dataNew, dp.data, dp.size);
        
        int length = dp.size / sizeof(LaserPoint);
        if(length>0){
            laserPointsTemp.resize(length);
            mLaserPoints.swap(laserPointsTemp);
        }
    }
        
    bool LaserServerComm::hasDataPackageWaiting(){
        std::lock_guard<mutex> lock( mMutex );
        return mHasDataPackageWaiting;
    }

    vector<LaserPoint>* LaserServerComm::getDataPackage(){
        std::lock_guard<mutex> lock( mMutex );
        
//        if(mStartScript->isThreadRunning()) mSend_socket->Send(mDataPack.data, mDataPack.size);

        
        convertDataPackage(mDataPack);
        mHasDataPackageWaiting = false;
        return &mLaserPoints;
//        return mDataPack;
    }
        
        
        void LaserServerComm::sendBlank(){
            vector<LaserPoint> vec;
            
            float percent,amount;
            amount = 100;
            for(int i=0;i<amount;i++){
                LaserPoint p;
                percent = i/ amount;
                p.x = sin(toRadians(percent*360.0)) * 100 + 2048;
                p.y = cos(toRadians(percent*360.0)) * 100 + 2048;
                p.r = 0;
                p.g = 0;
                p.b = 0;
                p.i = 0;
                vec.push_back(p);
            }
            sendData(vec);
        }
        
        void LaserServerComm::sendData(const vector<LaserPoint>& points){
            int kNumPoints = points.size();
            int amount = kNumPoints * 8;
            char* buf = new char[amount+1+3];
            int bufptr = 0;
            int speed = 1000;
            double x,y;
            for (int i = 0; i < kNumPoints; ++i) {
                x = points[i].x;
                y = points[i].y;
                //        double x = 2048.0 + i * 10.0 - kNumPoints/10/2;
                //        double y = 2048.0 + sin(t + i/10.0)*100.0;
                buf[bufptr++] = (int)x & 0xff;
                buf[bufptr++] = ((int)x >> 8) & 0xf;
                buf[bufptr++] = (int)y & 0xff;
                buf[bufptr++] = ((int)y >> 8) & 0xf;
                buf[bufptr++] = mColorTableRed[points[i].r];
                buf[bufptr++] = mColorTableGreen[points[i].g];
                buf[bufptr++] = mColorTableBlue[points[i].b];
                buf[bufptr++] = 255;
            }
            buf[bufptr++] = 'F';
            buf[bufptr++] = (int)speed & 0xff;
            buf[bufptr++] = ((int)speed >> 8) & 0xff;
            buf[bufptr++] = 'S';
            mSend_socket->Send(buf,bufptr);
        }
	
}// namespace nono
}// namespace laser