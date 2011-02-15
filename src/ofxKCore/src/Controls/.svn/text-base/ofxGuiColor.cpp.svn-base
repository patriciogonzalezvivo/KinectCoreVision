/*
 *  ofxGuiColor.cpp
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiColor.h"

//	----------------------------------------------------------------------------------------------------

ofxGuiColor::ofxGuiColor()
{
	mParamType = kofxGui_Object_Color;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiColor::init(int id, string name, int x, int y, int width, int height, ofRGBA value, int display)
{
	int	textHeight	= (name == "") ? 0 : mGlobals->mParamFontHeight;
	
	mParamId		= id;
	mParamName		= name;
	
	mObjX			= x; 
	mObjY			= y;
	
	mObjWidth		= width;
	mObjHeight		= textHeight + height;
	
	mDisplay		= display;
	
	mSize			= (display == kofxGui_Color_RGB ? 3 : 4);

	setValue(value);
	setControlRegion(0, textHeight, width, height);
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiColor::setValue(ofRGBA value)
{
	mValue = value;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiColor::update(int id, int task, void* data, int length)
{
	bool handled = false;
	
	if(id == mParamId && length == sizeof(ofRGBA))
	{
		setValue(*(ofRGBA*)data);
		handled = true;
	}
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiColor::draw()
{
	glPushMatrix();
	
	glTranslatef(mObjX, mObjY, 0.0f);
	
	if(mParamName != "")
		drawParamString(0.0, 0.0, mParamName + ": " + mValue.toString(mDisplay), false);
	
	ofFill();
	
	//	background
	glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);
	ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);

	float	height	= (mCtrHeight - 2.0 - mSize) / (float)mSize;
	float	posY	= mCtrY + 2.0;
	float	posX	= mCtrWidth * mValue.r;
	
	//	r
	glColor4f(1.0, 0.0, 0.0, 0.8);
	ofRect(mCtrX, posY, posX, height);
	glColor4f(mGlobals->mHandleColor.r, mGlobals->mHandleColor.g, mGlobals->mHandleColor.b, mGlobals->mHandleColor.a);
	ofRect(posX, posY, 1.0, height);
	
	posY	+= 1.0 + height;
	posX	 = mCtrWidth * mValue.g;
	
	//	g
	glColor4f(0.0, 1.0, 0.0, 0.8);
	ofRect(mCtrX, posY, posX, height);
	glColor4f(mGlobals->mHandleColor.r, mGlobals->mHandleColor.g, mGlobals->mHandleColor.b, mGlobals->mHandleColor.a);
	ofRect(posX, posY, 1.0, height);

	posY	+= 1.0 + height;
	posX	 = mCtrWidth * mValue.b;

	//	b
	glColor4f(0.0, 0.0, 1.0, 0.8);
	ofRect(mCtrX, posY, posX, height);
	glColor4f(mGlobals->mHandleColor.r, mGlobals->mHandleColor.g, mGlobals->mHandleColor.b, mGlobals->mHandleColor.a);
	ofRect(posX, posY, 1.0, height);
	
	if(mDisplay == kofxGui_Color_RGBA)
	{
		posY	+= 1.0 + height;
		posX	 = mCtrWidth * mValue.a;

		//	a
		glColor4f(1.0, 1.0, 1.0, 0.4);
		ofRect(mCtrX, posY, posX, height);
		glColor4f(mGlobals->mHandleColor.r, mGlobals->mHandleColor.g, mGlobals->mHandleColor.b, mGlobals->mHandleColor.a);
		ofRect(posX, posY, 1.0, height);
	}
	
	ofNoFill();
	
	//	frame
	glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
	ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);
	
	glPopMatrix();
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiColor::mouseDragged(int x, int y, int button)
{
	if(mMouseIsDown)
	{
		//	int value = mValue.toInt(mDisplay);
		mValue.setChanel(mSlider, mouseToFraction(mouseToLocal(x, y)).x);
		
		//	if(mValue.toInt(mDisplay) != value)
			mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Color, &mValue, sizeof(ofRGBA));
	}
	
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiColor::mousePressed(int x, int y, int button)
{
	ofxPoint2f inside = mouseToLocal(x, y);
	mMouseIsDown = isPointInsideMe(inside);
	
	if(mMouseIsDown)
	{
		mSlider = mouseToSlider(mouseToFraction(inside).y);
		mouseDragged(x, y, button);
	}
	
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiColor::mouseReleased(int x, int y, int button)
{
	bool handled = mMouseIsDown;
	
	if(mMouseIsDown)
		mMouseIsDown = false;
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiColor::buildFromXml()
{
	mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Color, &mValue, sizeof(ofRGBA));
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiColor::saveToXml()
{
	int id = saveObjectData();
	
	mGlobals->mXml.setValue("OBJECT:VALUE", mValue.toString(kofxGui_Color_RGBA), id);
}

//	----------------------------------------------------------------------------------------------------

int ofxGuiColor::mouseToSlider(float y)
{
	float position = (int)(y * mSize);
	
	return CLAMP(position, 0, mSize);
}

//	----------------------------------------------------------------------------------------------------
