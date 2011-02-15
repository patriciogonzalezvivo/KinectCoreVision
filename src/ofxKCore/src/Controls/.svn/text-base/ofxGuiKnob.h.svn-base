/*
 *  ofxGuiKnob.h
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI_KNOB
#define OFX_GUI_KNOB

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiTypes.h"
#include "ofxGuiObject.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiKnob : public ofxGuiObject
	{
		
	public:
		
		ofxGuiKnob();
		
		void		init(int id, string name, int x, int y, int width, int height, float min, float max, float value, int display, int steps);
		
		void		setValue(float value);
		void		setRange(float min, float max);
		
		bool		update(int id, int task, void* data, int length);
		void		draw();
		
		bool		mouseDragged(int x, int y, int button);
		bool		mousePressed(int x, int y, int button);
		bool		mouseReleased(int x, int y, int button);
		
		void		buildFromXml();
		void		saveToXml();
		
		float		valueToFraction(float value);
		float		fractionToValue(float fraction);
				
		void		drawValueString(float x, float y, string text);

		float		mValue, mMinVal, mMaxVal, mValDlt;
		ofxPoint2f	mFirstHit;
	};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
