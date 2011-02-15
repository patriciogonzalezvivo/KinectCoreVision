/*
 *  ofxGuiObject.h
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI_OBJECT
#define OFX_GUI_OBJECT

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiTypes.h"
#include "ofxGuiGlobals.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiObject
{
	
public:

	ofxGuiObject();
	
	virtual	bool	update(int parameterId, int task, void* data, int length){return false;}
	virtual	void	draw(){}

	virtual bool	mouseDragged(int x, int y, int button){return false;}
	virtual bool	mousePressed(int x, int y, int button){return false;}
	virtual bool	mouseReleased(int x, int y, int button){return false;}

	virtual	void	buildFromXml(){}
	virtual	void	saveToXml(){}
	
	void			drawHeadString(float x, float y, string text, bool center);
	void			drawParamString(float x, float y, string text, bool center);
	
	string			floatToString(float value, int display);
	string			pointToString(ofxPoint2f value, int display);
	
	bool			isPointInsideMe(int x, int y);
	bool			isPointInsideMe(ofxPoint2f point);
	
	ofxPoint2f		mouseToLocal(int x, int y);
	ofxPoint2f		mouseToFraction(ofxPoint2f mouse);
	ofxPoint2f		fractionToLocal(ofxPoint2f fraction);
	
	void			setControlRegion(int x, int y, int width, int height);
	
	int				saveObjectData();
	string			getTagName();
	
	int				mParamId, mParamType, mDisplay, mSteps;
	string			mParamName;
	
	float			mObjX, mObjY, mObjWidth, mObjHeight;
	float			mCtrX, mCtrY, mCtrWidth, mCtrHeight, mCtrRight, mCtrBottom;
		
	bool			mMouseIsDown;
	
	ofxGuiGlobals*	mGlobals;
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
