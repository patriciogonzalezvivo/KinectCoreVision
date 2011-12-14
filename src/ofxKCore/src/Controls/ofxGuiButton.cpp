/*
 *  ofxGuiButton.cpp
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiButton.h"

//	----------------------------------------------------------------------------------------------------

ofxGuiButton::ofxGuiButton()
{
	mParamType = kofxGui_Object_Button;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiButton::init(int id, string name, int x, int y, int width, int height, bool value, int display)
{
	int	textWidth	= (name == "") ? 0 : mGlobals->mButtonXText + roundInt(mGlobals->mHeadFont.stringWidth(name));

	mParamId		= id;
	mParamName		= name;
	
	mObjX			= x; 
	mObjY			= y;
	
	mObjWidth		= textWidth + width;
	mObjHeight		= height;

	mDisplay		= display;
	
	setValue(value);
	setControlRegion(0, 0, width, height);
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiButton::setValue(bool value)
{
	mValue = value;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiButton::update(int id, int task, void* data, int length)
{
	bool handled = false;
	
	if(id == mParamId && length == sizeof(bool))
	{
		setValue(*(bool*)data);
		handled = true;
	}
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiButton::draw()
{
	glPushMatrix();
	
		glTranslatef(mObjX, mObjY, 0.0f);
		
		if(mParamName != "")
			drawParamString(mCtrWidth + mGlobals->mButtonXText, mGlobals->mButtonYText, mParamName, false);
		
		ofFill();
		
		//	background
		glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);
		ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);
		
		if(mValue == 1)
		{
			//	handle
			glColor4f(mGlobals->mButtonColor.r, mGlobals->mButtonColor.g, mGlobals->mButtonColor.b, mGlobals->mButtonColor.a);
			ofRect(mCtrX , mCtrY, mCtrWidth, mCtrHeight);
		}
		
		ofNoFill();
		
		//	frame
		glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
		ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);
	
	glPopMatrix();
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiButton::mouseDragged(int x, int y, int button)
{
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiButton::mousePressed(int x, int y, int button)
{
	mMouseIsDown = isPointInsideMe(mouseToLocal(x, y));
	
	if(mMouseIsDown)
	{
		if(mDisplay == kofxGui_Button_Trigger)
			setValue(true);
		else
			setValue(!mValue);
		
		mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Bool, &mValue, sizeof(bool));
	}

	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiButton::mouseReleased(int x, int y, int button)
{
	bool handled = mMouseIsDown;
	
	if(mMouseIsDown)
	{
		if(mDisplay == kofxGui_Button_Trigger)
		{
			setValue(false);
			mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Bool, &mValue, sizeof(bool));
		}
		
		mMouseIsDown = false;
	}
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiButton::buildFromXml()
{
	mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Bool, &mValue, sizeof(bool));
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiButton::saveToXml()
{
	int		id		= saveObjectData();
	bool	value	= (mDisplay == kofxGui_Button_Trigger) ? false : mValue;
	
	mGlobals->mXml.setValue("OBJECT:VALUE", value, id);
}

//	----------------------------------------------------------------------------------------------------
