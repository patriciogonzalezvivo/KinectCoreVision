/*
 *  ofxGuiSwitch.h
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI_SWITCH
#define OFX_GUI_SWITCH

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiTypes.h"
#include "ofxGuiObject.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiSwitch : public ofxGuiObject
	{
		
	public:
		
		ofxGuiSwitch();
		
		void			init(int id, string name, int x, int y, int width, int height, int min, int max, int value, const string* paramStrings);
		
		void			setValue(int value);
		void			setRange(int min, int max);
		
		bool			update(int id, int task, void* data, int length);
		void			draw();
		
		bool			mouseDragged(int x, int y, int button);
		bool			mousePressed(int x, int y, int button);
		bool			mouseReleased(int x, int y, int button);
		
		void			buildFromXml();
		void			saveToXml();
		
		int				fractionToValue(float fraction);
		
		int				mValue, mMinVal, mMaxVal, mValDlt;
		vector			<string>mParamStrings;
	};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
