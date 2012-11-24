/*
*  Filters.h
*
*
*  Created on 2/2/09.
*  Copyright 2009 NUI Group. All rights reserved.
*
*/

#ifndef FILTERS_H_
#define FILTERS_H_

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "CPUImageFilter.h"

#define CAMERA_EXPOSURE_TIME  2200.0f

class Filters {
public:

    Filters(){
		camWidth = 320*2;
		camHeight = 240*2;
		exposureStartTime = CAMERA_EXPOSURE_TIME;

		//  filter values
        //
		threshold       = 120;
		smooth          = 0;
		highpassBlur    = 0;
		highpassNoise   = 0;
		highpassAmp     = 0;
		fLearnRate      = 1;
    }

    virtual void allocate( int w, int h ) = 0;
    virtual void applyFilters(CPUImageFilter& img, const ofPoint *src, const ofPoint *dst) = 0;
    virtual void draw() = 0;

    ofxCvGrayscaleImage original;
    ofxCvGrayscaleImage grayImg;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage subtractBg;
    ofxCvGrayscaleImage grayDiff;
    ofxCvGrayscaleImage highpassImg;
    ofxCvGrayscaleImage ampImg;
	ofxCvShortImage		floatBgImg;
    
    int camWidth;
    int camHeight;
    int exposureStartTime;

    //filter values
	int threshold;
    int smooth;
    int highpassBlur;
    int highpassNoise;
    int	highpassAmp;

    float fLearnRate;// rate to learn background

    //filter bools
	bool bLearnBackground;
	bool bVerticalMirror;
	bool bHorizontalMirror;
	bool bDynamicBG;
	bool bSmooth;
	bool bHighpass;
	bool bAmplify;
    bool bThreshold;
	bool bTrackDark;
    bool bLearnBakground;
	bool bMiniMode;
};


#endif
