/*
 *  ofxGuiButton.h
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI_BUTTON
#define OFX_GUI_BUTTON

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiTypes.h"
#include "ofxGuiObject.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiButton : public ofxGuiObject
{
		
public:
	
	ofxGuiButton();
	
	void	init(int id, string name, int x, int y, int width, int height, bool value, int display);
	
	void	setValue(bool value);

	bool	update(int id, int task, void* data, int length);
	void	draw();
	
	bool	mouseDragged(int x, int y, int button);
	bool	mousePressed(int x, int y, int button);
	bool	mouseReleased(int x, int y, int button);
	
	void	buildFromXml();
	void	saveToXml();
	
	bool	mValue;
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
