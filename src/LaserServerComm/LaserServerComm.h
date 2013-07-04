//
//  LaserServerComm.h
//  LaserTrails
//
//  Created by say nono on 25.02.13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ip/UdpSocket.h"
#include "ip/PacketListener.h"
#include "osc/OscOutboundPacketStream.h"
#include "cinder/app/AppBasic.h"
#include "StartScript.h"
//    

using namespace ci;
using namespace ci::app;
using namespace std;

namespace nono {
    namespace laser {
        
        struct LaserPoint {
            unsigned short x;  // 2 Bytes  Value 0 - 4095  X-Coordinate
            unsigned short y;  // 2 Bytes  Value 0 - 4095  Y-coordinate
            unsigned char  r;  // 1 Byte   Value 0 - 255   Red
            unsigned char  g;  // 1 Byte   Value 0 - 255   Green
            unsigned char  b;  // 1 Byte   Value 0 - 255   Blue
            unsigned char  i;  // 1 Byte   Value 0 - 255   Intensity
        };
        
        struct dataPackage{
            const char *data;
            int size;
        };
        
        class LaserServerComm : public PacketListener {
        public:
            LaserServerComm();
            ~LaserServerComm();
            
            void setup( std::string hostnameServer, int portServer, int portListen , bool multicast );
            
            void sendBlank();
            void sendData(const vector<LaserPoint>& points);
            
            void shutdown();
            void shutDownLaserServer();
            
            virtual void ProcessPacket( const char *data, int size,
                                       const IpEndpointName& remoteEndpoint );
            
            bool hasDataPackageWaiting();
            vector<LaserPoint>* getDataPackage();
            
            vector<char> mColorTableRed;
            vector<char> mColorTableGreen;
            vector<char> mColorTableBlue;
            vector<char> mColorTableIntensity;

            
        private:
            
            void threadSocket();
            void convertDataPackage(dataPackage dp);
            void adjustColors(char* data, int size);
            
            UdpTransmitSocket*              mSend_socket;
            UdpListeningReceiveSocket*      mListen_socket;
            std::auto_ptr<StartScript>      mStartScript;
            
            mutable std::mutex              mMutex;
            std::shared_ptr<std::thread>    mThread;
            bool                            mListenSocketHasShutdown;
            dataPackage                     mDataPack;
            bool                            mHasDataPackageWaiting;
            
            vector<LaserPoint>              mLaserPoints;
            char                            mIncomingData[100000];
            int                             mIncomingDataPos;

            
            
        };
    }
}


