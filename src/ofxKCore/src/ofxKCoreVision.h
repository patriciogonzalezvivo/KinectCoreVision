
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
//#include "ofxDirList.h"
//#include "ofxNetwork.h"
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
	ofxKCoreVision(bool debug)
	{
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

		//initialize filter
		filter = NULL;

		//fps and dsp calculation
		frames		= 0;
		fps			= 0;
		lastFPSlog	= 0;
		differenceTime = 0;

		//bools
		bCalibration= 0;
		bFullscreen = 0;
		bShowLabels = 1;
		bMiniMode = 0;
		bDrawOutlines = 1;
		bGPUMode = 0;
		bTUIOMode = 0;

		showConfiguration = 0;

		//Kinect Camera
		camRate = 30;
		camWidth = 320*2;
		camHeight = 240*2;

		//ints/floats
		backgroundLearnRate = .01;
		MIN_BLOB_SIZE = 2;
		MAX_BLOB_SIZE = 100;
		hullPress = 20;

		contourFinder.bTrackBlobs=false;
		contourFinder.bTrackFingers=false;
		contourFinder.bTrackObjects=false;

        //if auto tracker is defined then the tracker automagically comes up
        //on startup..
        #ifdef STANDALONE
            bStandaloneMode = true;
        #else
            bStandaloneMode = false;
        #endif
	}

	~ofxKCoreVision(){
		// AlexP
		// C++ guarantees that operator delete checks its argument for null-ness
		delete filter;		filter = NULL;
		kinect.close();
	}

	/****************************************************************
	 *						Public functions
	 ****************************************************************/
	//Basic Events called every frame
    void _setup(ofEventArgs &e);
    void _update(ofEventArgs &e);
	void _draw(ofEventArgs &e);
    void _exit(ofEventArgs &e);
    //Mouse Events
    void _mousePressed(ofMouseEventArgs &e);
    void _mouseDragged(ofMouseEventArgs &e);
    void _mouseReleased(ofMouseEventArgs &e);
    //Key Events
    void _keyPressed(ofKeyEventArgs &e);
    void _keyReleased(ofKeyEventArgs &e);

	//GUI
	void setupControls();
	void handleGui(int parameterId, int task, void* data, int length);
	ofxGui*		controls;

	//image processing stuff
	void initDevice();
	void getPixels();
	void grabFrameToCPU();
	void grabFrameToGPU(GLuint target);

	//drawing
	void drawFingerOutlines();
	void drawMiniMode();
	void drawFullMode();

	//Load/save settings
	void loadXMLSettings();
	void saveSettings();

	//Getters
	map<int, Blob> getBlobs();
	map<int, Blob> getFingers();
	map<int, Blob> getObjects();

	/***************************************************************
	 *					Kinect Capture Device
	 ***************************************************************/
	ofxKinect           kinect;

	int					nearThreshold;
	int					farThreshold;

	/****************************************************************
	 *            Variables in config.xml Settings file
	 *****************************************************************/
	int 				frameseq;
	int 				threshold;
	int					wobbleThreshold;
	int 				camRate;
	int 				camWidth;
	int 				camHeight;
	int					winWidth;
	int					winHeight;
	int					MIN_BLOB_SIZE;
	int					MAX_BLOB_SIZE;
	float				backgroundLearnRate;

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
	//filters
	bool				bAutoBackground;
	//modes
	bool				bGPUMode;

	//Area slider variables
	int					minTempArea;
	int					maxTempArea;
	float				hullPress;

	bool                bStandaloneMode;

	/****************************************************
	 *End config.xml variables
	 *****************************************************/

	//Debug mode variables
	bool				debugMode;

	//Undistortion of Image - Required for some setups
	bool				bUndistort;
	ofxCvGrayscaleImage	undistortedImg;

	//FPS variables
	int 				frames;
	int  				fps;
	float				lastFPSlog;
	int					differenceTime;

	//Fonts
	ofTrueTypeFont		verdana;
	ofTrueTypeFont      sidebarTXT;
	ofTrueTypeFont		bigvideo;

	//Images
	ofImage				background;

	//Blob Tracker
	BlobTracker			tracker;

	//Template Utilities
	TemplateUtils		templates;

	//Template Registration
	ofRectangle			rect;
	ofRectangle			minRect;
	ofRectangle			maxRect;

	//Object Selection bools
	bool				isSelecting;

	//Area sliders
    /****************************************************************
	 *						Private Stuff
	 ****************************************************************/
	string				videoFileName;

	int					maxBlobs;

	// The variable which will check the initilisation of camera
	//to avoid multiple initialisation
	bool				cameraInited;

	//Calibration
    Calibration			calib;

	//Blob Finder
	ContourFinder		contourFinder;

	//Image filters
	Filters*			filter;
	CPUImageFilter      processedImg;
	ofxCvGrayscaleImage	sourceImg;

	//XML Settings Vars
	ofxXmlSettings		XML;
	string				message;

	//Communication
	TUIO				myTUIO;
	string				tmpLocalHost;
    int					tmpPort;
	int					tmpFlashPort;

	//Logging
	char				dateStr [9];
	char				timeStr [9];
	time_t				rawtime;
	struct tm *			timeinfo;
	char				fileName [80];
	FILE *				stream ;
};
#endif
