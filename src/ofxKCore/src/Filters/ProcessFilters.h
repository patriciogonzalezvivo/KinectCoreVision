/*
*  ProcessFilters.h
*
*
*  Created on 2/2/09.
*  Copyright 2009 NUI Group. All rights reserved.
*
*/

#ifndef PROCESS_FILTERS_H_
#define PROCESS_FILTERS_H_

#include "Filters.h"

class ProcessFilters : public Filters {
public:

    void allocate( int w, int h ) {
        
        camWidth = w;
        camHeight = h;
        
		fLearnRate = 0.0f;
        bMiniMode = false;
        
		exposureStartTime = ofGetElapsedTimeMillis();
        
        original.allocate(camWidth, camHeight);     //  Original
        grayImg.allocate(camWidth, camHeight);		//  Gray Image
        grayBg.allocate(camWidth, camHeight);		//  Background Image
        subtractBg.allocate(camWidth, camHeight);   //  Background After subtraction
        grayDiff.allocate(camWidth, camHeight);		//  Difference Image between Background and Source
        highpassImg.allocate(camWidth, camHeight);  //  Highpass Image
        ampImg.allocate(camWidth, camHeight);		//  Amplied Image
        floatBgImg.allocate(camWidth, camHeight);	//  ofxShortImage used for simple dynamic background subtraction
        
    }
    
    void applyFilters(CPUImageFilter& img, const ofPoint *src, const ofPoint *dst){
        
        //  Set Mirroring Horizontal/Vertical
        //
        if (bVerticalMirror || bHorizontalMirror)
            img.mirror(bVerticalMirror, bHorizontalMirror);
        
        if (!bMiniMode)
            grayImg = img; //for drawing
        
        //  Warp
        //
        original = img;
        img.warpIntoMe( original , src, dst);
        
        //  Dynamic background with learn rate
        //
        if(bDynamicBG){
            floatBgImg.addWeighted( img, fLearnRate);
			//grayBg = floatBgImg;  // not yet implemented
            cvConvertScale( floatBgImg.getCvImage(), grayBg.getCvImage(), 255.0f/65535.0f, 0 );
            grayBg.flagImageChanged();
        }
        
        //  Recapature the background until image/camera is fully exposed
        //
        if((ofGetElapsedTimeMillis() - exposureStartTime) < CAMERA_EXPOSURE_TIME) bLearnBakground = true;
        
        //  Capture full background
        //
        if (bLearnBakground == true){
            floatBgImg = img;
			//grayBg = floatBgImg;  // not yet implemented
			cvConvertScale( floatBgImg.getCvImage(), grayBg.getCvImage(), 255.0f/65535.0f, 0 );
			grayBg.flagImageChanged();
            bLearnBakground = false;
        }
        
		//Background Subtraction
        //img.absDiff(grayBg, img);
        
		if(bTrackDark)
			cvSub(grayBg.getCvImage(), img.getCvImage(), img.getCvImage());
		else
			cvSub(img.getCvImage(), grayBg.getCvImage(), img.getCvImage());
        
		img.flagImageChanged();
        
		if(bSmooth){//Smooth
            img.blur((smooth * 2) + 1); //needs to be an odd number
            if(!bMiniMode)
                subtractBg = img; //for drawing
        }
        
        if(bHighpass){//HighPass
            img.highpass(highpassBlur, highpassNoise);
            if(!bMiniMode)
                highpassImg = img; //for drawing
        }
        
        if(bAmplify){//Amplify
            img.amplify(img, highpassAmp);
            if(!bMiniMode)
                ampImg = img; //for drawing
        }
        
        img.threshold(threshold); //Threshold
		//img.adaptiveThreshold(threshold, -3);
        
        if(!bMiniMode)
            grayDiff = img; //for drawing
    }
    
    void draw(){
//        grayImg.draw(30, 15, 320, 240);
        original.draw(30, 15, 320, 240);
        grayDiff.draw(375, 15, 320, 240);
        floatBgImg.draw(30, 392, 128, 96);
        subtractBg.draw(165, 392, 128, 96);
        highpassImg.draw(300, 392, 128, 96);
        ampImg.draw(435, 392, 128, 96);
    }

};
#endif
