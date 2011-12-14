/*
 *  ofxGuiPanel.cpp
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiPanel.h"

//	----------------------------------------------------------------------------------------------------

ofxGuiPanel::ofxGuiPanel()
{
	mParamType = kofxGui_Object_Panel;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiPanel::init(int id, string name, int x, int y, int border, int spacing)
{
	int	textHeight	= (name == "") ? 2 * border :  2 * border +mGlobals->mHeadFontHeight;

	mParamId		= id;
	mParamName		= name;

	mObjX			= x; 
	mObjY			= y;

	mBorder			= border;
	mSpacing		= spacing;
	
	adjustToNewContent(roundInt(mGlobals->mHeadFont.stringWidth(name)), textHeight);
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiPanel::update(int parameterId, int task, void* data, int length)
{
	bool			handled	= false;
	ofxGuiObject*	tmpObj	= NULL;
	
	for(int i = 0; i < mObjects.size(); i++)
	{
		tmpObj	= (ofxGuiObject*)mObjects.at(i);
		handled	= tmpObj->update(parameterId, task, data, length);
		
		if(handled)
			break;
	}
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiPanel::draw()
{
	glPushMatrix();
		
		glTranslatef(mObjX, mObjY, 0.0f);

		ofFill();
		
		//	background
		glColor4f(mGlobals->mCoverColor.r, mGlobals->mCoverColor.g, mGlobals->mCoverColor.b, mGlobals->mCoverColor.a);
		ofRect(0.0f, 0.0f, mObjWidth, mObjHeight);
	
		ofNoFill();
		
		if(mParamName != "")
			drawHeadString(mBorder, mBorder, mParamName, false);

		if(mBorder > 0)
		{
			//	border
			glColor4f(mGlobals->mBorderColor.r, mGlobals->mBorderColor.g, mGlobals->mBorderColor.b, mGlobals->mBorderColor.a);
			ofRect(0.0f, 0.0f, mObjWidth, mObjHeight);
		}
	
		ofxGuiObject* tmpObj;
	
		for(int i = 0; i < mObjects.size(); i++)
		{
			tmpObj = (ofxGuiObject*)mObjects.at(i);
			tmpObj->draw();
		}
	
	glPopMatrix();
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiPanel::mouseDragged(int x, int y, int button)
{
	bool handled = false;
	
	if(mMouseIsDown)
	{		
		ofPoint inside = mouseToLocal(x, y);
		
		ofxGuiObject* tmpObj;
		
		for(int i = 0; i < mObjects.size(); i++)
		{
			tmpObj	= (ofxGuiObject*)mObjects.at(i);
			handled	= tmpObj->mouseDragged(inside.x, inside.y, button);
			
			if(handled)
				break;
		}
	}
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiPanel::mousePressed(int x, int y, int button)
{
	bool		handled	= false;
	ofPoint	inside	= mouseToLocal(x, y);
	
	if(isPointInsideMe(inside))
	{		
		ofxGuiObject* tmpObj;
		
		for(int i = 0; i < mObjects.size(); i++)
		{
			tmpObj	= (ofxGuiObject*)mObjects.at(i);
			handled	= tmpObj->mousePressed(inside.x, inside.y, button);
			
			if(handled)
				break;
		}
		
		mMouseIsDown = true;
	}
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

bool ofxGuiPanel::mouseReleased(int x, int y, int button)
{
	bool		handled	= false;
	ofPoint	inside	= mouseToLocal(x, y);
	
	ofxGuiObject* tmpObj;
	
	for(int i = 0; i < mObjects.size(); i++)
	{
		tmpObj	= (ofxGuiObject*)mObjects.at(i);
		handled	= tmpObj->mouseReleased(inside.x, inside.y, button);
		
		if(handled)
			break;
	}
	
	mMouseIsDown = false;
	
	return handled;
}

//	----------------------------------------------------------------------------------------------------

ofxGuiObject* ofxGuiPanel::addSlider(int id, string name, int width, int height, float min, float max, float value, int display, int steps)
{
	int offset = (mObjects.size() == 0 && mParamName == "") ? 0 : mSpacing;
	
	ofxGuiSlider* slider = new ofxGuiSlider();
	slider->init(id, name, mBorder, mObjHeight - mBorder + offset, width, height, min, max, value, display, steps);
	mObjects.push_back(slider);

	adjustToNewContent(slider->mObjWidth, slider->mObjHeight + offset);
	
	return slider;
}

//	----------------------------------------------------------------------------------------------------

ofxGuiObject* ofxGuiPanel::addXYPad(int id, string name, int width, int height, ofPoint min, ofPoint max, ofPoint value, int display, int steps)
{
	int offset = (mObjects.size() == 0 && mParamName == "") ? 0 : mSpacing;

	ofxGuiXYPad* xypad = new ofxGuiXYPad();
	xypad->init(id, name, mBorder, mObjHeight - mBorder + offset, width, height, min, max, value, display, steps);
	mObjects.push_back(xypad);
	
	adjustToNewContent(xypad->mObjWidth, xypad->mObjHeight + offset);
	
	return xypad;
}

//	----------------------------------------------------------------------------------------------------

ofxGuiObject* ofxGuiPanel::addPoints(int id, string name, int width, int height, ofPoint min, ofPoint max, ofPoint value, int display, int steps)
{
	int offset = (mObjects.size() == 0 && mParamName == "") ? 0 : mSpacing;

	ofxGuiPoints* points = new ofxGuiPoints();
	points->init(id, name, mBorder, mObjHeight - mBorder + offset, width, height, min, max, value, display, steps);
	mObjects.push_back(points);
	
	adjustToNewContent(points->mObjWidth, points->mObjHeight + offset);
	
	return points;
}

//	----------------------------------------------------------------------------------------------------

ofxGuiObject* ofxGuiPanel::addButton(int id, string name, int width, int height, bool value, int display)
{
	int offset = (mObjects.size() == 0 && mParamName == "") ? 0 : mSpacing;

	ofxGuiButton* button = new ofxGuiButton();
	button->init(id, name, mBorder, mObjHeight - mBorder + offset, width, height, value, display);
	mObjects.push_back(button);
	
	adjustToNewContent(button->mObjWidth, button->mObjHeight + offset);
	
	return button;
}

//	----------------------------------------------------------------------------------------------------

ofxGuiObject* ofxGuiPanel::addFiles(int id, string name, int width, int height, string value, string subPath, string suffix)
{
	int offset = (mObjects.size() == 0 && mParamName == "") ? 0 : mSpacing;

	ofxGuiFiles* files = new ofxGuiFiles();
	files->init(id, name, mBorder, mObjHeight - mBorder + offset, width, height, value, subPath, suffix);
	mObjects.push_back(files);
	
	adjustToNewContent(files->mObjWidth, files->mObjHeight + offset);
	
	return files;
}

//	----------------------------------------------------------------------------------------------------

ofxGuiObject* ofxGuiPanel::addColor(int id, string name, int width, int height, ofRGBA value, int display)
{
	int offset = (mObjects.size() == 0 && mParamName == "") ? 0 : mSpacing;
	
	ofxGuiColor* color = new ofxGuiColor();
	color->init(id, name, mBorder, mObjHeight - mBorder + offset, width, height, value, display);
	mObjects.push_back(color);
	
	adjustToNewContent(color->mObjWidth, color->mObjHeight + offset);
	
	return color;
}

//	----------------------------------------------------------------------------------------------------

ofxGuiObject* ofxGuiPanel::addMatrix(int id, string name, int width, int height, int xGrid, int yGrid, int value, int mode, int spacing)
{
	int offset = (mObjects.size() == 0 && mParamName == "") ? 0 : mSpacing;
	
	ofxGuiMatrix* matrix = new ofxGuiMatrix();
	matrix->init(id, name, mBorder, mObjHeight - mBorder + offset, width, height, xGrid, yGrid, value, mode, spacing);
	mObjects.push_back(matrix);
	
	adjustToNewContent(matrix->mObjWidth, matrix->mObjHeight + offset);
	
	return matrix;
}

//	----------------------------------------------------------------------------------------------------

ofxGuiObject* ofxGuiPanel::addScope(int id, string name, int width, int height, int length, ofPoint value, int display)
{
	int offset = (mObjects.size() == 0 && mParamName == "") ? 0 : mSpacing;
	
	ofxGuiScope* scope = new ofxGuiScope();
	scope->init(id, name, mBorder, mObjHeight - mBorder + offset, width, height, length, value, display);
	mObjects.push_back(scope);
	
	adjustToNewContent(scope->mObjWidth, scope->mObjHeight + offset);
	
	return scope;
}

//	----------------------------------------------------------------------------------------------------

ofxGuiObject* ofxGuiPanel::addKnob(int id, string name, int width, int height, float min, float max, float value, int display, int steps)
{
	int offset = (mObjects.size() == 0 && mParamName == "") ? 0 : mSpacing;
	
	ofxGuiKnob* knob = new ofxGuiKnob();
	knob->init(id, name, mBorder, mObjHeight - mBorder + offset, width, height, min, max, value, display, steps);
	mObjects.push_back(knob);
	
	adjustToNewContent(knob->mObjWidth, knob->mObjHeight + offset);
	
	return knob;
}

//	----------------------------------------------------------------------------------------------------

ofxGuiObject* ofxGuiPanel::addRadar(int id, string name, int width, int height, float min, float max, float value, int display, int steps)
{
	//	todo
	return NULL;
}

//	----------------------------------------------------------------------------------------------------

ofxGuiObject* ofxGuiPanel::addSwitch(int id, string name, int width, int height, int min, int max, int value, const string* paramStrings)
{
	int offset = (mObjects.size() == 0 && mParamName == "") ? 0 : mSpacing;
	
	ofxGuiSwitch* swtch = new ofxGuiSwitch();
	swtch->init(id, name, mBorder, mObjHeight - mBorder + offset, width, height, min, max, value, paramStrings);
	mObjects.push_back(swtch);
	
	adjustToNewContent(swtch->mObjWidth, swtch->mObjHeight + offset);
	
	return swtch;
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiPanel::adjustToNewContent(int width, int height)
{
	if(width > mObjWidth - mBorder * 2)
		mObjWidth = width + mBorder * 2;

	mObjHeight += height;
	
	setControlRegion(mBorder, mBorder, mObjWidth - mBorder, mObjHeight - mBorder);
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiPanel::buildFromXml()
{
	int numberOfTags = mGlobals->mXml.getNumTags("OBJECT");
	
	if(numberOfTags > 0)
	{
		for(int i = 0; i < numberOfTags; i++)
		{
			mGlobals->mXml.pushTag("OBJECT", i);

			int		id		= mGlobals->mXml.getValue("ID", 0);
			string	type	= mGlobals->mXml.getValue("TYPE", "");
			string	name	= mGlobals->mXml.getValue("NAME", "");
			int		width	= mGlobals->mXml.getValue("WIDTH", 0);
			int		height	= mGlobals->mXml.getValue("HEIGHT", 0);
			int		display	= mGlobals->mXml.getValue("DISPLAY", 0);
			int		steps	= mGlobals->mXml.getValue("STEPS", 0);
			int		mode	= mGlobals->mXml.getValue("MODE", 0);
			
			if(type == "SLIDER")
			{
				float	min		= mGlobals->mXml.getValue("MIN", 0.0f);
				float	max		= mGlobals->mXml.getValue("MAX", 0.0f);
				float	value	= mGlobals->mXml.getValue("VALUE", 0.0f);

				ofxGuiObject* slider = addSlider(id, name, width, height, min, max, value, display, steps);
				slider->buildFromXml();
			}
			else if(type == "XYPAD")
			{
				float	minx		= mGlobals->mXml.getValue("MIN_X", 0.0f);
				float	miny		= mGlobals->mXml.getValue("MIN_Y", 0.0f);
				float	maxx		= mGlobals->mXml.getValue("MAX_X", 0.0f);
				float	maxy		= mGlobals->mXml.getValue("MAX_Y", 0.0f);
				float	valuex		= mGlobals->mXml.getValue("VALUE_X", 0.0f);
				float	valuey		= mGlobals->mXml.getValue("VALUE_Y", 0.0f);
				
				ofPoint min		= ofPoint(minx, miny);
				ofPoint max		= ofPoint(maxx, maxy);
				ofPoint value	= ofPoint(valuex, valuey);
				
				ofxGuiObject* xypad = addXYPad(id, name, width, height, min, max, value, display, steps);
				xypad->buildFromXml();
			}
			else if(type == "POINTS")
			{
				float	minx		= mGlobals->mXml.getValue("MIN_X", 0.0f);
				float	miny		= mGlobals->mXml.getValue("MIN_Y", 0.0f);
				float	maxx		= mGlobals->mXml.getValue("MAX_X", 0.0f);
				float	maxy		= mGlobals->mXml.getValue("MAX_Y", 0.0f);
				float	valuex		= mGlobals->mXml.getValue("VALUE_X", 0.0f);
				float	valuey		= mGlobals->mXml.getValue("VALUE_Y", 0.0f);
				
				ofPoint min		= ofPoint(minx, miny);
				ofPoint max		= ofPoint(maxx, maxy);
				ofPoint value	= ofPoint(valuex, valuey);
				
				ofxGuiObject* points = addPoints(id, name, width, height, min, max, value, display, steps);
				points->buildFromXml();
			}
			else if(type == "BUTTON")
			{
				bool value = mGlobals->mXml.getValue("VALUE", 0);
				
				ofxGuiObject* button = addButton(id, name, width, height, value, mode);
				button->buildFromXml();
			}
			else if(type == "FILES")
			{
				string	subPath	= mGlobals->mXml.getValue("SUBPATH", "");
				string	suffix	= mGlobals->mXml.getValue("SUFFIX", "");
				
				ofxGuiObject* files = addFiles(id, name, width, height, mGlobals->mXmlfile, subPath, suffix);
				files->buildFromXml();
			}
			else if(type == "COLOR")
			{
				ofRGBA value = ofRGBA(mGlobals->mXml.getValue("VALUE", "FFFFFFFF"));
				
				ofxGuiObject* color = addColor(id, name, width, height, value, mode);
				color->buildFromXml();
			}
			else if(type == "MATRIX")
			{
				int	xGrid	= mGlobals->mXml.getValue("XGRID", 0);
				int	yGrid	= mGlobals->mXml.getValue("YGRID", 0);
				int	value	= mGlobals->mXml.getValue("VALUE", 0);
				int	spacing	= mGlobals->mXml.getValue("SPACING", 0);
				
				ofxGuiObject* matrix = addMatrix(id, name, width, height, xGrid, yGrid, value, mode, spacing);

				matrix->buildFromXml();
			}
			else if(type == "SCOPE")
			{
				int			length	= mGlobals->mXml.getValue("LENGTH", 0);
				float		valuex	= mGlobals->mXml.getValue("VALUE_X", 0.0f);
				float		valuey	= mGlobals->mXml.getValue("VALUE_Y", 0.0f);
				ofPoint	value	= ofPoint(valuex, valuey);
				
				ofxGuiObject* scope = addScope(id, name, width, height, length, value, mode);
				scope->buildFromXml();
			}
			else if(type == "KNOB")
			{
				float	min		= mGlobals->mXml.getValue("MIN", 0.0f);
				float	max		= mGlobals->mXml.getValue("MAX", 0.0f);
				float	value	= mGlobals->mXml.getValue("VALUE", 0.0f);
				
				ofxGuiObject* knob = addKnob(id, name, width, height, min, max, value, display, steps);
				knob->buildFromXml();
			}
			else if(type == "SWITCH")
			{
				float	min		= mGlobals->mXml.getValue("MIN", 0.0f);
				float	max		= mGlobals->mXml.getValue("MAX", 0.0f);
				float	value	= mGlobals->mXml.getValue("VALUE", 0.0f);
				
				//	const string* strings = 
				
				ofxGuiObject* swtch = addSwitch(id, name, width, height, min, max, value, NULL);
				swtch->buildFromXml();
			}
			
			mGlobals->mXml.popTag();
		}
	}
}

//	----------------------------------------------------------------------------------------------------

void ofxGuiPanel::saveToXml()
{
	ofxGuiObject* tmpObj;
	
	int id = saveObjectData();
	
	mGlobals->mXml.setValue("OBJECT:BORDER", mBorder, id);
	mGlobals->mXml.setValue("OBJECT:SPACING", mSpacing, id);
	mGlobals->mXml.pushTag("OBJECT", id);
	
	for(int i = 0; i < mObjects.size(); i++)
	{
		tmpObj = (ofxGuiObject*)mObjects.at(i);
		tmpObj->saveToXml();
	}
	
	mGlobals->mXml.popTag();
}

//	----------------------------------------------------------------------------------------------------
