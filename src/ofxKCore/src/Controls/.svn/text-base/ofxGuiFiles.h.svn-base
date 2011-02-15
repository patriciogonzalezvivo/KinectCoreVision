/*
 *  ofxGuiFiles.h
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI_FILES
#define OFX_GUI_FILES

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiTypes.h"
#include "ofxGuiObject.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiFiles : public ofxGuiObject
{
	
public:
	
	ofxGuiFiles();
	
	void	init(int id, string name, int x, int y, int width, int height, string value, string subPath, string suffix);
	
	void	setValue(string value);
	
	bool	update(int id, int task, void* data, int length);
	void	draw();
	
	bool	mouseDragged(int x, int y, int button);
	bool	mousePressed(int x, int y, int button);
	bool	mouseReleased(int x, int y, int button);
	
	void	buildFromXml();
	void	saveToXml();
	
	float	valueToFraction(float value);
	float	fractionToValue(float fraction);

	int		getFileList();
	
	int		mSelected, mNumberOfFiles;
	string	mValue, mMemory, mPath, mSuffix;
		
	vector	<string> mFilelist;
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
