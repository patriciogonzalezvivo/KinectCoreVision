/*
 *  ofxGuiRadar.cpp
 *  ofxGui
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiRadar.h"

//	----------------------------------------------------------------------------------------------------

ofxGuiRadar::ofxGuiRadar()
{
	mParamType = kofxGui_Object_Radar;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiRadar::init(int id, string name, int x, int y, int width, int height, float min, float max, float value, int display, int steps)
{
	int	textHeight	= (name == "") ? 0 : mGlobals->mParamFontHeight;
	
	mParamId		= id;
	mParamName		= name;
	
	mObjX			= x; 
	mObjY			= y;
	
	mObjWidth		= width;
	mObjHeight		= textHeight + height;
	
	mDisplay		= display;
	mSteps			= steps;
	
	setRange(min, max);
	setValue(value);
	setControlRegion(0, textHeight, width, height);
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiRadar::setValue(float value)
{
	if(mSteps > 1)
	{
		float	fraction	= valueToFraction(value);
		float	steps		= (float)mSteps - 1;
		float	slice		= long(fraction * steps + 0.5) / steps;
		
		value = mMinVal + mValDlt * slice;
	}
	
	mValue = value;	
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiRadar::setRange(float min, float max) 
{
	mMinVal	= min;
	mMaxVal	= max;
	mValDlt	= mMaxVal - mMinVal;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiRadar::update(int id, int task, void* data, int length)
{
	bool handled = false;
	
	if(id == mParamId)
	{
		if(task == kofxGui_Set_Float)
			setValue(*(float*)data);
		
		handled = true;
	}
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiRadar::draw()
{
	glPushMatrix();
		
		glTranslatef(mObjX, mObjY, 0.0);
		
		if(mParamName != "")
			drawParamString(0.0, 0.0, mParamName + ": " + floatToString(mValue, mDisplay), false);
		
		float x = (mCtrWidth * valueToFraction(mValue));
		
		ofFill();
		
		//	background
		glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);
		ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);
		
		//	action
		glColor4f(mGlobals->mSliderColor.r, mGlobals->mSliderColor.g, mGlobals->mSliderColor.b, mGlobals->mSliderColor.a);
		ofRect(mCtrX, mCtrY, x, mCtrHeight);
		
		//	handle
		glColor4f(mGlobals->mHandleColor.r, mGlobals->mHandleColor.g, mGlobals->mHandleColor.b, mGlobals->mHandleColor.a);
		ofRect(x, mCtrY, 1.0, mCtrHeight);
		
		ofNoFill();
		
		//	frame
		glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
		ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);
		
	glPopMatrix();
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiRadar::mouseDragged(int x, int y, int button)
{
	if(mMouseIsDown)
	{
		float value = fractionToValue(mouseToFraction(mouseToLocal(x, y)).x);
		
		if(value != mValue)
		{
			setValue(value);
			mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Float, &mValue, sizeof(float));
		}
	}
	
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiRadar::mousePressed(int x, int y, int button)
{
	mMouseIsDown = isPointInsideMe(mouseToLocal(x, y));
	
	if (mMouseIsDown)
		mouseDragged(x, y, button);
	
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiRadar::mouseReleased(int x, int y, int button)
{
	bool handled = mMouseIsDown;
	
	if(mMouseIsDown)
		mMouseIsDown = false;
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiRadar::buildFromXml()
{
	mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Float, &mValue, sizeof(float));
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiRadar::saveToXml()
{
	int id = saveObjectData();
	
	mGlobals->mXml.setValue("OBJECT:MIN", mMinVal, id);
	mGlobals->mXml.setValue("OBJECT:MAX", mMaxVal, id);
	mGlobals->mXml.setValue("OBJECT:VALUE", mValue, id);
}

//	----------------------------------------------------------------------------------------------------

float ofxGuiRadar::valueToFraction(float value)
{
	return (value - mMinVal) / mValDlt;
}

//	----------------------------------------------------------------------------------------------------

float ofxGuiRadar::fractionToValue(float fraction)
{
	return (mValDlt * fraction) + mMinVal;
}

//	----------------------------------------------------------------------------------------------------
