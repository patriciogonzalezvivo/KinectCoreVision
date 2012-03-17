/*
*  Calibration.h
*  
*
*  Created on 2/2/09.
*  Copyright 2009 NUI Group. All rights reserved.
*
*/

#ifndef CALIBRATION_H
#define CALIBRATION_H

#include "ofxXmlSettings.h" // LOAD CONFIG.XML
#include "ofMain.h"
#include "CalibrationUtils.h"
#include "../Events/TouchMessenger.h"
#include "../Tracking/ContourFinder.h"
#include "../Tracking/Tracking.h"

class Calibration : public TouchListener {

	public:

		Calibration() {
			TouchEvents.addRAWListener(this);
            ofAddListener(ofEvents().keyPressed, this, &Calibration::_keyPressed);
            ofAddListener(ofEvents().keyReleased, this, &Calibration::_keyReleased);
			calibrating = false;
			bShowTargets = true;
			bW			= false;
			bA			= false;
			bS			= false;
			bD			= false;
			targetColor = 0xFF0000;
			arcAngle    = 0;
		}

		//Basic Methods
		void setup(int _camWidth, int _camHeight, BlobTracker *trackerIn);
		//Key Events
		void _keyPressed(ofKeyEventArgs &e);
		void _keyReleased(ofKeyEventArgs &e);
        //Touch Events
		void RAWTouchDown( Blob b );
		void RAWTouchMoved( Blob b );
		void RAWTouchUp( Blob b );
		void RAWTouchHeld( Blob b);
		//other
        void doCalibration();
		void passInContourFinder(int numBlobs, vector<Blob> blobs);
        void passInTracker(BlobTracker *trackerIn);

		bool                calibrating;

	private:
		
		void drawFingerOutlines();
		void drawCalibrationBlobs();
		void drawCalibrationPointsAndBox();
		void saveConfiguration();
        void DrawCircleLoader(double xctr, double yctr, double radius, double startAngle, double endAngle);

        bool			bW;
		bool			bS;
		bool			bA;
		bool			bD;
		bool			bShowTargets;
        int 			camWidth;
		int 			camHeight;
		float           arcAngle;
		float			targetColor;
		//Fonts
		ofTrueTypeFont	verdana;
		ofTrueTypeFont	calibrationText;
		//Draw Particle Image
		ofImage			calibrationParticle;		
		//Blob Tracker
		BlobTracker*	tracker;
		CalibrationUtils calibrate;
		ContourFinder	contourFinder;
		ofxXmlSettings	calibrationXML;
};

#endif
