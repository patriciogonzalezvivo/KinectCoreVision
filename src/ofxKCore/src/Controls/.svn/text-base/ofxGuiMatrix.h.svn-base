/*
 *  ofxGuiMatrix.h
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI_MATRIX
#define OFX_GUI_MATRIX

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiTypes.h"
#include "ofxGuiObject.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiMatrix : public ofxGuiObject
{
public:
	
	 ofxGuiMatrix();
	~ofxGuiMatrix();
	
	void	init(int id, string name, int x, int y, int width, int height, int xGrid, int yGrid, int value, int mode, int spacing);
	
	void	setValue(int value);
	
	bool	update(int id, int task, void* data, int length);
	void	draw();
	
	bool	mouseDragged(int x, int y, int button);
	bool	mousePressed(int x, int y, int button);
	bool	mouseReleased(int x, int y, int button);
	
	void	buildFromXml();
	void	saveToXml();
			
	int		mouseToPadId(ofxPoint2f point);
	
	int		mValue;
	int		mXGrid, mYGrid, mSpacing;

	int*	mBuffer;
	int		mBufferLength;
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
