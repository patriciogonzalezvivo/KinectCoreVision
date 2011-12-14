/*
 *  ofxGuiPanel.h
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI_PANEL
#define OFX_GUI_PANEL

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiObject.h"
#include "ofxGuiGlobals.h"
#include "ofxGuiSlider.h"
#include "ofxGuiXYPad.h"
#include "ofxGuiPoints.h"
#include "ofxGuiButton.h"
#include "ofxGuiFiles.h"
#include "ofxGuiColor.h"
#include "ofxGuiMatrix.h"
#include "ofxGuiScope.h"
#include "ofxGuiKnob.h"
#include "ofxGuiRadar.h"
#include "ofxGuiSwitch.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiPanel : public ofxGuiObject
{

public:

	ofxGuiPanel();

	void			init(int id, string name, int x, int y, int border, int spacing);

	bool			update(int parameterId, int task, void* data, int length);
	void			draw();

	bool			mouseDragged(int x, int y, int button);
	bool			mousePressed(int x, int y, int button);
	bool			mouseReleased(int x, int y, int button);
	
	ofxGuiObject*	addSlider(int id, string name, int width, int height, float min, float max, float value, int display, int steps);
	ofxGuiObject*	addXYPad(int id, string name, int width, int height, ofPoint min, ofPoint max, ofPoint value, int display, int steps);
	ofxGuiObject*	addPoints(int id, string name, int width, int height, ofPoint min, ofPoint max, ofPoint value, int display, int steps);
	ofxGuiObject*	addButton(int id, string name, int width, int height, bool value, int display);
	ofxGuiObject*	addFiles(int id, string name, int width, int height, string value, string subPath, string suffix);
	ofxGuiObject*	addColor(int id, string name, int width, int height, ofRGBA value, int display);
	ofxGuiObject*	addMatrix(int id, string name, int width, int height, int xGrid, int yGrid, int value, int mode, int spacing);
	ofxGuiObject*	addScope(int id, string name, int width, int height, int length, ofPoint value, int display);
	ofxGuiObject*	addKnob(int id, string name, int width, int height, float min, float max, float value, int display, int steps);
	ofxGuiObject*	addRadar(int id, string name, int width, int height, float min, float max, float value, int display, int steps);
	ofxGuiObject*	addSwitch(int id, string name, int width, int height,  int min, int max, int value, const string* paramStrings);
	
	void			adjustToNewContent(int w, int h);

	void			buildFromXml();
	void			saveToXml();

	int				mBorder, mSpacing;
	
	vector			<ofxGuiObject*> mObjects;
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
