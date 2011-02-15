/*
 *  ofxGuiPoints.h
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI_POINTS
#define OFX_GUI_POINTS

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiTypes.h"
#include "ofxGuiObject.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiPoints : public ofxGuiObject
{

public:

	ofxGuiPoints();

	void		init(int id, string name, int x, int y, int width, int height, ofPoint min, ofPoint max, ofPoint value, int display, int steps);

	void		setValue(ofPoint value);
	void		setRange(ofPoint min, ofPoint max);

	bool		update(int id, int task, void* data, int length);
	void		draw();

	bool		mouseDragged(int x, int y, int button);
	bool		mousePressed(int x, int y, int button);
	bool		mouseReleased(int x, int y, int button);
	
	void		buildFromXml();
	void		saveToXml();

	ofPoint	valueToFraction(ofPoint value);
	ofPoint	fractionToValue(ofPoint fraction);
	
	bool		isPointWithinDistance(ofPoint position);
	
	float		mDistance;
	
	ofPoint	mValue, mOutVal;
	
	ofPoint	mMinVal;
	ofPoint	mMaxVal;
	ofPoint	mValDlt;
	
	ofPointList	mList;
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
