/*
 *  ofxGuiFiles.cpp
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiFiles.h"

//	----------------------------------------------------------------------------------------------------

ofxGuiFiles::ofxGuiFiles()
{
	mParamType = kofxGui_Object_Files;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiFiles::init(int id, string name, int x, int y, int width, int height, string value, string path, string suffix)
{
	int	textHeight	= (name == "") ? 0 : mGlobals->mParamFontHeight;
	
	mParamId		= id;
	mParamName		= name;
	
	mObjX			= x; 
	mObjY			= y;
	
	mPath			= path;
	mSuffix			= suffix;

	int maxWidth	= getFileList();
	
	if(maxWidth > width)
		width = maxWidth;
	
	mObjWidth		= width;
	mObjHeight		= textHeight + height;
			
	setValue(value);
	setControlRegion(0, textHeight, width, height);
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiFiles::setValue(string value)
{
	mSelected = 0;
	
	for(int i = 0; i < mFilelist.size(); i++)
	{
		string file = mFilelist.at(i);
		
		if(value == file)
		{
			mSelected	= i;
			mValue		= value;
			break;
		}
	}
	
	if(mSelected == 0 && mFilelist.size() > 0)
		mValue = mFilelist.at(mSelected);
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiFiles::update(int id, int task, void* data, int length)
{
	bool handled = false;
	
	if(id == mParamId)
	{
		if(task == kofxGui_Set_Bool)
		{
			if((*(bool*)data))
				getFileList();

		}
		else if(task == kofxGui_Set_String)
		{
			setValue((*(string*)data));
		}

		handled = true;
	}
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiFiles::draw()
{
	glPushMatrix();
	
	glTranslatef(mObjX, mObjY, 0.0f);
	
		if(mParamName != "")
			drawParamString(0.0, 0.0, mParamName + ": " + ofToString(mNumberOfFiles, 0) + "/" + ofToString(mSelected + 1, 0), false);

		ofFill();
		
		//	background
		glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);
		ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);

		if(mValue != "")
			drawParamString(mCtrX + mGlobals->mFilesXText, mCtrY + mGlobals->mFilesYText, mValue, false);	

		ofNoFill();
		
		//	frame
		glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
		ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);
	
	glPopMatrix();
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiFiles::mouseDragged(int x, int y, int button)
{
	if(mMouseIsDown && mNumberOfFiles > 0)
	{
		mSelected	= roundInt(fractionToValue(mouseToFraction(mouseToLocal(x, y)).x));
		mValue		= mFilelist.at(mSelected);
	}
		
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiFiles::mousePressed(int x, int y, int button)
{
	mMouseIsDown = isPointInsideMe(mouseToLocal(x, y));
	
	if(mMouseIsDown)
	{
		mMemory = mValue;
		mouseDragged(x, y, button);
	}
	
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiFiles::mouseReleased(int x, int y, int button)
{
	bool handled = mMouseIsDown;

	if(mMouseIsDown)
	{
		if(isPointInsideMe(mouseToLocal(x, y)))
		   mGlobals->mListener->handleGui(mParamId, kofxGui_Set_String, &mValue, sizeof(string));
		else
		   mValue = mMemory;
		   
		mMouseIsDown = false;
	}
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiFiles::buildFromXml()
{
	mGlobals->mListener->handleGui(mParamId, kofxGui_Set_String, &mValue, sizeof(string));
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiFiles::saveToXml()
{
	int id = saveObjectData();
	
	mGlobals->mXml.setValue("OBJECT:VALUE", mValue, id);
	mGlobals->mXml.setValue("OBJECT:SUBPATH", mPath, id);
	mGlobals->mXml.setValue("OBJECT:SUFFIX", mSuffix, id);
}

//	----------------------------------------------------------------------------------------------------

float ofxGuiFiles::valueToFraction(float value)
{
	return value / (mNumberOfFiles - 1);
}

//	----------------------------------------------------------------------------------------------------

float ofxGuiFiles::fractionToValue(float fraction)
{
	return fraction * (mNumberOfFiles - 1);
}

//	----------------------------------------------------------------------------------------------------

int ofxGuiFiles::getFileList()
{	
	mFilelist.clear();
	
	mGlobals->mDir.reset();
	mGlobals->mDir.allowExt(mSuffix);
	
	mNumberOfFiles	= mGlobals->mDir.listDir(mPath);
	int maxWidth	= 0;
	
	for(int i = 0; i < mNumberOfFiles; i++)
	{
		string file = mGlobals->mDir.getName(i);
		mFilelist.push_back(file);
		
		int width = roundInt(mGlobals->mParamFont.stringWidth(file));
		
		if(width > maxWidth)
			maxWidth = width;
	}
	
	return maxWidth;
}

//	----------------------------------------------------------------------------------------------------
