/*
 *  ofxGuiMatrix.cpp
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiMatrix.h"

//	----------------------------------------------------------------------------------------------------

ofxGuiMatrix::ofxGuiMatrix()
{
	mParamType		= kofxGui_Object_Matrix;
	
	mBuffer			= NULL;
	mBufferLength	= 0;
}

//	----------------------------------------------------------------------------------------------------

ofxGuiMatrix::~ofxGuiMatrix()
{
	if(mBuffer)
		delete[] mBuffer;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiMatrix::init(int id, string name, int x, int y, int width, int height, int xGrid, int yGrid, int value, int display, int spacing)
{
	int	textHeight	= (name == "") ? 0 : mGlobals->mParamFontHeight;
	
	mParamId		= id;
	mParamName		= name;
	
	mObjX			= x; 
	mObjY			= y;
	
	mObjWidth		= width;
	mObjHeight		= textHeight + height;
	
	mXGrid			= xGrid;
	mYGrid			= yGrid;
	
	mDisplay			= display;
	mSpacing		= spacing;
	
	setValue(value);
	setControlRegion(0, textHeight, width, height);

	if(mBuffer)
		delete[] mBuffer;
	
	mBufferLength	= xGrid * yGrid;
	mBuffer			= new int[mBufferLength];
	
	memset(mBuffer, 0, sizeof(int) * mBufferLength);

	mGlobals->mListener->handleGui(mParamId, kofxGui_Set_IntArray, mBuffer, mBufferLength);
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiMatrix::setValue(int value)
{
	mValue = value;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiMatrix::update(int id, int task, void* data, int length)
{
	bool	handled	= false;
	int		value	= mValue;
	
	if(id == mParamId)
	{	
		if(task == kofxGui_Set_Float)
			setValue(CLAMP(*(float*)data, 0.0f, 1.0f) * mBufferLength - 1);
		else if(task == kofxGui_Set_Int)
			setValue(CLAMP(*(int*)data, 0, mBufferLength - 1));
		
		handled = true;
	}
	
	if(value != mValue)
	{
		ofCell outVal = ofCell(mValue, mBuffer[mValue]);
		mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Cell, &outVal, sizeof(ofCell));
	}
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiMatrix::draw()
{
	glPushMatrix();
	
	glTranslatef(mObjX, mObjY, 0.0f);
	
	if(mParamName != "")
		drawParamString(0.0, 0.0, mParamName + ": " + ofToString(mValue), false);
	
	ofFill();
	
	//	background
	glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);
	ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);
	
	ofNoFill();

	//	pads
	glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
	
	int		s	= mSpacing / 2;
	float	x	= mCtrX + s;
	float	y	= mCtrY + s;
	float	w	= (mCtrWidth - mSpacing) / mXGrid;
	float	h	= (mCtrHeight - mSpacing) / mYGrid;
	
	for(int i = 0; i < mYGrid; i++)
	{
		for(int j = 0; j < mXGrid; j++)
		{
			int index = j + (i * mXGrid);
			
			if((mBuffer[index] & kofxGui_Matrix_Set) == kofxGui_Matrix_Set)
			{
				ofFill();
				glColor4f(mGlobals->mButtonColor.r, mGlobals->mButtonColor.g, mGlobals->mButtonColor.b, mGlobals->mButtonColor.a);
				ofRect(x + s, y + s, w - mSpacing, h - mSpacing);
			}
			
			if((mBuffer[index] & kofxGui_Matrix_Selected) == kofxGui_Matrix_Selected)
			{
				ofNoFill();
				glColor4f(mGlobals->mMatrixColor.r, mGlobals->mMatrixColor.g, mGlobals->mMatrixColor.b, mGlobals->mMatrixColor.a);
				ofRect(x + s, y + s, w - mSpacing, h - mSpacing);
			}
			else if(mValue == index)
			{
				ofNoFill();
				glColor4f(mGlobals->mAxisColor.r, mGlobals->mAxisColor.g, mGlobals->mAxisColor.b, mGlobals->mAxisColor.a);
				ofRect(x + s, y + s, w - mSpacing, h - mSpacing);
			}
			else
			{
				ofNoFill();
				glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
				ofRect(x + s, y + s, w - mSpacing, h - mSpacing);
			}
			
			x += w;
		}
		
		y += h;
		x  = mCtrX + s;
	}
		
	//	frame
	glColor4f(mGlobals->mFrameColor.r, mGlobals->mFrameColor.g, mGlobals->mFrameColor.b, mGlobals->mFrameColor.a);
	ofRect(mCtrX, mCtrY, mCtrWidth, mCtrHeight);
	
	glPopMatrix();
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiMatrix::mouseDragged(int x, int y, int button)
{
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiMatrix::mousePressed(int x, int y, int button)
{
	ofxPoint2f inside = mouseToLocal(x, y);
	mMouseIsDown = isPointInsideMe(inside);
	
	if(mMouseIsDown)
	{
		int id = mouseToPadId(mouseToFraction(inside));
		
		if (mDisplay == kofxGui_Button_Trigger)
			mBuffer[id]	|= kofxGui_Matrix_Set;	// = 1;
		else
			mBuffer[id]	^= kofxGui_Matrix_Set;	// !mBuffer[id];
		
		setValue(id);
		
		ofCell outVal = ofCell(mValue, mBuffer[mValue]);
		mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Cell, &outVal, sizeof(ofCell));
	}
	
	return mMouseIsDown;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiMatrix::mouseReleased(int x, int y, int button)
{
	bool handled = mMouseIsDown;
	
	if(mMouseIsDown)
	{
		if(mDisplay == kofxGui_Button_Trigger)
		{
			mBuffer[mValue] ^= kofxGui_Matrix_Set;	//	= 0;
			mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Int, &mValue, sizeof(int));
		}
		
		mMouseIsDown = false;
	}
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiMatrix::buildFromXml()
{
	int numberOfTags = mGlobals->mXml.getNumTags("PAD");
	
	if(numberOfTags > 0)
	{
		memset(mBuffer, 0, sizeof(int) * mBufferLength);
		
		for(int i = 0; i < numberOfTags; i++)
		{
			mGlobals->mXml.pushTag("PAD", i);
			
			int	j	= mGlobals->mXml.getValue("INDEX", 0);
			int	v	= mGlobals->mXml.getValue("VALUE", 0);
			
			if(j < mBufferLength)
			   mBuffer[j] = v;
			
			mGlobals->mXml.popTag();
		}
	}

	mGlobals->mListener->handleGui(mParamId, kofxGui_Set_Int, &mValue, sizeof(int));
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiMatrix::saveToXml()
{
	int id = saveObjectData();
	
	mGlobals->mXml.setValue("OBJECT:XGRID", mXGrid, id);
	mGlobals->mXml.setValue("OBJECT:YGRID", mYGrid, id);
	mGlobals->mXml.setValue("OBJECT:VALUE", mValue, id);
	mGlobals->mXml.setValue("OBJECT:SPACING", mSpacing, id);

	mGlobals->mXml.pushTag("OBJECT", id);
	
	for(int i = 0; i < mBufferLength; i++)
	{
		int v = mBuffer[i];
		
		if(v == 0)
			continue;
		
		id = mGlobals->mXml.addTag("PAD");
		
		mGlobals->mXml.setValue("PAD:INDEX", i, id);
		mGlobals->mXml.setValue("PAD:VALUE", v, id);
	}
	
	mGlobals->mXml.popTag();
}

//	----------------------------------------------------------------------------------------------------

int ofxGuiMatrix::mouseToPadId(ofxPoint2f point)
{
	float x = (int)(point.x * mXGrid);
	float y = (int)(point.y * mYGrid);

	return x + (y * mXGrid); 
}

//	----------------------------------------------------------------------------------------------------
