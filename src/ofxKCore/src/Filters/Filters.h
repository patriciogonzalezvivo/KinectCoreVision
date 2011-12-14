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
//#include "GPUImageFilter.h"

#define CAMERA_EXPOSURE_TIME  2200.0f

class Filters {

	public:

	  Filters(){

		camWidth = 320*2;
		camHeight = 240*2;
		exposureStartTime = CAMERA_EXPOSURE_TIME;

		//filter values
		threshold = 120;
		smooth = 0;
		highpassBlur = 0;
		highpassNoise = 0;
		highpassAmp = 0;
		fLearnRate = 1;
	  }

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

    //CPU
    ofxCvGrayscaleImage grayImg;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage subtractBg;
    ofxCvGrayscaleImage grayDiff;
    ofxCvGrayscaleImage highpassImg;
    ofxCvGrayscaleImage ampImg;
	ofxCvShortImage		floatBgImg;


    //GPU
//    GLuint			gpuBGTex;
//    GLuint			gpuSourceTex;
//    ofxCvGrayscaleImage gpuReadBackImageGS;
//	unsigned char  * gpuReadBackBuffer;
//    GPUImageFilter * contrastFilter;
//    GPUImageFilter * subtractFilter;
//    GPUImageFilter * subtractFilter2; //we need 2 because we are showing the output of each
//    GPUImageFilter * gaussVFilter;
//    GPUImageFilter * gaussVFilter2;
//    GPUImageFilter * gaussHFilter;
//    GPUImageFilter * gaussHFilter2;
//    GPUImageFilter * threshFilter;
//    GPUImageFilter * copyFilter;
//    GPUImageFilter * grayScale;

    virtual void allocate( int w, int h ) = 0;
    virtual void applyCPUFilters(CPUImageFilter& img) = 0;
    virtual void draw() = 0;

//    virtual void allocateGPU() = 0;
//    virtual void applyGPUFilters() = 0;
//    virtual void drawGPU() = 0;
};


#endif
