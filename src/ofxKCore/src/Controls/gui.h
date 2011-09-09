/*
*  GUI.h
*
*
*  Created on 2/2/09.
*  Copyright 2009 NUI Group. All rights reserved.
*
*/

#ifndef GUI_CONTROLS_H
#define GUI_CONTROLS_H

#include "ofxKCoreVision.h"

ofxKCoreVision  *appPtr;

void ofxKCoreVision::setupControls()
{
	appPtr = this;

	//panel border color
	controls->mGlobals->mBorderColor.r = 0;
	controls->mGlobals->mBorderColor.g = 0;
	controls->mGlobals->mBorderColor.b = 0;
	controls->mGlobals->mBorderColor.a = .3;
	//panel color
	controls->mGlobals->mCoverColor.r = 1;
	controls->mGlobals->mCoverColor.g = 1;
	controls->mGlobals->mCoverColor.b = 1;
	controls->mGlobals->mCoverColor.a = .4;
	//control outline color
	controls->mGlobals->mFrameColor.r = 0;
	controls->mGlobals->mFrameColor.g = 0;
	controls->mGlobals->mFrameColor.b = 0;
	controls->mGlobals->mFrameColor.a = .3;
	//text color
	controls->mGlobals->mTextColor.r = 0;
	controls->mGlobals->mTextColor.g = 0;
	controls->mGlobals->mTextColor.b = 0;
	controls->mGlobals->mTextColor.a = 1;
	//button color
	controls->mGlobals->mButtonColor.r = 1;
	controls->mGlobals->mButtonColor.g = 0;
	controls->mGlobals->mButtonColor.b = 0;
	controls->mGlobals->mButtonColor.a = .8;
	//slider tip color
	controls->mGlobals->mHandleColor.r = 0;
	controls->mGlobals->mHandleColor.g = 0;
	controls->mGlobals->mHandleColor.b = 0;
	//slider color
	controls->mGlobals->mSliderColor.r = 1;
	controls->mGlobals->mSliderColor.g = 0;
	controls->mGlobals->mSliderColor.b = 0;
	controls->mGlobals->mSliderColor.a = .8;

	ofxGuiPanel* propPanel = controls->addPanel(appPtr->propertiesPanel, "Camera Properties", 740, 150, 12, OFXGUI_PANEL_SPACING);
	propPanel->addButton(appPtr->propertiesPanel_flipV, "Flip Vertical (j)", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Switch);
	propPanel->addButton(appPtr->propertiesPanel_flipH, "Flip Horizontal (h)", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Switch);
	propPanel->mObjWidth = 200;
	propPanel->mObjHeight = 80;


	ofxGuiPanel* oPanel = controls->addPanel(appPtr->optionPanel, "Communication", 740, 240, OFXGUI_PANEL_BORDER, OFXGUI_PANEL_SPACING);
	oPanel->addButton(appPtr->optionPanel_tuio_osc, "TUIO UDP (t)", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Switch);
	oPanel->addButton(appPtr->optionPanel_tuio_tcp, "Flash XML (f)", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Switch);
	oPanel->addButton(appPtr->optionPanel_bin_tcp, "Binary TCP (n)", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Switch);
	oPanel->mObjHeight = 90;
	oPanel->mObjWidth = 200;

	ofxGuiPanel* trackingPanel = controls->addPanel(appPtr->optionPanel, "Track", 740, 440, OFXGUI_PANEL_BORDER, OFXGUI_PANEL_SPACING);
	trackingPanel->addButton(appPtr->trackingPanel_trackBlobs, "Blobs", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Switch);
	trackingPanel->addButton(appPtr->trackingPanel_trackFingers, "Fingers", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Switch);
	trackingPanel->addButton(appPtr->trackingPanel_trackObjects, "Objects", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Switch);
	trackingPanel->mObjHeight = 90;
	trackingPanel->mObjWidth = 200;

	ofxGuiPanel* cPanel = controls->addPanel(appPtr->calibrationPanel, "Calibration", 740, 95, OFXGUI_PANEL_BORDER, OFXGUI_PANEL_SPACING);
	cPanel->addButton(appPtr->calibrationPanel_calibrate, "Enter Calibration (c)", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Trigger);
	cPanel->mObjWidth = 200;
	cPanel->mObjHeight = 45;

	ofxGuiPanel* panel2 = controls->addPanel(appPtr->savePanel, "Settings", 740, 340, OFXGUI_PANEL_BORDER, OFXGUI_PANEL_SPACING);
	panel2->addButton(appPtr->kParameter_SaveXml, "Save Settings (s)", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Trigger);
	panel2->addButton(appPtr->kParameter_SaveTemplateXml, "Save Templates", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Trigger);
	panel2->addButton(appPtr->kParameter_LoadTemplateXml, "Load Templates", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Trigger);
	panel2->mObjWidth = 200;
	panel2->mObjHeight = 90;

	//Tracked Image
	ofxGuiPanel* trackPanel = controls->addPanel(appPtr->trackedPanel, "Tracked Image", 376, 255, OFXGUI_PANEL_BORDER, OFXGUI_PANEL_SPACING);
	trackPanel->addButton(appPtr->trackedPanel_darkblobs, "Inverse", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Switch);
	trackPanel->addSlider(appPtr->trackedPanel_threshold, "Image Threshold", 140, 13, 0.0f, 255.0f, filter->threshold, kofxGui_Display_Int, 0);
	trackPanel->addSlider(appPtr->trackedPanel_min_movement, "Movement Filtering", 140, 13, 0.0f, 15.0f, tracker.MOVEMENT_FILTERING, kofxGui_Display_Int, 0);
	trackPanel->addSlider(appPtr->trackedPanel_min_blob_size, "Min Blob Size", 140, 13, 1.0f, 500.0f, MIN_BLOB_SIZE, kofxGui_Display_Int, 0);
	trackPanel->addSlider(appPtr->trackedPanel_max_blob_size, "Max Blob Size", 140, 13, 1.0f, 1000.0f, MAX_BLOB_SIZE, kofxGui_Display_Int, 0);
	trackPanel->mObjHeight = 120;
	trackPanel->mObjWidth = 319;
	trackPanel->mObjects[0]->mObjX = 120;
	trackPanel->mObjects[0]->mObjY = 11;
	trackPanel->mObjects[1]->mObjY = 32;
	trackPanel->mObjects[2]->mObjX = 165;
	trackPanel->mObjects[2]->mObjY = 32;
	trackPanel->mObjects[3]->mObjY = 67;
	trackPanel->mObjects[4]->mObjX = 165;
	trackPanel->mObjects[4]->mObjY = 67;
	trackPanel->adjustToNewContent(100, 0);

	//Source Image
	ofxGuiPanel* srcPanel = controls->addPanel(appPtr->sourcePanel, "Source Image", 31, 255, OFXGUI_PANEL_BORDER, OFXGUI_PANEL_SPACING);
	srcPanel->addButton(appPtr->trackedPanel_outlines, "Show Outlines (o)", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Switch);
	srcPanel->addButton(appPtr->trackedPanel_ids, "Show IDs (i)", OFXGUI_BUTTON_HEIGHT, OFXGUI_BUTTON_HEIGHT, kofxGui_Button_Off, kofxGui_Button_Switch);
	//srcPanel->addSlider(appPtr->trackedPanel_hullPress, "Finger Pressition", 140, 13, 0.0, 100.0, hullPress, kofxGui_Display_Float2, 0);
	srcPanel->mObjWidth = 319;
	srcPanel->mObjects[0]->mObjX = 110;
	srcPanel->mObjects[0]->mObjY = 11;
	srcPanel->mObjects[1]->mObjX = 230;
	srcPanel->mObjects[1]->mObjY = 11;
	//srcPanel->mObjects[2]->mObjX = 230; //
	//srcPanel->mObjects[2]->mObjY = 32; //
	//srcPanel->mObjects[3]->mObjX = 110;
	//srcPanel->mObjects[3]->mObjY = 42;
	//srcPanel->mObjects[4]->mObjX = 230;
	//srcPanel->mObjects[4]->mObjY = 42;
	srcPanel->adjustToNewContent(100, 0);
	srcPanel->mObjHeight = 60;

	//Distance (ex template)
	ofxGuiPanel* tPanel = controls->addPanel(appPtr->TemplatePanel, "Distance between:", 31, 315, OFXGUI_PANEL_BORDER, OFXGUI_PANEL_SPACING);
	tPanel->addSlider(appPtr->TemplatePanel_minArea, "Near mm", 140, 13, 0, 4000, nearThreshold, kofxGui_Display_Int, 1);
	tPanel->addSlider(appPtr->TemplatePanel_maxArea, "Far mm", 140, 13, 0, 4000, farThreshold, kofxGui_Display_Int, 1);
	tPanel->mObjWidth = 319;
	tPanel->mObjHeight = 60;
	tPanel->mObjects[0]->mObjY = 25;
	tPanel->mObjects[1]->mObjX = 165;
	tPanel->mObjects[1]->mObjY = 25;
	tPanel->adjustToNewContent(100, 0);

	//Background Image
	ofxGuiPanel* bkPanel1 = controls->addPanel(appPtr->backgroundPanel, "Background", 31, 487, 10, 7);
	bkPanel1->addButton(backgroundPanel_remove, "Remove BG (b)", 10, 10, kofxGui_Button_Off, kofxGui_Button_Trigger);
	bkPanel1->addButton(backgroundPanel_dynamic, "Dynamic Subtract", 10, 10, kofxGui_Button_Off, kofxGui_Button_Switch);
	bkPanel1->addSlider(appPtr->backgroundPanel_learn_rate, "Learn Speed", 110, 13, 1.0f, 500.0f, backgroundLearnRate, kofxGui_Display_Int, 0);
	bkPanel1->mObjWidth = 127;
	bkPanel1->mObjHeight = 95;

	//Smooth Image
	ofxGuiPanel* sPanel = controls->addPanel(appPtr->smoothPanel, "Smooth", 166, 487, 10, 7);
	sPanel->addButton(smoothPanel_use, "", 12, 12, kofxGui_Button_Off, kofxGui_Button_Switch);
	sPanel->addSlider(smoothPanel_smooth, "Smooth", 110, 13, 0.0f, 15.0f, filter->smooth, kofxGui_Display_Int, 0);
	sPanel->mObjects[0]->mObjX = 105;
	sPanel->mObjects[0]->mObjY = 10;
	sPanel->mObjects[1]->mObjY = 30;
	sPanel->mObjWidth = 127;
	sPanel->mObjHeight = 95;

	//Highpass Image
	ofxGuiPanel* hpPanel = controls->addPanel(appPtr->highpassPanel, "Highpass", 301, 487, OFXGUI_PANEL_BORDER, 7);
	hpPanel->addButton(highpassPanel_use, "", 12, 12, kofxGui_Button_Off, kofxGui_Button_Switch);
	hpPanel->addSlider(highpassPanel_blur, "Blur", 110, 13, 0.0f, 200.0f, filter->highpassBlur, kofxGui_Display_Int, 0);
	hpPanel->addSlider(highpassPanel_noise, "Noise", 110, 13, 0.0f, 30.0f, filter->highpassNoise, kofxGui_Display_Int, 0);
	hpPanel->mObjects[0]->mObjX = 105;
	hpPanel->mObjects[0]->mObjY = 10;
	hpPanel->mObjects[1]->mObjY = 30;
	hpPanel->mObjects[2]->mObjY = 60;
	hpPanel->mObjWidth = 127;
	hpPanel->mObjHeight = 95;

	//Amplify Image
	ofxGuiPanel* ampPanel = controls->addPanel(appPtr->amplifyPanel, "Amplify", 436, 487, OFXGUI_PANEL_BORDER, 7);
	ampPanel->addButton(amplifyPanel_use, "", 12, 12, kofxGui_Button_Off, kofxGui_Button_Switch);
	ampPanel->addSlider(amplifyPanel_amp, "Amplify", 110, 13, 0.0f, 300.0f, filter->highpassAmp, kofxGui_Display_Int, 0);
	ampPanel->mObjects[0]->mObjX = 105;
	ampPanel->mObjects[0]->mObjY = 10;
	ampPanel->mObjects[1]->mObjY = 30;
	ampPanel->mObjWidth = 127;
	ampPanel->mObjHeight = 95;

	//do update while inactive
	controls->forceUpdate(false);
	controls->activate(true);

	/****************************
	* Set GUI values on startup
	****************************/
	controls->update(appPtr->propertiesPanel_flipV, kofxGui_Set_Bool, &appPtr->filter->bVerticalMirror, sizeof(bool));
	controls->update(appPtr->propertiesPanel_flipH, kofxGui_Set_Bool, &appPtr->filter->bHorizontalMirror, sizeof(bool));
	controls->update(appPtr->trackedPanel_outlines, kofxGui_Set_Bool, &appPtr->bDrawOutlines, sizeof(bool));
	controls->update(appPtr->trackedPanel_ids, kofxGui_Set_Bool, &appPtr->bShowLabels, sizeof(bool));
	controls->update(appPtr->trackedPanel_darkblobs, kofxGui_Set_Bool, &appPtr->filter->bTrackDark, sizeof(bool));
	//Calibration
	controls->update(appPtr->calibrationPanel_calibrate, kofxGui_Set_Bool, &appPtr->bCalibration, sizeof(bool));
	//Dynamic Background
	controls->update(appPtr->backgroundPanel_dynamic, kofxGui_Set_Bool, &appPtr->filter->bDynamicBG, sizeof(bool));
	//Smooth
	controls->update(appPtr->smoothPanel_use, kofxGui_Set_Bool, &appPtr->filter->bSmooth, sizeof(bool));
	controls->update(appPtr->smoothPanel_smooth, kofxGui_Set_Bool, &appPtr->filter->smooth, sizeof(float));
	//Highpass
	controls->update(appPtr->highpassPanel_use, kofxGui_Set_Bool, &appPtr->filter->bHighpass, sizeof(bool));
	controls->update(appPtr->highpassPanel_blur, kofxGui_Set_Bool, &appPtr->filter->highpassBlur, sizeof(float));
	controls->update(appPtr->highpassPanel_noise, kofxGui_Set_Bool, &appPtr->filter->highpassNoise, sizeof(float));
	//Amplify
	controls->update(appPtr->amplifyPanel_use, kofxGui_Set_Bool, &appPtr->filter->bAmplify, sizeof(bool));
	controls->update(appPtr->amplifyPanel_amp, kofxGui_Set_Bool, &appPtr->filter->highpassAmp, sizeof(float));
	//Threshold
	controls->update(appPtr->trackedPanel_threshold, kofxGui_Set_Bool, &appPtr->filter->threshold, sizeof(float));
	//Min Movement
	controls->update(appPtr->trackedPanel_min_movement, kofxGui_Set_Bool, &appPtr->tracker.MOVEMENT_FILTERING, sizeof(float));
	//Min Blob Size
	controls->update(appPtr->trackedPanel_min_blob_size, kofxGui_Set_Bool, &appPtr->MIN_BLOB_SIZE, sizeof(float));
	//Max Blob Size
	controls->update(appPtr->trackedPanel_max_blob_size, kofxGui_Set_Bool, &appPtr->MAX_BLOB_SIZE, sizeof(float));
	//Hull Convex Pressition
	//controls->update(appPtr->trackedPanel_hullPress, kofxGui_Set_Bool, &appPtr->hullPress, sizeof(float));
	//Template Area
	controls->update(appPtr->TemplatePanel_minArea, kofxGui_Set_Bool, &appPtr->minTempArea, sizeof(float));
	controls->update(appPtr->TemplatePanel_maxArea, kofxGui_Set_Bool, &appPtr->maxTempArea, sizeof(float));
	//Background Learn Rate
	controls->update(appPtr->backgroundPanel_learn_rate, kofxGui_Set_Bool, &appPtr->backgroundLearnRate, sizeof(float));
	//Track Panel
	controls->update(appPtr->trackingPanel_trackBlobs, kofxGui_Set_Bool, &appPtr->contourFinder.bTrackBlobs, sizeof(bool));
	controls->update(appPtr->trackingPanel_trackFingers, kofxGui_Set_Bool, &appPtr->contourFinder.bTrackFingers, sizeof(bool));
	controls->update(appPtr->trackingPanel_trackObjects, kofxGui_Set_Bool, &appPtr->contourFinder.bTrackObjects, sizeof(bool));
	//Send TUIO
	controls->update(appPtr->optionPanel_tuio_osc, kofxGui_Set_Bool, &appPtr->myTUIO.bOSCMode, sizeof(bool));
	controls->update(appPtr->optionPanel_tuio_tcp, kofxGui_Set_Bool, &appPtr->myTUIO.bTCPMode, sizeof(bool));
	controls->update(appPtr->optionPanel_bin_tcp, kofxGui_Set_Bool, &appPtr->myTUIO.bBinaryMode, sizeof(bool));
	//TUIO Height Width
	//controls->update(appPtr->optionPanel_tuio_height_width, kofxGui_Set_Bool, &appPtr->myTUIO.bHeightWidth, sizeof(bool));
}

void ofxKCoreVision ::handleGui(int parameterId, int task, void* data, int length){
	switch(parameterId){
		//Calibration
		case calibrationPanel_calibrate:
				bShowInterface = false;
				//Enter/Exit Calibration
				bCalibration = true;
				calib.calibrating = true;
				tracker.isCalibrating = true;
				if (bFullscreen == false) ofToggleFullscreen();
				bFullscreen = true;
			break;
		//Source
		case propertiesPanel_flipH:
			if(length == sizeof(bool))
				filter->bHorizontalMirror = *(bool*)data;
				//filter_fiducial->bHorizontalMirror = *(bool*)data;
			break;
		case propertiesPanel_flipV:
			if(length == sizeof(bool))
				filter->bVerticalMirror = *(bool*)data;
				//filter_fiducial->bVerticalMirror = *(bool*)data;
			break;

		//Tracking Panel
		case trackingPanel_trackBlobs:
			if(length == sizeof(bool))
				contourFinder.bTrackBlobs=*(bool*)data;
			break;
		case trackingPanel_trackFingers:
			if(length == sizeof(bool))
				contourFinder.bTrackFingers=*(bool*)data;
			break;
		case trackingPanel_trackObjects:
			if(length == sizeof(bool))
			{
				contourFinder.bTrackObjects=*(bool*)data;
				if(contourFinder.bTrackObjects)
				{
					templates.loadTemplateXml();
				}
				else
				{
					templates.saveTemplateXml();
				}
			}
			break;
		//Communication
		case optionPanel_tuio_osc:
			if(length == sizeof(bool))
				myTUIO.bOSCMode = *(bool*)data;
			//	bTUIOMode = *(bool*)data;
				//set tcp to opposite
			//	myTUIO.bTCPMode = false;
			//	controls->update(appPtr->optionPanel_tuio_tcp, kofxGui_Set_Bool, &appPtr->myTUIO.bTCPMode, sizeof(bool));
			//	myTUIO.bBinaryMode = false;
			//	controls->update(appPtr->optionPanel_bin_tcp, kofxGui_Set_Bool, &appPtr->myTUIO.bBinaryMode, sizeof(bool));
				//clear blobs
//				myTUIO.blobs.clear();
			break;
		case optionPanel_tuio_tcp:
			if(length == sizeof(bool))
				myTUIO.bTCPMode = *(bool*)data;
			//	bTUIOMode = *(bool*)data;
				//set osc to opposite
			//	myTUIO.bOSCMode = false;
			//	controls->update(appPtr->optionPanel_tuio_osc, kofxGui_Set_Bool, &appPtr->myTUIO.bOSCMode, sizeof(bool));
			//	myTUIO.bBinaryMode = false;
			//	controls->update(appPtr->optionPanel_bin_tcp, kofxGui_Set_Bool, &appPtr->myTUIO.bBinaryMode, sizeof(bool));
				//clear blobs
//				myTUIO.blobs.clear();
			break;
		case optionPanel_bin_tcp:
			if(length == sizeof(bool))
				myTUIO.bBinaryMode = *(bool*)data;
			bTUIOMode = *(bool*)data;
			//set tcp & osc to opposite
			myTUIO.bTCPMode = false;
			controls->update(appPtr->optionPanel_tuio_tcp, kofxGui_Set_Bool, &appPtr->myTUIO.bTCPMode, sizeof(bool));
			myTUIO.bOSCMode = false;
			controls->update(appPtr->optionPanel_tuio_osc, kofxGui_Set_Bool, &appPtr->myTUIO.bOSCMode, sizeof(bool));
			//clear blobs
//				myTUIO.blobs.clear();
			break;
// 		case optionPanel_tuio_height_width:
// 			if(length == sizeof(bool))
// 				myTUIO.bHeightWidth = *(bool*)data;
// 			break;
		//Background
		case backgroundPanel_dynamic:
			if(length == sizeof(bool))
				filter->bDynamicBG = *(bool*)data;
				//filter_fiducial->bDynamicBG = *(bool*)data;
			break;
		case backgroundPanel_remove:
			if(length == sizeof(bool))
				filter->bLearnBakground = *(bool*)data;
				//filter_fiducial->bLearnBakground = *(bool*)data;
			break;
		case backgroundPanel_learn_rate:
			if(length == sizeof(float))
				backgroundLearnRate = *(float*)data;
			break;
		//Highpass
		case highpassPanel_use:
			if(length == sizeof(bool))
				filter->bHighpass = *(bool*)data;
			break;
		case highpassPanel_blur:
			if(length == sizeof(float))
				filter->highpassBlur = *(float*)data;
			break;
		case highpassPanel_noise:
			if(length == sizeof(float))
				filter->highpassNoise = *(float*)data;
			break;
		//Amplify
		case amplifyPanel_use:
			if(length == sizeof(bool))
				filter->bAmplify = *(bool*)data;
			break;
		case amplifyPanel_amp:
			if(length == sizeof(float))
				filter->highpassAmp = *(float*)data;
			break;
		case trackedPanel_darkblobs:
			if(length == sizeof(bool))
				filter->bTrackDark = *(bool*)data;
			break;
		case trackedPanel_threshold:
			if(length == sizeof(float))
				filter->threshold = *(float*)data;
			break;
		case trackedPanel_min_movement:
			if(length == sizeof(float))
				tracker.MOVEMENT_FILTERING = *(float*)data;
			break;
		case trackedPanel_min_blob_size:
			if(length == sizeof(float))
				MIN_BLOB_SIZE = *(float*)data;
			break;
		case trackedPanel_max_blob_size:
			if(length == sizeof(float))
				MAX_BLOB_SIZE = *(float*)data;
			break;
		case trackedPanel_outlines:
			if(length == sizeof(bool))
				bDrawOutlines = *(bool*)data;
			break;
		case trackedPanel_ids:
			if(length == sizeof(bool))
				bShowLabels = *(bool*)data;
			break;
		//smooth
		case smoothPanel_smooth:
			if(length == sizeof(float))
				filter->smooth = *(float*)data;
			break;
		case smoothPanel_use:
			if(length == sizeof(bool))
				filter->bSmooth = *(bool*)data;
			break;
		//Template Range Sliders
		case TemplatePanel_minArea:
			nearThreshold = *(float*)data;
			break;
		case TemplatePanel_maxArea:
			farThreshold = *(float*)data;
			break;
		//Save Settings
		case kParameter_SaveXml:
			if(length == sizeof(bool))
			{
				if(*(bool*)data)
				{
					controls->saveToXml(OFXGUI_XML);
					saveSettings();
				}
			}
			break;
		case kParameter_LoadTemplateXml:
			if(length == sizeof(bool))
				if(*(bool*)data)
					if(templates.loadTemplateXml())
						printf("Templates Loaded\n");
			break;
		case kParameter_SaveTemplateXml:
			if(length == sizeof(bool))
				if(*(bool*)data)
					templates.saveTemplateXml();
			break;
	}
}
#endif //GUI_CONTROLS_H

