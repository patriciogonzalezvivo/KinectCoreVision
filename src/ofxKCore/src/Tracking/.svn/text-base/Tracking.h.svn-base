/*
 *  Tracking.h
 *
 *  Created by Ramsin Khoshabeh on 5/4/08.
 *  Copyright 2008 risenparadigm. All rights reserved.
 *
 * Changelog:
 * 08/15/08 -- Fixed a major bug in the track algorithm
 */

#ifndef _TRACKING_H
#define _TRACKING_H

#include <list>
#include <map>

#include "ofxFiducial.h"
#include "ContourFinder.h"
#include "ofxFiducialTracker.h"
#include "../Events/TouchMessenger.h"
#include "../Calibration/CalibrationUtils.h"

class BlobTracker : public TouchListener
{
public:
	BlobTracker();
	~BlobTracker();
	//assigns IDs to each blob in the contourFinder
	void track(ContourFinder* newBlobs);
	void passInCalibration(CalibrationUtils* calibrate);
	void passInFiducialInfo(ofxFiducialTracker*	_fidfinder);
	void doFiducialCalculation();

	ofxFiducialTracker*	fidfinder;

	CalibrationUtils* calibrate;
	bool isCalibrating;
	int MOVEMENT_FILTERING;
	std::map<int, Blob> getTrackedBlobs();
	std::map<int, Blob> getTrackedObjects();

private:
	int trackKnn(ContourFinder *newBlobs, Blob *track, int k, double thresh);
	int						IDCounter;	  //counter of last blob
	int						fightMongrel;
	std::vector<Blob>		trackedBlobs; //tracked blobs
	std::map<int, Blob>     calibratedBlobs;

	std::map<int,Blob>		trackedObjects;
	std::map<int, Blob>		calibratedObjects;

};

#endif
