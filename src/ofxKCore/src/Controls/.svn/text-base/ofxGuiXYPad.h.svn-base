/*
 *  ofxGuiXYPad.h
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI_PAD
#define OFX_GUI_PAD

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiTypes.h"
#include "ofxGuiObject.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiXYPad : public ofxGuiObject
{

public:

	ofxGuiXYPad();

	void		init(int id, string name, int x, int y, int width, int height, ofxPoint2f min, ofxPoint2f max, ofxPoint2f value, int display, int steps);

	void		setValue(ofxPoint2f value);
	void		setRange(ofxPoint2f min, ofxPoint2f max);

	bool		update(int id, int task, void* data, int length);
	void		draw();

	bool		mouseDragged(int x, int y, int button);
	bool		mousePressed(int x, int y, int button);
	bool		mouseReleased(int x, int y, int button);
	
	void		buildFromXml();
	void		saveToXml();

	ofxPoint2f	valueToFraction(ofxPoint2f value);
	ofxPoint2f	fractionToValue(ofxPoint2f fraction);
	
	ofxPoint2f	mValue;
	ofxPoint2f	mMinVal;
	ofxPoint2f	mMaxVal;
	ofxPoint2f	mValDlt;
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
