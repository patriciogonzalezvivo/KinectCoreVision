/*
 *  ofxGuiGlobals.h
 *  openFrameworks
 *
 *  Created by Stefan Kirch on 18.06.08.
 *  Copyright 2008 alphakanal. All rights reserved.
 *
 */

//	----------------------------------------------------------------------------------------------------

#ifndef OFX_GUI_GLOBALS
#define OFX_GUI_GLOBALS

//	----------------------------------------------------------------------------------------------------

#include "ofxGuiTypes.h"

//	----------------------------------------------------------------------------------------------------

class ofxGuiGlobals
{
		
public:
	
	static			ofxGuiGlobals* Instance();
	
	void			buildFromXml();
	void			saveToXml();

	void			loadFonts();
	
	ofxGuiListener*	mListener;

	ofTrueTypeFont	mHeadFont;
	ofTrueTypeFont	mParamFont;
	
	ofxXmlSettings	mXml;
	ofxDirList		mDir;

	string			mXmlfile;
	
	string			mHeadFontName;
	int				mHeadFontSize;
	int				mHeadFontXOffset;
	int				mHeadFontYOffset;
	int				mHeadFontHeight;
	
	string			mParamFontName;
	int				mParamFontSize;
	int				mParamFontXOffset;
	int				mParamFontYOffset;
	int				mParamFontHeight;

	int				mButtonXText;
	int				mButtonYText;
	
	int				mFilesXText;
	int				mFilesYText;
	
	int				mPointSize;
	
	int				mKnobSize;
	
	ofRGBA			mCoverColor, mTextColor, mBorderColor, mFrameColor, mSliderColor, mAxisColor, mHandleColor, mButtonColor, mCurveColor, mScopeColor, mMatrixColor;

private:
	
	ofxGuiGlobals();	
};

//	----------------------------------------------------------------------------------------------------

#endif

//	----------------------------------------------------------------------------------------------------
