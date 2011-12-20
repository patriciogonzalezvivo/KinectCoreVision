/*
*  TUIO.h
*
*
*  Created on 2/2/09.
*  Copyright 2009 NUI Group. All rights reserved.
*
*/

#include "TUIO.h"

TUIO::TUIO(){

}

TUIO::~TUIO(){
	// this could be useful for whenever we get rid of an object
}

void TUIO::setup(const char* host, int port, int flashport) {
	localHost = host;
	TUIOPort = port;
	TUIOFlashPort = flashport;
	frameseq = 0;

	//FOR TCP
	bIsConnected = m_tcpServer.setup(TUIOFlashPort);

	//FOR OSC
	TUIOSocket.setup(localHost, TUIOPort);
}

void TUIO::setMode(bool blobs, bool fingers, bool objects) {
	bBlobs	 = true; //bBlobs;
	bFingers = fingers;
	bObjects = objects;
}

void TUIO::sendTUIO(map<int, Blob> *blobBlobs, map<int, Blob> *fingerBlobs, map<int, Blob> *objectBlobs){
	frameseq += 1;

	// if sending OSC (not TCP)
	if(bOSCMode) {
		if(bBlobs){
			ofxOscBundle b;
			ofxOscMessage alive;
			// Sends alive message - saying 'Hey, there's no alive blobs'
			alive.setAddress("/tuio/2Dcur");
			alive.addStringArg("alive");

			// Send fseq message
			ofxOscMessage fseq;
			fseq.setAddress( "/tuio/2Dcur" );
			fseq.addStringArg( "fseq" );
			fseq.addIntArg(frameseq);

			if(blobBlobs->size() == 0){
				b.addMessage( alive );		// add message to bundle
				b.addMessage( fseq );		// add message to bundle
				TUIOSocket.sendBundle( b ); // send bundle
			} else { // actually send the blobs
				map<int, Blob>::iterator blob;
				for(blob = blobBlobs->begin(); blob != blobBlobs->end(); blob++) {
					// omit point (0,0) since this means that we are outside of the range
					if(blob->second.centroid.x == 0 && blob->second.centroid.y == 0)
						continue;

					//Set Message
					ofxOscMessage set;
					set.setAddress( "/tuio/2Dcur" );
					set.addStringArg("set");
					set.addIntArg(blob->second.id);				// id
					set.addFloatArg(blob->second.centroid.x);	// x
					set.addFloatArg(blob->second.centroid.y);	// y
					set.addFloatArg(blob->second.D.x);			// dX
					set.addFloatArg(blob->second.D.y);			// dY
					set.addFloatArg(blob->second.maccel);		// m
					if(bHeightWidth){
						set.addFloatArg(blob->second.boundingRect.width);	// wd
						set.addFloatArg(blob->second.boundingRect.height);	// ht
					}
					b.addMessage( set );							// add message to bundle
					alive.addIntArg(blob->second.id);				// add blob to list of ALL active IDs
				}

				b.addMessage( alive );	 //add message to bundle
				b.addMessage( fseq );	 //add message to bundle
				TUIOSocket.sendBundle( b ); //send bundle
			}
		}

		if(bFingers){
			ofxOscBundle b;
			ofxOscMessage alive;
			// Sends alive message - saying 'Hey, there's no alive blobs'
			alive.setAddress("/tuio/2Dcur");
			alive.addStringArg("alive");

			// Send fseq message
			ofxOscMessage fseq;
			fseq.setAddress( "/tuio/2Dcur" );
			fseq.addStringArg( "fseq" );
			fseq.addIntArg(frameseq);

			if(fingerBlobs->size() == 0){
				b.addMessage( alive );		// add message to bundle
				b.addMessage( fseq );		// add message to bundle
				TUIOSocket.sendBundle( b ); // send bundle
			} else { // actually send the blobs
				map<int, Blob>::iterator blob;
				for(blob = fingerBlobs->begin(); blob != fingerBlobs->end(); blob++) {
					// omit point (0,0) since this means that we are outside of the range
					if(blob->second.centroid.x == 0 && blob->second.centroid.y == 0)
						continue;

					//Set Message
					ofxOscMessage set;
					set.setAddress( "/tuio/2Dcur" );
					set.addStringArg("set");
					set.addIntArg(blob->second.id);				// id
					set.addFloatArg(blob->second.centroid.x);	// x
					set.addFloatArg(blob->second.centroid.y);	// y
					set.addFloatArg(blob->second.D.x);			// dX
					set.addFloatArg(blob->second.D.y);			// dY
					set.addFloatArg(blob->second.maccel);		// m
					if(bHeightWidth){
						set.addFloatArg(blob->second.boundingRect.width);	// wd
						set.addFloatArg(blob->second.boundingRect.height);	// ht
					}
					b.addMessage( set );							// add message to bundle
					alive.addIntArg(blob->second.id);				// add blob to list of ALL active IDs
				}

				b.addMessage( alive );	 //add message to bundle
				b.addMessage( fseq );	 //add message to bundle
				TUIOSocket.sendBundle( b ); //send bundle
			}
		}

		if(bObjects){
			ofxOscBundle b_obj;
			ofxOscMessage alive_obj;
			// Sends alive message - saying 'Hey, there's no alive blobs'
			alive_obj.setAddress("/tuio/2Dcur");
			alive_obj.addStringArg("alive");

			// Send fseq message
			ofxOscMessage fseq_obj;
			fseq_obj.setAddress( "/tuio/2Dcur" );
			fseq_obj.addStringArg( "fseq" );
			fseq_obj.addIntArg(frameseq);

			if(objectBlobs->size() == 0){
				b_obj.addMessage( alive_obj );		// add message to bundle
				b_obj.addMessage( fseq_obj );		// add message to bundle
				TUIOSocket.sendBundle( b_obj ); // send bundle
			} else {
				map<int, Blob>::iterator blob_obj;
				for(blob_obj = objectBlobs->begin(); blob_obj != objectBlobs->end(); blob_obj++) {
					// omit point (0,0) since this means that we are outside of the range
					if(blob_obj->second.centroid.x == 0 && blob_obj->second.centroid.y == 0)
						continue;

					//Set Message
					ofxOscMessage set_obj;
					set_obj.setAddress( "/tuio/2Dcur" );
					set_obj.addStringArg("set");
					set_obj.addIntArg(blob_obj->second.id);				// id
					set_obj.addFloatArg(blob_obj->second.centroid.x);	// x
					set_obj.addFloatArg(blob_obj->second.centroid.y);	// y
					set_obj.addFloatArg(blob_obj->second.D.x);			// dX
					set_obj.addFloatArg(blob_obj->second.D.y);			// dY
					set_obj.addFloatArg(blob_obj->second.maccel);		// m
					if(bHeightWidth) {
						set_obj.addFloatArg(blob_obj->second.boundingRect.width);	// wd
						set_obj.addFloatArg(blob_obj->second.boundingRect.height);	// ht
					}
					b_obj.addMessage( set_obj );							// add message to bundle
					alive_obj.addIntArg(blob_obj->second.id);				// add blob to list of ALL active IDs
				}
				b_obj.addMessage( alive_obj );		//add message to bundle
				b_obj.addMessage( fseq_obj );		//add message to bundle
				TUIOSocket.sendBundle( b_obj ); //send bundle
			}
		}
	}

	if(bTCPMode) { // else, if TCP (flash) mode {
		if(bBlobs || bFingers || bObjects) {
			if(blobBlobs->size() == 0 && fingerBlobs->size() == 0 && objectBlobs->size() == 0) {
				m_tcpServer.sendToAll("<OSCPACKET ADDRESS=\"127.0.0.1\" PORT=\""+ofToString(TUIOFlashPort)+"\" TIME=\""+ofToString(ofGetElapsedTimef())+"\">" +
									  "<MESSAGE NAME=\"/tuio/2Dcur\">"+
									  "<ARGUMENT TYPE=\"s\" VALUE=\"alive\"/>"+
									  "</MESSAGE>"+
									  "<MESSAGE NAME=\"/tuio/2Dcur\">"+
									  "<ARGUMENT TYPE=\"s\" VALUE=\"fseq\"/>"+
									  "<ARGUMENT TYPE=\"i\" VALUE=\""+ofToString(frameseq)+"\"/>" +
									  "</MESSAGE>"+
									  "</OSCPACKET>");
			} else {
				string setBlobsMsg;
				string aliveBeginMsg = "<MESSAGE NAME=\"/tuio/2Dcur\"><ARGUMENT TYPE=\"s\" VALUE=\"alive\"/>";
				string aliveEndMsg = "</MESSAGE>";
				string aliveBlobsMsg;

				//Blob TUIO
				map<int, Blob>::iterator blob;
				for(blob = blobBlobs->begin(); blob != blobBlobs->end(); blob++){
					// omit point (0,0) since this means that we are outside of the range
					if(blob->second.centroid.x == 0 && blob->second.centroid.y == 0)
						continue;

					// if sending height and width
					if(bHeightWidth){
						setBlobsMsg += "<MESSAGE NAME=\"/tuio/2Dcur\"><ARGUMENT TYPE=\"s\" VALUE=\"set\"/><ARGUMENT TYPE=\"i\" VALUE=\""+ofToString(blob->second.id)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob->second.centroid.x)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob->second.centroid.y)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob->second.D.x)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob->second.D.y)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob->second.maccel)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob->second.boundingRect.width)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob->second.boundingRect.height)+"\"/>"+
						"</MESSAGE>";
					} else {
						setBlobsMsg += "<MESSAGE NAME=\"/tuio/2Dcur\"><ARGUMENT TYPE=\"s\" VALUE=\"set\"/><ARGUMENT TYPE=\"i\" VALUE=\""+ofToString(blob->second.id)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob->second.centroid.x)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob->second.centroid.y)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob->second.D.x)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob->second.D.y)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob->second.maccel)+"\"/>"+
						"</MESSAGE>";
					}
					aliveBlobsMsg += "<ARGUMENT TYPE=\"i\" VALUE=\""+ofToString(blob->second.id)+"\"/>";
				}

				//Finger TUIO
				//map<int, Blob>::iterator blob;
				map<int, Blob>::iterator blob_fng;
				for(blob_fng = fingerBlobs->begin(); blob_fng != fingerBlobs->end(); blob_fng++){
					// omit point (0,0) since this means that we are outside of the range
					if(blob_fng->second.centroid.x == 0 && blob_fng->second.centroid.y == 0)
						continue;

					// if sending height and width
					if(bHeightWidth){
						setBlobsMsg += "<MESSAGE NAME=\"/tuio/2Dcur\"><ARGUMENT TYPE=\"s\" VALUE=\"set\"/><ARGUMENT TYPE=\"i\" VALUE=\""+ofToString(blob->second.id)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_fng->second.centroid.x)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_fng->second.centroid.y)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_fng->second.D.x)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_fng->second.D.y)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_fng->second.maccel)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_fng->second.boundingRect.width)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_fng->second.boundingRect.height)+"\"/>"+
						"</MESSAGE>";
					} else {
						setBlobsMsg += "<MESSAGE NAME=\"/tuio/2Dcur\"><ARGUMENT TYPE=\"s\" VALUE=\"set\"/><ARGUMENT TYPE=\"i\" VALUE=\""+ofToString(blob->second.id)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_fng->second.centroid.x)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_fng->second.centroid.y)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_fng->second.D.x)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_fng->second.D.y)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_fng->second.maccel)+"\"/>"+
						"</MESSAGE>";
					}
					aliveBlobsMsg += "<ARGUMENT TYPE=\"i\" VALUE=\""+ofToString(blob_fng->second.id)+"\"/>";
				}


				//Object TUIO
				map<int, Blob>::iterator blob_obj;
				for(blob_obj = objectBlobs->begin(); blob_obj != objectBlobs->end(); blob_obj++) {
					// omit point (0,0) since this means that we are outside of the range
					if(blob_obj->second.centroid.x == 0 && blob_obj->second.centroid.y == 0)
						continue;

					// if sending height and width
					if(bHeightWidth) {
						setBlobsMsg += "<MESSAGE NAME=\"/tuio/2Dcur\"><ARGUMENT TYPE=\"s\" VALUE=\"set\"/><ARGUMENT TYPE=\"i\" VALUE=\""+ofToString(blob_obj->second.id)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_obj->second.centroid.x)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_obj->second.centroid.y)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_obj->second.D.x)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_obj->second.D.y)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_obj->second.maccel)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_obj->second.boundingRect.width)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_obj->second.boundingRect.height)+"\"/>"+
						"</MESSAGE>";
					} else {
						setBlobsMsg += "<MESSAGE NAME=\"/tuio/2Dcur\"><ARGUMENT TYPE=\"s\" VALUE=\"set\"/><ARGUMENT TYPE=\"i\" VALUE=\""+ofToString(blob_obj->second.id)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_obj->second.centroid.x)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_obj->second.centroid.y)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_obj->second.D.x)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_obj->second.D.y)+"\"/>"+
						"<ARGUMENT TYPE=\"f\" VALUE=\""+ofToString(blob_obj->second.maccel)+"\"/>"+
						"</MESSAGE>";
					}
					aliveBlobsMsg += "<ARGUMENT TYPE=\"i\" VALUE=\""+ofToString(blob_obj->second.id)+"\"/>";
				}

				string fseq = "<MESSAGE NAME=\"/tuio/2Dcur\"><ARGUMENT TYPE=\"s\" VALUE=\"fseq\"/><ARGUMENT TYPE=\"i\" VALUE=\""+ofToString(frameseq) + "\"/></MESSAGE>";
				m_tcpServer.sendToAll("<OSCPACKET ADDRESS=\"127.0.0.1\" PORT=\"" +
									  ofToString(TUIOFlashPort) + "\" TIME=\""+ofToString(ofGetElapsedTimef()) + "\">" +
									  setBlobsMsg + aliveBeginMsg + aliveBlobsMsg + aliveEndMsg + fseq + "</OSCPACKET>");
			}
		}
	}

	if (bBinaryMode) { // else, if TCP (binary) mode
		if(bBlobs) {
			uchar buf[1024*8];
			uchar *p = buf;
			// Add "CCV" as a data header
			*p++ = 'C';	*p++ = 'C';	*p++ = 'V';	*p++ = '\0';
			if(blobBlobs->size() == 0){
				memset(p, 0, 4);
				p += 4;
		    } else {
				int count = 0;
				map<int, Blob>::iterator blob;
				// count the blobs that are non (0,0)
				for(blob = blobBlobs->begin(); blob != blobBlobs->end(); blob++) {
					// omit point (0,0) since this means that we are outside of the range
					if(blob->second.centroid.x == 0 && blob->second.centroid.y == 0)
						continue;
					count++;
				}
				// send blob count first
				memcpy(p, &count, 4);	p += 4;
				// send blob information
				for(blob = blobBlobs->begin(); blob != blobBlobs->end(); blob++) {
					// omit point (0,0) since this means that we are outside of the range
					if(blob->second.centroid.x == 0 && blob->second.centroid.y == 0)
						continue;

					memcpy(p, &blob->second.id, 4);							p += 4;
					memcpy(p, &blob->second.centroid.x, 4);					p += 4;
					memcpy(p, &blob->second.centroid.y, 4);					p += 4;
					memcpy(p, &blob->second.D.x, 4);						p += 4;
					memcpy(p, &blob->second.D.y, 4);						p += 4;
					memcpy(p, &blob->second.maccel, 4);						p += 4;

					if(bHeightWidth) {
						memcpy(p, &blob->second.boundingRect.width, 4);		p += 4;
						memcpy(p, &blob->second.boundingRect.height, 4);	p += 4;
					}
				}
			}
			// send blob data to clients
			m_tcpServer.sendRawBytesToAll((const char*)buf, p-buf);
		}

		if(bFingers) {
			uchar buf[1024*8];
			uchar *p = buf;
			// Add "CCV" as a data header
			*p++ = 'C';	*p++ = 'C';	*p++ = 'V';	*p++ = '\0';
			if(fingerBlobs->size() == 0){
				memset(p, 0, 4);
				p += 4;
			} else {
				int count = 0;
				map<int, Blob>::iterator blob;
				// count the blobs that are non (0,0)
				for(blob = fingerBlobs->begin(); blob != fingerBlobs->end(); blob++) {
					// omit point (0,0) since this means that we are outside of the range
					if(blob->second.centroid.x == 0 && blob->second.centroid.y == 0)
						continue;
					count++;
				}
				// send blob count first
				memcpy(p, &count, 4);	p += 4;
				// send blob information
				for(blob = fingerBlobs->begin(); blob != fingerBlobs->end(); blob++) {
					// omit point (0,0) since this means that we are outside of the range
					if(blob->second.centroid.x == 0 && blob->second.centroid.y == 0)
						continue;

					memcpy(p, &blob->second.id, 4);							p += 4;
					memcpy(p, &blob->second.centroid.x, 4);					p += 4;
					memcpy(p, &blob->second.centroid.y, 4);					p += 4;
					memcpy(p, &blob->second.D.x, 4);						p += 4;
					memcpy(p, &blob->second.D.y, 4);						p += 4;
					memcpy(p, &blob->second.maccel, 4);						p += 4;

					if(bHeightWidth) {
						memcpy(p, &blob->second.boundingRect.width, 4);		p += 4;
						memcpy(p, &blob->second.boundingRect.height, 4);	p += 4;
					}
				}
			}
			// send blob data to clients
			m_tcpServer.sendRawBytesToAll((const char*)buf, p-buf);
		}

		// bObjects ??????

	}
}
