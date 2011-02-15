/*
 *  ofxGuiScope.h
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI_SCOPE
#define OFX_GUI_SCOPE

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiTypes.h"
#include "ofxGuiObject.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiScope : public ofxGuiObject
{
	
public:
	
	 ofxGuiScope();
	~ofxGuiScope();
	
	void		init(int id, string name, int x, int y, int width, int height, int length, ofxPoint2f value, int mode);
	
	void		setValue(ofxPoint2f value);
	
	bool		update(int id, int task, void* data, int length);
	void		draw();
	
	bool		mouseDragged(int x, int y, int button);
	bool		mousePressed(int x, int y, int button);
	bool		mouseReleased(int x, int y, int button);
	
	void		buildFromXml();
	void		saveToXml();
		
	ofxPoint2f	valueToFraction(ofxPoint2f value);
	ofxPoint2f	fractionToValue(ofxPoint2f fraction);

	ofxPoint2f	mValue;
	
	float*		mBuffer;
	int			mBufferLength;
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
