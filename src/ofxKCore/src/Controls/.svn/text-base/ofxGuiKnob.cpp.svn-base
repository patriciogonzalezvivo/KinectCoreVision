/*
 *  ofxGuiKnob.cpp
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiKnob.h"

//	----------------------------------------------------------------------------------------------------

ofxGuiKnob::ofxGuiKnob()
{
	mParamType = kofxGui_Object_Knob;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiKnob::init(int id, string name, int x, int y, int width, int height, float min, float max, float value, int display, int steps)
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

void ofxGuiKnob::setValue(float value)
{
	if(mSteps > 1)
	{
		float	fraction	= valueToFraction(value);
		float	steps		= (float)mSteps - 1;
		float	slice		= roundInt(fraction * steps) / steps;
		
		value = mMinVal + mValDlt * slice;
	}
	
	mValue = value;	
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiKnob::setRange(float min, float max) 
{
	mMinVal	= min;
	mMaxVal	= max;
	mValDlt	= mMaxVal - mMinVal;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiKnob::update(int id, int task, void* data, int length)
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

void ofxGuiKnob::draw()
{
	glPushMatrix();
	
	glTranslatef(mObjX, mObjY, 0.0);
	
	float	w	= mCtrWidth / 2;
	float	h	= mCtrHeight / 2;
	float	x	= mCtrX + w;
	float	y	= mCtrY + h;
	
	float	v1	= 130.0f;
	float	v2	= 280.0f;
	
	int		resolution = 22;
	
	float	angle, step, cosine, sine, xpos, ypos;
	
	if(mParamName != "")
		drawParamString(x, 0.0, mParamName, true);
	
	ofFill();
	
	//	background
	glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);
	ofEllipse(x, y, w, h);
	
	//	action
	glColor4f(mGlobals->mSliderColor.r, mGlobals->mSliderColor.g, mGlobals->mSliderColor.b, mGlobals->mSliderColor.a);
	
	step	= (DEG_TO_RAD * valueToFraction(mValue) * v2) / (resolution - 1);
	angle	= DEG_TO_RAD * v1;
	
	glBegin(GL_TRIANGLE_STRIP);
		for(int i = 0; i < resolution; i++)
		{
			cosine	= cos(angle);
			sine	= sin(angle);
			
			xpos	= cosine * w;
			ypos	= sine * h;
			
			glVertex2f(x + xpos, y + ypos);
			
			xpos	= cosine * (w - mGlobals->mKnobSize);
			ypos	= sine * (h - mGlobals->mKnobSize);
			
			glVertex2f(x + xpos, y + ypos);
			
			angle += step;
		}
	glEnd();
	
	ofNoFill();
	
	//	handle
	glColor4f(mGlobals->mHandleColor.r, mGlobals->mHandleColor.g, mGlobals->mHandleColor.b, mGlobals->mHandleColor.a);
	
	angle	= DEG_TO_RAD * v1;
	cosine	= cos(angle);
	sine	= sin(angle);
	
	ofLine(x + cosine * w, y + sine * h, x + cosine * (w - mGlobals->mKnobSize), y + sine * (h - mGlobals->mKnobSize));
	
	angle	= DEG_TO_RAD * (v1 + valueToFraction(mValue) * v2);
	cosine	= cos(angle);
	sine	= sin(angle);
	
	ofLine(x + cosine * w, y + sine * h, x + cosine * (w - mGlobals->mKnobSize), y + sine * (h - mGlobals->mKnobSize));
	
	step	= (DEG_TO_RAD * valueToFraction(mValue) * v2) / (resolution - 1);
	angle	= DEG_TO_RAD * v1;
	
	glPushMatrix();	
	glTranslatef(x, y, 0.0);
	ofBeginShape();
	
	for(int i = 0; i < resolution; i++)
	{
		xpos	= cos(angle) * (w - mGlobals->mKnobSize);
		ypos	= sin(angle) * (h - mGlobals->mKnobSize);
		
		ofVertex(xpos, ypos);
		angle += step;
	}
	
	ofEndShape(false);
	glPopMatrix();
	
	//	frame
	glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
	ofEllipse(x, y, w, h);
	
	drawValueString(x, y, floatToString(mValue, mDisplay));
	
	glPopMatrix();
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiKnob::mouseDragged(int x, int y, int button)
{
	if(mMouseIsDown)
	{
		ofxPoint2f point	= mouseToLocal(x, y);
		
		float	deltaX		= point.x - mFirstHit.x;
		float	deltaY		= point.y - mFirstHit.y;
		float	delta		= deltaX - deltaY;
		float	value		= CLAMP(mValue + delta * (mValDlt / 100.0f), mMinVal, mMaxVal);
		
		if(value != mValue)
		{
			setValue(value);
			mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Float, &mValue, sizeof(float));
			
			mFirstHit = point;
		}
	}
	
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiKnob::mousePressed(int x, int y, int button)
{
	ofxPoint2f point	= mouseToLocal(x, y);
	mMouseIsDown		= isPointInsideMe(point);
	
	if (mMouseIsDown)
	{
		mFirstHit = point;
		mouseDragged(x, y, button);
	}
	
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiKnob::mouseReleased(int x, int y, int button)
{
	bool handled = mMouseIsDown;
	
	if(mMouseIsDown)
		mMouseIsDown = false;
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiKnob::buildFromXml()
{
	mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Float, &mValue, sizeof(float));
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiKnob::saveToXml()
{
	int id = saveObjectData();
	
	mGlobals->mXml.setValue("OBJECT:MIN", mMinVal, id);
	mGlobals->mXml.setValue("OBJECT:MAX", mMaxVal, id);
	mGlobals->mXml.setValue("OBJECT:VALUE", mValue, id);
}

//	----------------------------------------------------------------------------------------------------

float ofxGuiKnob::valueToFraction(float value)
{
	return (value - mMinVal) / mValDlt;
}

//	----------------------------------------------------------------------------------------------------

float ofxGuiKnob::fractionToValue(float fraction)
{
	return (mValDlt * fraction) + mMinVal;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiKnob::drawValueString(float x, float y, string text)
{
	glColor4f(mGlobals->mTextColor.r, mGlobals->mTextColor.g, mGlobals->mTextColor.b, mGlobals->mTextColor.a);
	
	x -= roundInt(mGlobals->mParamFont.stringWidth(text) / 2.0f);
	mGlobals->mParamFont.drawString(text, x, y);
	
	//	debug rect to position font
	/*
	 ofRectangle rect = mGlobals->mParamFont.getStringBoundingBox(text, x, y);
	 ofNoFill();
	 glColor4f(1.0, 0.0, 0.0, 1.0);
	 ofRect(x, y, rect.width, mGlobals->mParamFontHeight);
	 */
}

//	----------------------------------------------------------------------------------------------------
