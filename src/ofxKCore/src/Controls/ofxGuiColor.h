/*
 *  ofxGuiColor.h
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI_COLOR
#define OFX_GUI_COLOR

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiTypes.h"
#include "ofxGuiObject.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiColor : public ofxGuiObject
	{
		
	public:
		
		ofxGuiColor();
		
		void	init(int id, string name, int x, int y, int width, int height, ofRGBA value, int display);
		
		void	setValue(ofRGBA value);
		
		bool	update(int id, int task, void* data, int length);
		void	draw();
		
		bool	mouseDragged(int x, int y, int button);
		bool	mousePressed(int x, int y, int button);
		bool	mouseReleased(int x, int y, int button);
		
		void	buildFromXml();
		void	saveToXml();
		
		int		mouseToSlider(float y);

		int		mSize, mSlider;
		ofRGBA	mValue;
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
