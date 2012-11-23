
/*
 *  ofxKCoreVision.h
 *  based on ofxNCoreVision.h
 *  Based on NUI Group Community Core Vision
 *
 *  Created by NUI Group Dev Team A on 2/1/09.
 *  Copyright 2009 NUI Group/Inc. All rights reserved.
 *
 */
#ifndef _ofxKCoreVision_H
#define _ofxKCoreVision_H

//Main
#include "ofMain.h"
//Addons

#include "ofxOpenCv.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"

// Kinect
#include "ofxKinect.h"

// Our Addon
#include "ofxKCore.h"

// height and width of the source/tracked draw window
#define MAIN_WINDOW_WIDTH  320.0f
#define MAIN_WINDOW_HEIGHT 240.0f

class ofxKCoreVision : public ofxGuiListener{

// ofxGUI setup stuff
enum {
		propertiesPanel,
		propertiesPanel_flipV,
		propertiesPanel_flipH,
		propertiesPanel_pressure,

		optionPanel,
		optionPanel_tuio_osc,
		optionPanel_tuio_tcp,
		optionPanel_bin_tcp,
		optionPanel_tuio_height_width,

		calibrationPanel,
		calibrationPanel_calibrate,
		calibrationPanel_warp,

		sourcePanel,

		TemplatePanel,
		TemplatePanel_minArea,
		TemplatePanel_maxArea,

		backgroundPanel,
		backgroundPanel_remove,
		backgroundPanel_dynamic,
		backgroundPanel_learn_rate,

		smoothPanel,
		smoothPanel_use,
		smoothPanel_smooth,

		amplifyPanel,
		amplifyPanel_use,
		amplifyPanel_amp,

		highpassPanel,
		highpassPanel_use,
		highpassPanel_blur,
		highpassPanel_noise,

		trackedPanel,
		trackedPanel_darkblobs,
		trackedPanel_use,
		trackedPanel_threshold,
		trackedPanel_min_movement,
		trackedPanel_min_blob_size,
		trackedPanel_max_blob_size,
		trackedPanel_outlines,
		trackedPanel_ids,
		trackedPanel_hullPress,

		trackingPanel, //Panel for selecting what to track-Fingers, Objects or Fiducials
		trackingPanel_trackBlobs,
		trackingPanel_trackFingers,
		trackingPanel_trackObjects,

		savePanel,
		kParameter_SaveXml,
		kParameter_File,
		kParameter_LoadTemplateXml,
		kParameter_SaveTemplateXml,
	};

public:
    
	ofxKCoreVision(bool debug = true){
        ofAddListener(ofEvents().mousePressed, this, &ofxKCoreVision::_mousePressed);
        ofAddListener(ofEvents().mouseDragged, this, &ofxKCoreVision::_mouseDragged);
        ofAddListener(ofEvents().mouseReleased, this, &ofxKCoreVision::_mouseReleased);
        ofAddListener(ofEvents().keyPressed, this, &ofxKCoreVision::_keyPressed);
        ofAddListener(ofEvents().keyReleased, this, &ofxKCoreVision::_keyReleased);
        ofAddListener(ofEvents().setup, this, &ofxKCoreVision::_setup);
        ofAddListener(ofEvents().update, this, &ofxKCoreVision::_update);
        ofAddListener(ofEvents().draw, this, &ofxKCoreVision::_draw);
        ofAddListener(ofEvents().exit, this, &ofxKCoreVision::_exit);
        
        debugMode = debug;
        
        //  initialize filter
        //
        filter = NULL;
        
        //  fps and dsp calculation
        //
        frames          = 0;
        fps             = 0;
        lastFPSlog      = 0;
        differenceTime  = 0;
        
        //  ints/floats
        //
        backgroundLearnRate = .01;
        MIN_BLOB_SIZE       = 2;
        MAX_BLOB_SIZE       = 100;
        hullPress           = 20;
        pointSelected       = -1;
        
        //  Kinect Camera
        //
        camWidth            = 640;
        camHeight           = 480;
        srcPoints[0] = dstPoints[0] = ofPoint(0,0);
        srcPoints[1] = dstPoints[1] = ofPoint(camWidth,0);
        srcPoints[2] = dstPoints[2] = ofPoint(camWidth,camHeight);
        srcPoints[3] = dstPoints[3] = ofPoint(0,camHeight);
        
        //  bools
        //
        bCalibration        = 0;
        bFullscreen         = 0;
        bShowLabels         = 1;
        bMiniMode           = 0;
        bDrawOutlines       = 1;
        bTUIOMode           = 0;
        showConfiguration   = 0;
        
        contourFinder.bTrackBlobs   =   false;
        contourFinder.bTrackFingers =   false;
        contourFinder.bTrackObjects =   false;
        
        //  if auto tracker is defined then the tracker automagically comes up
        //  on startup..
#ifdef STANDALONE
        bStandaloneMode = true;
#else
        bStandaloneMode = false;
#endif
    }
    
    ~ofxKCoreVision(){
        delete filter;
        filter = NULL;
        kinect.close();
    }
    
	//  Load/save settings
    //
	bool loadXMLSettings();
	bool saveXMLSettings();

	//  Getters
    //
	map<int, Blob> getBlobs();
	map<int, Blob> getFingers();
	map<int, Blob> getObjects();

private:
    //  Events
    //
    void    _setup(ofEventArgs &e);
    void    _update(ofEventArgs &e);
	void    _draw(ofEventArgs &e);
    void    _exit(ofEventArgs &e);
    void    _mousePressed(ofMouseEventArgs &e);
    void    _mouseDragged(ofMouseEventArgs &e);
    void    _mouseReleased(ofMouseEventArgs &e);
    void    _keyPressed(ofKeyEventArgs &e);
    void    _keyReleased(ofKeyEventArgs &e);
    
    //  GUI
    //
	void    setupControls();
	void    handleGui(int parameterId, int task, void* data, int length);
	ofxGui* controls;
    
    //  Drawing
    //
	void drawOutlines();
	void drawMiniMode();
	void drawFullMode();
    
    //  Fonts
    //
	ofTrueTypeFont		verdana;
	ofTrueTypeFont      sidebarTXT;
	ofTrueTypeFont		bigvideo;
    
	//  Images
    //
	ofImage				background;
    
	//  Blob Tracker
    //
	BlobTracker			tracker;
    
    //  Kinect Device
    //
	ofxKinect           kinect;
	int					nearThreshold;
	int					farThreshold;

	//  Debug mode variables
    //
	bool				debugMode;

	//  FPS variables
    //
	int 				frames;
	int  				fps;
	float				lastFPSlog;
	int					differenceTime;

	//  Template Utilities
    //
	TemplateUtils		templates;

	//  Template Registration
    //
	ofRectangle			rect;
	ofRectangle			minRect;
	ofRectangle			maxRect;

	//  Object Selection bools
    //
	bool				isSelecting;
    
	string				videoFileName;

	int					maxBlobs;

	// The variable which will check the initilisation of camera
	//to avoid multiple initialisation
	bool				cameraInited;

	//  Calibration
    //
    Calibration			calib;

	//  Blob Finder
    //
	ContourFinder		contourFinder;

	//  Image filters
    //
	Filters*			filter;
	CPUImageFilter      processedImg;
	ofxCvGrayscaleImage	sourceImg;

	//  XML Settings Vars
    //
	string				message;

	//  Communication
    //
	TUIO				myTUIO;
	string				tmpLocalHost;
    int					tmpPort;
	int					tmpFlashPort;

	//  Logging
    //
	char				dateStr [9];
	char				timeStr [9];
	time_t				rawtime;
	struct tm *			timeinfo;
	char				fileName [80];
	FILE *				stream ;
    
    //  Variables in config.xml Settings file
	//
    ofPoint             srcPoints[4];
    ofPoint             dstPoints[4];
    int                 pointSelected;
	float				backgroundLearnRate;
    float				hullPress;          //  For finger detection
	int 				frameseq;
	int 				threshold;
	int					wobbleThreshold;
	int 				camWidth;
	int 				camHeight;
	int					winWidth;
	int					winHeight;
	int					MIN_BLOB_SIZE;
	int					MAX_BLOB_SIZE;
	int					minTempArea;        //  Area Slider
	int					maxTempArea;        //  Area Slider
	bool				showConfiguration;
	bool  				bMiniMode;
	bool				bShowInterface;
	bool				bShowPressure;
	bool				bDrawOutlines;
	bool				bTUIOMode;
	bool  				bFullscreen;
	bool 				bCalibration;
	bool				bShowLabels;
	bool				bNewFrame;
	bool				bAutoBackground;    //  Filters
	bool                bStandaloneMode;
};
#endif
