/*
*  ofxKCoreVision.cpp
*  based on ofxNCoreVision.cpp
*  NUI Group Community Core Vision
*
*  Created by NUI Group Dev Team A on 2/1/09.
*  Copyright 2009 NUI Group. All rights reserved.
*
*/

#include "ofxKCoreVision.h"
#include "Controls/gui.h"

/******************************************************************************
* The setup function is run once to perform initializations in the application
*****************************************************************************/
void ofxKCoreVision::_setup(ofEventArgs &e){
	grayImage.allocate(kinect.width, kinect.height);
	sourceImg.allocate(kinect.width, kinect.height);
	grayThresh.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
	
	nearThreshold = 50;
	farThreshold  = 180;
	
	
	//set the title
	ofSetWindowTitle("Kinect Vision based on CCV v 1.4");

	//create filter
	if(filter == NULL)	filter = new ProcessFilters();
	//if ( filter_fiducial == NULL ){filter_fiducial = new ProcessFilters();}

	//Load Settings from config.xml file
	loadXMLSettings();

	if(debugMode){
		printf("DEBUG MODE : Printing to File\n");
		/*****************************************************************************************************
		* LOGGING
		******************************************************************************************************/
		/* alright first we need to get time and date so our logs can be ordered */
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		strftime (fileName,80,"../logs/log_%B_%d_%y_%H_%M_%S.txt",timeinfo);
		FILE *stream ;
		sprintf(fileName, ofToDataPath(fileName).c_str());
		if((stream = freopen(fileName, "w", stdout)) == NULL){}
		/******************************************************************************************************/
	}

	cameraInited = false;

	//Setup Window Properties
	ofSetWindowShape(winWidth,winHeight);
	ofSetVerticalSync(false);	            //Set vertical sync to false for better performance?

	//printf("Application Loaded...\n?");

	//load camera/video
	initDevice();
	printf("Kinect Initialised...\n");

	//set framerate
	ofSetFrameRate(camRate * 1.3);			//This will be based on camera fps in the future

	/*****************************************************************************************************
	* Allocate images (needed for drawing/processing images)
	******************************************************************************************************/
	processedImg.allocate(camWidth, camHeight); //main Image that'll be processed.
	processedImg.setUseTexture(false);			//We don't need to draw this so don't create a texture
	sourceImg.allocate(camWidth, camHeight);    //Source Image
	sourceImg.setUseTexture(false);				//We don't need to draw this so don't create a texture

	//Fiducial Images
	//processedImg_fiducial.allocate(camWidth, camHeight); //main Image that'll be processed.
	//processedImg_fiducial.setUseTexture(false);                        //We don't need to draw this so don't create a texture
	undistortedImg.allocate(camWidth, camHeight);
	/******************************************************************************************************/

	//Fonts - Is there a way to dynamically change font size?
	verdana.loadFont("verdana.ttf", 8, true, true);	   //Font used for small images

	//Static Images
	background.loadImage("images/background.jpg"); //Main (Temp?) Background
	//GUI Controls
	controls = ofxGui::Instance(this);
	setupControls();

	//printf("Controls Loaded...\n");

	//Setup Calibration
	calib.setup(camWidth, camHeight, &tracker);

	//Allocate Filters
	filter->allocate( camWidth, camHeight );
	//filter_fiducial->allocate( camWidth, camHeight );

	//Fiducial Initialisation

	// factor for Fiducial Drawing. The ImageSize is hardcoded 320x240 Pixel!(Look at ProcessFilters.h at the draw() Method
	//fiducialDrawFactor_Width = 320 / static_cast<float>(filter->camWidth);//camWidth;
	//fiducialDrawFactor_Height = 240 / static_cast<float>(filter->camHeight);//camHeight;


	/*****************************************************************************************************
	* Startup Modes
	******************************************************************************************************/
	//If Standalone Mode (not an addon)
	if (bStandaloneMode)
	{
		printf("Starting in standalone mode...\n\n");
		showConfiguration = true;
	}
	if (bMiniMode)
	{
		showConfiguration = true;
		bShowInterface = false;
		printf("Starting in Mini Mode...\n\n");
		ofSetWindowShape(190, 200); //minimized size
		filter->bMiniMode = bMiniMode;
	}
	else{
		bShowInterface = true;
		printf("Starting in full mode...\n\n");
	}

	//If Object tracking activated
	if(contourFinder.bTrackObjects)
	{
		templates.loadTemplateXml();
	}

	contourFinder.setTemplateUtils(&templates);
	//tracker.passInFiducialInfo(&fidfinder);

	printf("Community Core Vision is setup!\n\n");
}

/****************************************************************
*	Load/Save config.xml file Settings
****************************************************************/
void ofxKCoreVision::loadXMLSettings()
{
	// TODO: a seperate XML to map keyboard commands to action
	message = "Loading config.xml...";
	// Can this load via http?
	if ( XML.loadFile("config.xml"))
		message = "Settings Loaded!\n\n";
	else
		message = "No Settings Found...\n\n"; //FAIL

	//--------------------------------------------------------------
	//  START BINDING XML TO VARS
	//--------------------------------------------------------------
	winWidth					= XML.getValue("CONFIG:WINDOW:WIDTH", 950);
	winHeight					= XML.getValue("CONFIG:WINDOW:HEIGHT", 600);
	maxBlobs					= XML.getValue("CONFIG:BLOBS:MAXNUMBER", 20);
	bShowLabels					= XML.getValue("CONFIG:BOOLEAN:LABELS",0);
	bDrawOutlines				= XML.getValue("CONFIG:BOOLEAN:OUTLINES",0);
	bUndistort					= XML.getValue("CONFIG:BOOLEAN:UNDISTORT", 0);
	filter->bLearnBakground		= XML.getValue("CONFIG:BOOLEAN:LEARNBG",0);
	filter->bVerticalMirror		= XML.getValue("CONFIG:BOOLEAN:VMIRROR",0);
	filter->bHorizontalMirror	= XML.getValue("CONFIG:BOOLEAN:HMIRROR",0);

	
	nearThreshold				= XML.getValue("CONFIG:KINECT:NEAR",0);
	farThreshold				= XML.getValue("CONFIG:KINECT:FAR",100);
	angle						= XML.getValue("CONFIG:KINECT:ANGLE",0);
	
	//Filters
	filter->bTrackDark			= XML.getValue("CONFIG:BOOLEAN:TRACKDARK", 0);
	filter->bHighpass			= XML.getValue("CONFIG:BOOLEAN:HIGHPASS",1);
	filter->bAmplify			= XML.getValue("CONFIG:BOOLEAN:AMPLIFY", 1);
	filter->bSmooth				= XML.getValue("CONFIG:BOOLEAN:SMOOTH", 1);
	filter->bDynamicBG			= XML.getValue("CONFIG:BOOLEAN:DYNAMICBG", 1);
	//MODES
	bGPUMode					= XML.getValue("CONFIG:BOOLEAN:GPU", 0);
	bMiniMode                   = XML.getValue("CONFIG:BOOLEAN:MINIMODE",0);
	//CONTROLS
	tracker.MOVEMENT_FILTERING	= XML.getValue("CONFIG:INT:MINMOVEMENT",0);
	MIN_BLOB_SIZE				= XML.getValue("CONFIG:INT:MINBLOBSIZE",2);
	MAX_BLOB_SIZE				= XML.getValue("CONFIG:INT:MAXBLOBSIZE",100);
	backgroundLearnRate			= XML.getValue("CONFIG:INT:BGLEARNRATE", 0.01f);
	//Filter Settings
	filter->threshold			= XML.getValue("CONFIG:INT:THRESHOLD",0);
	filter->highpassBlur		= XML.getValue("CONFIG:INT:HIGHPASSBLUR",0);
	filter->highpassNoise		= XML.getValue("CONFIG:INT:HIGHPASSNOISE",0);
	filter->highpassAmp			= XML.getValue("CONFIG:INT:HIGHPASSAMP",0);
	filter->smooth				= XML.getValue("CONFIG:INT:SMOOTH",0);
	minTempArea					= XML.getValue("CONFIG:INT:MINTEMPAREA",0);
	maxTempArea					= XML.getValue("CONFIG:INT:MAXTEMPAREA",0);
	//Tracking Options
	contourFinder.bTrackFingers				= XML.getValue("CONFIG:BOOLEAN:TRACKFINGERS",0);
	contourFinder.bTrackObjects				= XML.getValue("CONFIG:BOOLEAN:TRACKOBJECTS",0);
	//contourFinder.bTrackFiducials			= XML.getValue("CONFIG:BOOLEAN:TRACKFIDUCIALS",0);

	//NETWORK SETTINGS
	bTUIOMode					= XML.getValue("CONFIG:BOOLEAN:TUIO",0);
	myTUIO.bOSCMode				= XML.getValue("CONFIG:BOOLEAN:OSCMODE",1);
	myTUIO.bTCPMode				= XML.getValue("CONFIG:BOOLEAN:TCPMODE",1);
	myTUIO.bBinaryMode			= XML.getValue("CONFIG:BOOLEAN:BINMODE",1);
	myTUIO.bHeightWidth			= XML.getValue("CONFIG:BOOLEAN:HEIGHTWIDTH",0);
	tmpLocalHost				= XML.getValue("CONFIG:NETWORK:LOCALHOST", "localhost");
	tmpPort						= XML.getValue("CONFIG:NETWORK:TUIOPORT_OUT", 3333);
	tmpFlashPort				= XML.getValue("CONFIG:NETWORK:TUIOFLASHPORT_OUT", 3000);
	myTUIO.setup(tmpLocalHost.c_str(), tmpPort, tmpFlashPort); //have to convert tmpLocalHost to a const char*
	//--------------------------------------------------------------
	//  END XML SETUP

	//Filter for Fiducial setup
	/*filter_fiducial->bLearnBackground        = false;
	filter_fiducial->bVerticalMirror        = filter->bVerticalMirror;
	filter_fiducial->bHorizontalMirror        = filter->bHorizontalMirror;
	filter_fiducial->bTrackDark               = filter->bTrackDark;
//^^ did not want to hardcode this , but these will not be any use of this.

	filter_fiducial->bHighpass				= XML.getValue("CONFIG:FIDUCIAL:HIGHPASS", 0);
	filter_fiducial->bAmplify				= XML.getValue("CONFIG:FIDUCIAL:AMPLIFY", 0);
	filter_fiducial->bSmooth				= XML.getValue("CONFIG:FIDUCIAL:SMOOTH", 0);

	filter_fiducial->threshold				= XML.getValue("CONFIG:FIDUCIAL:THRESHOLD", 0);
	filter_fiducial->highpassBlur			= XML.getValue("CONFIG:FIDUCIAL:HIGHPASSBLUR", 0);
	filter_fiducial->highpassNoise			= XML.getValue("CONFIG:FIDUCIAL:HIGHPASSNOISE", 0);
	filter_fiducial->highpassAmp			= XML.getValue("CONFIG:FIDUCIAL:HIGHPASSAMP", 0);
	filter_fiducial->smooth					= XML.getValue("CONFIG:FIDUCIAL:SMOOTHVALUE", 0);
	 */
}

void ofxKCoreVision::saveSettings(){
	XML.setValue("CONFIG:KINECT:NEAR", nearThreshold);
	XML.setValue("CONFIG:KINECT:FAR", farThreshold);
	XML.setValue("CONFIG:KINECT:ANGLE", angle);
	
	XML.setValue("CONFIG:BOOLEAN:PRESSURE",bShowPressure);
	XML.setValue("CONFIG:BOOLEAN:LABELS",bShowLabels);
	XML.setValue("CONFIG:BOOLEAN:OUTLINES",bDrawOutlines);
	XML.setValue("CONFIG:BOOLEAN:UNDISTORT",bUndistort);
	XML.setValue("CONFIG:BOOLEAN:LEARNBG", filter->bLearnBakground);
	XML.setValue("CONFIG:BOOLEAN:VMIRROR", filter->bVerticalMirror);
	XML.setValue("CONFIG:BOOLEAN:HMIRROR", filter->bHorizontalMirror);
	XML.setValue("CONFIG:BOOLEAN:TRACKDARK", filter->bTrackDark);
	XML.setValue("CONFIG:BOOLEAN:HIGHPASS", filter->bHighpass);
	XML.setValue("CONFIG:BOOLEAN:AMPLIFY", filter->bAmplify);
	XML.setValue("CONFIG:BOOLEAN:SMOOTH", filter->bSmooth);
	XML.setValue("CONFIG:BOOLEAN:DYNAMICBG", filter->bDynamicBG);
	XML.setValue("CONFIG:INT:MINMOVEMENT", tracker.MOVEMENT_FILTERING);
	XML.setValue("CONFIG:INT:MINBLOBSIZE", MIN_BLOB_SIZE);
	XML.setValue("CONFIG:INT:MAXBLOBSIZE", MAX_BLOB_SIZE);
	XML.setValue("CONFIG:INT:BGLEARNRATE", backgroundLearnRate);
	XML.setValue("CONFIG:INT:THRESHOLD", filter->threshold);
	XML.setValue("CONFIG:INT:HIGHPASSBLUR", filter->highpassBlur);
	XML.setValue("CONFIG:INT:HIGHPASSNOISE", filter->highpassNoise);
	XML.setValue("CONFIG:INT:HIGHPASSAMP", filter->highpassAmp);
	XML.setValue("CONFIG:INT:SMOOTH", filter->smooth);
	//XML.setValue("CONFIG:INT:MINTEMPAREA", minTempArea);
	//XML.setValue("CONFIG:INT:MAXTEMPAREA", maxTempArea);
	XML.setValue("CONFIG:BOOLEAN:MINIMODE", bMiniMode);
	XML.setValue("CONFIG:BOOLEAN:TUIO",bTUIOMode);
	XML.setValue("CONFIG:BOOLEAN:TRACKFINGERS",contourFinder.bTrackFingers);
	XML.setValue("CONFIG:BOOLEAN:TRACKOBJECTS",contourFinder.bTrackObjects);
	//XML.setValue("CONFIG:BOOLEAN:TRACKFIDUCIALS",contourFinder.bTrackFiducials);
	XML.setValue("CONFIG:BOOLEAN:HEIGHTWIDTH", myTUIO.bHeightWidth);
	XML.setValue("CONFIG:BOOLEAN:OSCMODE", myTUIO.bOSCMode);
	XML.setValue("CONFIG:BOOLEAN:TCPMODE", myTUIO.bTCPMode);
	XML.setValue("CONFIG:BOOLEAN:BINMODE", myTUIO.bBinaryMode);

	//XML.setValue("CONFIG:FIDUCIAL:HIGHPASS", filter_fiducial->bHighpass);
	//XML.setValue("CONFIG:FIDUCIAL:AMPLIFY", filter_fiducial->bAmplify);
	//XML.setValue("CONFIG:FIDUCIAL:SMOOTH", filter_fiducial->bSmooth);

	//XML.setValue("CONFIG:FIDUCIAL:THRESHOLD", filter_fiducial->threshold);
	//XML.setValue("CONFIG:FIDUCIAL:HIGHPASSBLUR", filter_fiducial->highpassBlur);
	//XML.setValue("CONFIG:FIDUCIAL:HIGHPASSNOISE", filter_fiducial->highpassNoise);
	//XML.setValue("CONFIG:FIDUCIAL:HIGHPASSAMP", filter_fiducial->highpassAmp);
	//XML.setValue("CONFIG:FIDUCIAL:SMOOTHVALUE", filter_fiducial->smooth);

	XML.saveFile("config.xml");
}

/************************************************
*				Init Device
************************************************/
//Init Device (camera/video)
void ofxKCoreVision::initDevice(){
	//save/update log file
	if(debugMode) if((stream = freopen(fileName, "a", stdout)) == NULL){}
	
	kinect.init();
	kinect.setVerbose(true);
	kinect.open();
	kinect.enableDepthNearValueWhite(false);
	
	cameraInited	=	true;
	camWidth		=	kinect.width;
	camHeight		=	kinect.height;
}

/******************************************************************************
* The update function runs continuously. Use it to update states and variables
*****************************************************************************/
void ofxKCoreVision::_update(ofEventArgs &e){
	if(debugMode) if((stream = freopen(fileName, "a", stdout)) == NULL){}
	
	kinect.update();
	bNewFrame = kinect.isFrameNew();
	
	if(!bNewFrame){
		return;			//if no new frame, return
	} else {			//else process camera frame
		ofBackground(0, 0, 0);

		// Calculate FPS of Camera
		frames++;
		float time = ofGetElapsedTimeMillis();
		if (time > (lastFPSlog + 1000)) {
			fps = frames;
			frames = 0;
			lastFPSlog = time;
		}//End calculation

		float beforeTime = ofGetElapsedTimeMillis();

		if (bGPUMode){
			grabFrameToGPU(filter->gpuSourceTex);
			filter->applyGPUFilters();
			contourFinder.findContours(filter->gpuReadBackImageGS,  (MIN_BLOB_SIZE * 2) + 1, ((camWidth * camHeight) * .4) * (MAX_BLOB_SIZE * .001), maxBlobs, false);

			//if(contourFinder.bTrackFiducials){
				//grabFrameToGPU(filter_fiducial->gpuSourceTex);
				//filter_fiducial->applyGPUFilters();
				//fidfinder.findFiducials( filter_fiducial->gpuReadBackImageGS );
			//}
		} else {
			grabFrameToCPU();
			filter->applyCPUFilters( processedImg );
			contourFinder.findContours(processedImg,  (MIN_BLOB_SIZE * 2) + 1, ((camWidth * camHeight) * .4) * (MAX_BLOB_SIZE * .001), maxBlobs, false);

			//if(contourFinder.bTrackFiducials){
			//	filter_fiducial->applyCPUFilters( processedImg_fiducial );
			//	fidfinder.findFiducials( processedImg_fiducial );
			//}
		}

		//If Object tracking or Finger tracking is enabled
		if(contourFinder.bTrackFingers || contourFinder.bTrackObjects)
			tracker.track(&contourFinder);

		//Map Fiducials from camera to screen position
		/*if(contourFinder.bTrackFiducials)
			tracker.doFiducialCalculation();*/

		//get DSP time
		differenceTime = ofGetElapsedTimeMillis() - beforeTime;

		//Dynamic Background subtraction LearRate
			if (filter->bDynamicBG){
			filter->fLearnRate = backgroundLearnRate * .0001; //If there are no blobs, add the background faster.
			if (contourFinder.nBlobs > 0) //If there ARE blobs, add the background slower.
				filter->fLearnRate = backgroundLearnRate * .0001;
		}//End Background Learning rate

		//Sending TUIO messages
		if (myTUIO.bOSCMode || myTUIO.bTCPMode || myTUIO.bBinaryMode){
			//printf("sending data osc : %d TCP : %d binary : %d\n", myTUIO.bOSCMode, myTUIO.bTCPMode, myTUIO.bBinaryMode);
			myTUIO.setMode(contourFinder.bTrackFingers , contourFinder.bTrackObjects);//, contourFinder.bTrackFiducials);
			myTUIO.sendTUIO(&getBlobs(),&getObjects());//,&fidfinder.fiducialsList);
		}
	}
}


/************************************************
*				Input Device Stuff
************************************************/
//Grab frame from CPU
void ofxKCoreVision::grabFrameToCPU(){
	sourceImg.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
	grayThreshFar = sourceImg;
	grayThresh = sourceImg;
	grayThreshFar.threshold(farThreshold, true);
	grayThresh.threshold(nearThreshold);
	cvAnd(grayThresh.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
	grayImage.flagImageChanged();

	//convert to grayscale
	processedImg = grayImage;
	sourceImg.mirror(filter->bVerticalMirror, filter->bHorizontalMirror);
	//if(contourFinder.bTrackFiducials){processedImg_fiducial = grayImage;}
	
}

//Grab frame from GPU
void ofxKCoreVision::grabFrameToGPU(GLuint target){
	//grab the frame to a raw openGL texture
	
	sourceImg.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
	grayThreshFar = sourceImg;
	grayThresh = sourceImg;
	grayThreshFar.threshold(farThreshold, true);
	grayThresh.threshold(nearThreshold);
	cvAnd(grayThresh.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
	
	glEnable(GL_TEXTURE_2D);
	//glPixelStorei(1);
	glBindTexture(GL_TEXTURE_2D, target);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, camWidth, camHeight, GL_RGB, GL_UNSIGNED_BYTE, grayImage.getPixels());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D,0);
	sourceImg.mirror(filter->bVerticalMirror, filter->bHorizontalMirror);
}


/******************************************************************************
* The draw function paints the textures onto the screen. It runs after update.
*****************************************************************************/
void ofxKCoreVision::_draw(ofEventArgs &e)
{
	if (showConfiguration){
		//if calibration
		if (bCalibration){
			//Don't draw main interface
			calib.passInContourFinder(contourFinder.nBlobs, contourFinder.blobs);
			calib.doCalibration();
		}
		//if mini mode
		else if (bMiniMode){
			drawMiniMode();
		}
		//if full mode
		else if (bShowInterface){
			drawFullMode();
			
			if(bDrawOutlines || bShowLabels) 
				drawFingerOutlines();
			
			/*if(contourFinder.bTrackFiducials)
				drawFiducials();*/

			if(contourFinder.bTrackObjects && isSelecting){
				ofNoFill();
				ofSetColor(255, 0, 0);
				ofRect(rect.x,rect.y,rect.width,rect.height);
				ofSetColor(0, 255, 0);
				ofRect(minRect.x,minRect.y,minRect.width, minRect.height);
				ofSetColor(0, 0, 255);
				ofRect(maxRect.x, maxRect.y, maxRect.width, maxRect.height);
			}
		}

		//draw gui controls
		if (!bCalibration && !bMiniMode) 
			controls->draw();
	}
}

void ofxKCoreVision::drawFullMode(){
	ofSetColor(255);
	//Draw Background Image
	background.draw(0,0);

	//Draw Image Filters To Screen
	if (bGPUMode)
		filter->drawGPU();
	else {
		sourceImg.draw(30, 15, 320, 240);
		
		//if(!bFidMode){
			filter->draw();
		//} else {
		//	filter_fiducial->draw();
		//}
	}

	ofSetColor(255);

	string str0 = "Accel: ";
	str0 += ofToString(kinect.getMksAccel().x,1) + "/" + ofToString(kinect.getMksAccel().y,1) + "/" + ofToString(kinect.getMksAccel().z,1) + "\n";
	
	string str1 = "Dist: ";
	str1 += ofToString(nearThreshold) + " <-> " +  ofToString(farThreshold) + "\n";
	string str2 = "Resolution: ";
	str2+= ofToString(camWidth, 0) + "x" + ofToString(camHeight, 0)  + "\n";
	string str3 = "FPS: ";
	str3+= ofToString(fps, 0)+"\n";

	string str4 = "Processing: ";
	str4+= ofToString(differenceTime, 0)+" ms \n";

	string str5 = "Filter: ";
	//if(!bFidMode)
		str5+= "Finger/Object\n";
	//else 
	//	str5+= "Fiducial\n";

	string str6 = "Blobs: ";
	str6+= ofToString(contourFinder.nBlobs,0)+", "+ofToString(contourFinder.nObjects,0)+"\n";
	
	ofColor c;
	c.setHex(0x969696);
	ofSetColor(c);
	verdana.drawString( str3+ str0 + str6 + str4 + str2 + str5 , 570, 430);

	
	//TUIO data drawing
		char buf[256]="";
		if(myTUIO.bOSCMode && myTUIO.bTCPMode)
			sprintf(buf, "Dual Mode");
		else if(myTUIO.bOSCMode)
			sprintf(buf, "Host: %s\nProtocol: UDP [OSC]\nPort: %i", myTUIO.localHost, myTUIO.TUIOPort);
		else if(myTUIO.bTCPMode){
			if(myTUIO.bIsConnected)
				sprintf(buf, "Host: %s\nProtocol: TCP [XML]\nPort: %i", myTUIO.localHost, myTUIO.TUIOFlashPort);
			else
				sprintf(buf, "Binding Error\nHost: %s\nProtocol: TCP [XML]\nPort: %i", myTUIO.localHost, myTUIO.TUIOFlashPort);
		}else if(myTUIO.bBinaryMode){
			if(myTUIO.bIsConnected)
				sprintf(buf, "Host: %s\nProtocol: Binary\nPort: %i", myTUIO.localHost, myTUIO.TUIOFlashPort);
			else
				sprintf(buf, "Binding Error\nHost: %s\nProtocol: Binary\nPort: %i", myTUIO.localHost, myTUIO.TUIOFlashPort);
		}

		ofSetColor(c);
		verdana.drawString(buf, 573, 515);

}

void ofxKCoreVision::drawMiniMode(){
	//black background
	ofSetColor(0,0,0);
	ofRect(0,0,ofGetWidth(), ofGetHeight());
	//draw outlines
	if (bDrawOutlines)
	{
		for (int i=0; i<contourFinder.nBlobs; i++)
			contourFinder.blobs[i].drawContours(0,0, camWidth, camHeight+175, ofGetWidth(), ofGetHeight());

		for (int i=0;i<contourFinder.nObjects; i++)
			contourFinder.objects[i].drawBox(0,0, camWidth, camHeight+175, ofGetWidth(), ofGetHeight());
	}

	//draw grey rectagles for text information
	ofSetColor(128,128,128);
	ofFill();
	ofRect(0,ofGetHeight() - 83, ofGetWidth(), 20);
	ofRect(0,ofGetHeight() - 62, ofGetWidth(), 20);
	ofRect(0,ofGetHeight() - 41, ofGetWidth(), 20);
	ofRect(0,ofGetHeight() - 20, ofGetWidth(), 20);

	//draw text
	ofSetColor(250,250,250);
	verdana.drawString("Calc. Time  [ms]:        " + ofToString(differenceTime,0),10, ofGetHeight() - 70 );
	verdana.drawString("Kinect [fps]:            " + ofToString(fps,0),10, ofGetHeight() - 50 );
	
	verdana.drawString("Blob Count:               " + ofToString(contourFinder.nBlobs,0),10, ofGetHeight() - 29 );
	verdana.drawString("Communication:  " ,10, ofGetHeight() - 9 );

	//draw green tuio circle
	if((myTUIO.bIsConnected || myTUIO.bOSCMode) && bTUIOMode)
		ofSetColor(0,255,0);	//green = connected
	else
		ofSetColor(255,0,0);	//red = not connected
	ofFill();
	ofCircle(ofGetWidth() - 17 , ofGetHeight() - 10, 5);
	ofNoFill();
}

void ofxKCoreVision::drawFingerOutlines()
{
	//Find the blobs for drawing
	if(contourFinder.bTrackFingers){
		for (int i=0; i<contourFinder.nBlobs; i++)
		{
			if (bDrawOutlines){
				//Draw contours (outlines) on the source image
				contourFinder.blobs[i].drawContours(30, 15, camWidth, camHeight, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
			}
			if (bShowLabels){ //Show ID label
				float xpos = contourFinder.blobs[i].centroid.x * (MAIN_WINDOW_WIDTH/camWidth);
				float ypos = contourFinder.blobs[i].centroid.y * (MAIN_WINDOW_HEIGHT/camHeight);

				ofSetColor(200,255,200);
				char idStr[1024];

				sprintf(idStr, "id: %i", contourFinder.blobs[i].id);

				verdana.drawString(idStr, xpos + 365, ypos + contourFinder.blobs[i].boundingRect.height/2 + 45);
			}
		}
	}
	//Object Drawing
	if(contourFinder.bTrackObjects){
		for (int i=0; i<contourFinder.nObjects; i++)
		{
			if (bDrawOutlines){
				//Draw contours (outlines) on the source image
				contourFinder.objects[i].drawBox(40, 30, camWidth, camHeight, MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);
			}
			if (bShowLabels){ //Show ID label
				float xpos = contourFinder.objects[i].centroid.x * (MAIN_WINDOW_WIDTH/camWidth);
				float ypos = contourFinder.objects[i].centroid.y * (MAIN_WINDOW_HEIGHT/camHeight);

				ofSetColor(200,255,200);
				char idStr[1024];

				sprintf(idStr, "id: %i", contourFinder.objects[i].id);

				verdana.drawString(idStr, xpos + 365, ypos + contourFinder.objects[i].boundingRect.height/2 + 45);
			}
		}
	}


	ofSetColor(255);
}

/*
void ofxKCoreVision::drawFiducials()
{
	for (list<ofxFiducial>::iterator fiducial = fidfinder.fiducialsList.begin(); fiducial != fidfinder.fiducialsList.end(); fiducial++)
	{
		fiducial->drawScaled(30,15,fiducialDrawFactor_Width,fiducialDrawFactor_Height);

		fiducial->drawCornersScaled( 30, 15 ,fiducialDrawFactor_Width,fiducialDrawFactor_Height);

		ofSetColor(0,0,255);
		ofSetColor(255,255,255);

	}
}*/

/*****************************************************************************
* KEY EVENTS
*****************************************************************************/
void ofxKCoreVision::_keyPressed(ofKeyEventArgs &e)
{
	if (showConfiguration){
		switch (e.key){
		case 'b':
			//if(!bFidMode){
			filter->bLearnBakground = true;
			//} else {
			//filter_fiducial->bLearnBackground = true;
			//}
			break;
		case 'o':
			bDrawOutlines ? bDrawOutlines = false : bDrawOutlines = true;
			controls->update(appPtr->trackedPanel_outlines, kofxGui_Set_Bool, &appPtr->bDrawOutlines, sizeof(bool));
			break;
		case 'h':
			filter->bHorizontalMirror ? filter->bHorizontalMirror = false : filter->bHorizontalMirror = true;
			//filter_fiducial->bHorizontalMirror ? filter_fiducial->bHorizontalMirror = false : filter_fiducial->bHorizontalMirror = true;
			controls->update(appPtr->propertiesPanel_flipH, kofxGui_Set_Bool, &appPtr->filter->bHorizontalMirror, sizeof(bool));
			break;
		case 'j':
			filter->bVerticalMirror ? filter->bVerticalMirror = false : filter->bVerticalMirror = true;
			//filter_fiducial->bVerticalMirror ? filter_fiducial->bVerticalMirror = false : filter_fiducial->bVerticalMirror = true;
			controls->update(appPtr->propertiesPanel_flipV, kofxGui_Set_Bool, &appPtr->filter->bVerticalMirror, sizeof(bool));
			break;
		case 't':
			myTUIO.bOSCMode = !myTUIO.bOSCMode;
			myTUIO.bTCPMode = false;
			myTUIO.bBinaryMode = false;
			bTUIOMode = myTUIO.bOSCMode;
			controls->update(appPtr->optionPanel_tuio_tcp, kofxGui_Set_Bool, &appPtr->myTUIO.bTCPMode, sizeof(bool));
			controls->update(appPtr->optionPanel_tuio_osc, kofxGui_Set_Bool, &appPtr->myTUIO.bOSCMode, sizeof(bool));
			controls->update(appPtr->optionPanel_bin_tcp, kofxGui_Set_Bool, &appPtr->myTUIO.bBinaryMode, sizeof(bool));
			//clear blobs
//			myTUIO.blobs.clear();
			break;
		case 'f':
			myTUIO.bOSCMode = false;
			myTUIO.bTCPMode = !myTUIO.bTCPMode;
			myTUIO.bBinaryMode = false;
			bTUIOMode = myTUIO.bTCPMode;
			controls->update(appPtr->optionPanel_tuio_tcp, kofxGui_Set_Bool, &appPtr->myTUIO.bTCPMode, sizeof(bool));
			controls->update(appPtr->optionPanel_tuio_osc, kofxGui_Set_Bool, &appPtr->myTUIO.bOSCMode, sizeof(bool));
			controls->update(appPtr->optionPanel_bin_tcp, kofxGui_Set_Bool, &appPtr->myTUIO.bBinaryMode, sizeof(bool));
			//clear blobs
//			myTUIO.blobs.clear();
			break;
		case 'n':
			myTUIO.bOSCMode = false;
			myTUIO.bTCPMode = false;
			myTUIO.bBinaryMode = !myTUIO.bBinaryMode;
			bTUIOMode = myTUIO.bBinaryMode;
			controls->update(appPtr->optionPanel_tuio_tcp, kofxGui_Set_Bool, &appPtr->myTUIO.bTCPMode, sizeof(bool));
			controls->update(appPtr->optionPanel_tuio_osc, kofxGui_Set_Bool, &appPtr->myTUIO.bOSCMode, sizeof(bool));
			controls->update(appPtr->optionPanel_bin_tcp, kofxGui_Set_Bool, &appPtr->myTUIO.bBinaryMode, sizeof(bool));
			//clear blobs
			//			myTUIO.blobs.clear();
			break;
		case 'l':
			bShowLabels ? bShowLabels = false : bShowLabels = true;
			controls->update(appPtr->trackedPanel_ids, kofxGui_Set_Bool, &appPtr->bShowLabels, sizeof(bool));
			break;
		case 'p':
			bShowPressure ? bShowPressure = false : bShowPressure = true;
			break;
		case ' ':
			if (bMiniMode && !bCalibration) // NEED TO ADD HERE ONLY GO MINI MODE IF NOT CALIBRATING
			{
				bMiniMode = false;
				bShowInterface = true;
				filter->bMiniMode = bMiniMode;
				//filter_fiducial->bMiniMode = bMiniMode;
				ofSetWindowShape(950,600); //default size
			}
			else if(!bCalibration)
			{
				bMiniMode = true;
				bShowInterface = false;
				filter->bMiniMode = bMiniMode;
				//filter_fiducial->bMiniMode = bMiniMode;
				ofSetWindowShape(190,200); //minimized size
			}
			break;
		case 'x': //Exit Calibrating
			if (bCalibration)
			{	bShowInterface = true;
			bCalibration = false;
			calib.calibrating = false;
			tracker.isCalibrating = false;
			if (bFullscreen == true) ofToggleFullscreen();
			bFullscreen = false;
			}
			break;
		case OF_KEY_RETURN: //Close Template Selection and save it
			if( contourFinder.bTrackObjects && isSelecting )
			{
			isSelecting = false;
			templates.addTemplate(rect,minRect,maxRect,camWidth/320,camHeight/240);
			rect = ofRectangle();
			minRect = rect;
			maxRect = rect;
			minTempArea = 0;
			maxTempArea = 0;
			controls->update(appPtr->TemplatePanel_minArea, kofxGui_Set_Float, &appPtr->minTempArea, sizeof(float));
			controls->update(appPtr->TemplatePanel_maxArea, kofxGui_Set_Float, &appPtr->maxTempArea, sizeof(float));
			}
			break;
		/*case 'i':
			bFidMode = !bFidMode;

			if(bFidMode){//Update the GUI with Fiducial Filter values
				//Smooth
				controls->update(appPtr->smoothPanel_use, kofxGui_Set_Bool, &appPtr->filter_fiducial->bSmooth, sizeof(bool));
				controls->update(appPtr->smoothPanel_smooth, kofxGui_Set_Float, &appPtr->filter_fiducial->smooth, sizeof(float));
				//Highpass
				controls->update(appPtr->highpassPanel_use, kofxGui_Set_Bool, &appPtr->filter_fiducial->bHighpass, sizeof(bool));
				controls->update(appPtr->highpassPanel_blur, kofxGui_Set_Float, &appPtr->filter_fiducial->highpassBlur, sizeof(float));
				controls->update(appPtr->highpassPanel_noise, kofxGui_Set_Float, &appPtr->filter_fiducial->highpassNoise, sizeof(float));
				//Amplify
				controls->update(appPtr->amplifyPanel_use, kofxGui_Set_Bool, &appPtr->filter_fiducial->bAmplify, sizeof(bool));
				controls->update(appPtr->amplifyPanel_amp, kofxGui_Set_Float, &appPtr->filter_fiducial->highpassAmp, sizeof(float));
				//Threshold
				controls->update(appPtr->trackedPanel_threshold, kofxGui_Set_Float, &appPtr->filter_fiducial->threshold, sizeof(float));
			} else {//Update the GUI with normal Filter values
				//Smooth
				controls->update(appPtr->smoothPanel_use, kofxGui_Set_Bool, &appPtr->filter->bSmooth, sizeof(bool));
				controls->update(appPtr->smoothPanel_smooth, kofxGui_Set_Float, &appPtr->filter->smooth, sizeof(float));
				//Highpass
				controls->update(appPtr->highpassPanel_use, kofxGui_Set_Bool, &appPtr->filter->bHighpass, sizeof(bool));
				controls->update(appPtr->highpassPanel_blur, kofxGui_Set_Float, &appPtr->filter->highpassBlur, sizeof(float));
				controls->update(appPtr->highpassPanel_noise, kofxGui_Set_Float, &appPtr->filter->highpassNoise, sizeof(float));
				//Amplify
				controls->update(appPtr->amplifyPanel_use, kofxGui_Set_Bool, &appPtr->filter->bAmplify, sizeof(bool));
				controls->update(appPtr->amplifyPanel_amp, kofxGui_Set_Float, &appPtr->filter->highpassAmp, sizeof(float));
				//Threshold
				controls->update(appPtr->trackedPanel_threshold, kofxGui_Set_Float, &appPtr->filter->threshold, sizeof(float));
			}
			//TODO:Update the GUI
			break;*/
		
			case '>':
			case '.':
				farThreshold ++;
				if (farThreshold > 255) farThreshold = 255;
				break;
			case '<':		
			case ',':		
				farThreshold --;
				if (farThreshold < 0) farThreshold = 0;
				break;
				
			case '+':
			case '=':
				nearThreshold ++;
				if (nearThreshold > 255) nearThreshold = 255;
				break;
			case '-':		
				nearThreshold --;
				if (nearThreshold < 0) nearThreshold = 0;
				break;
			/*case 'w':
				kinect.enableDepthNearValueWhite(!(kinect.isDepthNearValueWhite()));
				break;*/
				
			case OF_KEY_UP:
				angle++;
				if(angle>30) angle=30;
				kinect.setCameraTiltAngle(angle);
				break;
				
			case OF_KEY_DOWN:
				angle--;
				if(angle<-30) angle=-30;
				kinect.setCameraTiltAngle(angle);
				break;
				
		default: //Check key character <<<<===== Remove this
			//printf("%c",e.key);
			break;
		}
	}
}

void ofxKCoreVision::_keyReleased(ofKeyEventArgs &e)
{
	if (showConfiguration)
	{
		if ( e.key == 'c' && !bCalibration)
		{
			bShowInterface = false;
			// Enter/Exit Calibration
			bCalibration = true;
			calib.calibrating = true;
			tracker.isCalibrating = true;
			if (bFullscreen == false) ofToggleFullscreen();
			bFullscreen = true;
		}
	}
	if ( e.key == '~' || e.key == '`' && !bMiniMode && !bCalibration) showConfiguration = !showConfiguration;
}

/*****************************************************************************
*	MOUSE EVENTS
*****************************************************************************/
void ofxKCoreVision::_mouseDragged(ofMouseEventArgs &e)
{
	if (showConfiguration)
		controls->mouseDragged(e.x, e.y, e.button); //guilistener
	if(contourFinder.bTrackObjects)
	{
		if( e.x > 385 && e.x < 705 && e.y > 30 && e.y < 270 )
		{
			if( e.x < rect.x || e.y < rect.y )
			{
				rect.width = rect.x - e.x;
				rect.height = rect.y - e.y;

				rect.x = e.x;
				rect.y =  e.y;
			}
			else
			{
				rect.width = e.x - rect.x;
				rect.height = e.y - rect.y;
			}
		}
	}
}

void ofxKCoreVision::_mousePressed(ofMouseEventArgs &e)
{
	if (showConfiguration)
	{
		controls->mousePressed( e.x, e.y, e.button ); //guilistener
		if ( contourFinder.bTrackObjects )
		{
			if ( e.x > 385 && e.x < 705 && e.y > 30 && e.y < 270 )
			{
				isSelecting = true;
				rect.x = e.x;
				rect.y = e.y;
				rect.width = 0;
				rect.height = 0;
			}
		}
		//Launch the website in browser
		if ( e.x > 723 && e.y > 549 )
			if ( e.x > 830 ) ofLaunchBrowser("http://www.patriciogonzalezvivo.com");
			else ofLaunchBrowser("http://ccv.nuigroup.com/");
	}
}

void ofxKCoreVision::_mouseReleased(ofMouseEventArgs &e)
{
	if (showConfiguration)
		controls->mouseReleased(e.x, e.y, 0); //guilistener
	if( e.x > 385 && e.x < 705 && e.y > 30 && e.y < 270 )
	{
		if	( contourFinder.bTrackObjects && isSelecting )
		{
			minRect = rect;
			maxRect = rect;
		}
	}
}

/*****************************************************************************
* Getters
*****************************************************************************/

std::map<int, Blob> ofxKCoreVision::getBlobs()
{
	return tracker.getTrackedBlobs();
}

std::map<int,Blob> ofxKCoreVision::getObjects()
{
	return tracker.getTrackedObjects();
}

/*****************************************************************************
* ON EXIT
*****************************************************************************/
void ofxKCoreVision::_exit(ofEventArgs &e){
	kinect.close();
	saveSettings();

	//Save templates
	if(contourFinder.bTrackObjects)
		templates.saveTemplateXml();

	// AlexP
	// C++ guarantees that operator delete checks its argument for null-ness
	delete filter;		filter = NULL;
	//delete vidGrabber;	vidGrabber = NULL;
	//delete vidPlayer;	vidPlayer = NULL;
	// -------------------------------- SAVE STATE ON EXIT
	printf("Vision module has exited!\n");
}

