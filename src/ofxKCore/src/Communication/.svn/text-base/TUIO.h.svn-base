/*
*  TUIO.h
*  
*
*  Created on 2/2/09.
*  Copyright 2009 NUI Group. All rights reserved.
*
*/

#ifndef TUIO_H
#define TUIO_H

#include "../Tracking/ContourFinder.h"
#include "ofxFiducial.h"
#include "ofxOsc.h"
#include "ofxNetwork.h"

class TUIO 
{
	public:		
		TUIO();
		~TUIO();
		
		//methods
		void setup(const char* host, int port, int flashport);
		void sendTUIO(std::map<int, Blob> * fingerBlobs, std::map<int, Blob> * objectBlobs ,std::list <ofxFiducial> * fiducialsList);
		void setMode(bool fingers, bool objects, bool fiducials);

		//TCP Network 
		ofxTCPServer 	m_tcpServer;
		//OSC Network 
		ofxOscSender	TUIOSocket; 
		const char*		localHost;
		int				TUIOPort;	
		int				TUIOFlashPort;
		bool 			bHeightWidth;
		bool 			bOSCMode;
		bool			bTCPMode;
		bool			bBinaryMode;
		bool			bIsConnected;

		bool			bFingers;
		bool			bObjects;
		bool			bFiducials;

	private:
		int				frameseq;
		bool			send(string message);
		string			partialPrevMsg;
};

#endif