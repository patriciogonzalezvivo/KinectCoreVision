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
		//initialize learnrate
		fLearnRate = 0.0f;
        bMiniMode = false;

		exposureStartTime = ofGetElapsedTimeMillis();

        //CPU Setup
        grayImg.allocate(camWidth, camHeight);		//Gray Image
        grayBg.allocate(camWidth, camHeight);		//Background Image
        subtractBg.allocate(camWidth, camHeight);   //Background After subtraction
        grayDiff.allocate(camWidth, camHeight);		//Difference Image between Background and Source
        highpassImg.allocate(camWidth, camHeight);  //Highpass Image
        ampImg.allocate(camWidth, camHeight);		//Amplied Image
        floatBgImg.allocate(camWidth, camHeight);	//ofxShortImage used for simple dynamic background subtraction

        //GPU Setup
		gpuReadBackBuffer = new unsigned char[camWidth*camHeight*3];
        gpuReadBackImageGS.allocate(camWidth, camHeight);
        //allocateGPU();
		//^^ Commented out for now, till full GPU implementation
    }

    void allocateGPU(){

        glGenTextures(1, &gpuSourceTex);
        glGenTextures(1, &gpuBGTex);

		delete gpuReadBackBuffer;

        gpuReadBackBuffer = new unsigned char[camWidth*camHeight*3];
        gpuReadBackImageGS.allocate(camWidth, camHeight);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, gpuSourceTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8,  camWidth, camHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glBindTexture(GL_TEXTURE_2D, gpuBGTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8,  camWidth, camHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

        subtractFilter = new GPUImageFilter("filters/absSubtract.xml", camWidth, camHeight);
        subtractFilter2 = new GPUImageFilter("filters/subtract.xml", camWidth, camHeight);
        contrastFilter = new GPUImageFilter("filters/contrast.xml", camWidth, camHeight);
        gaussVFilter = new GPUImageFilter("filters/gaussV.xml", camWidth, camHeight);
        gaussHFilter = new GPUImageFilter("filters/gauss.xml", camWidth, camHeight);
        gaussVFilter2 = new GPUImageFilter("filters/gaussV2.xml", camWidth, camHeight);
        gaussHFilter2 = new GPUImageFilter("filters/gauss2.xml", camWidth, camHeight);
        threshFilter = new GPUImageFilter("filters/threshold.xml", camWidth, camHeight);
        copyFilter = new GPUImageFilter("filters/copy.xml", camWidth, camHeight);
        grayScale = new GPUImageFilter("filters/grayScale.xml", camWidth, camHeight);
    }

/****************************************************************
 *	CPU Filters
 ****************************************************************/
     void applyCPUFilters(CPUImageFilter& img){

        //Set Mirroring Horizontal/Vertical
        if(bVerticalMirror || bHorizontalMirror) img.mirror(bVerticalMirror, bHorizontalMirror);

        if(!bMiniMode) grayImg = img; //for drawing

        //Dynamic background with learn rate
        if(bDynamicBG){
            floatBgImg.addWeighted( img, fLearnRate);
			//grayBg = floatBgImg;  // not yet implemented
			 cvConvertScale( floatBgImg.getCvImage(), grayBg.getCvImage(), 255.0f/65535.0f, 0 );       
			 grayBg.flagImageChanged();
        }

        //recapature the background until image/camera is fully exposed
        if((ofGetElapsedTimeMillis() - exposureStartTime) < CAMERA_EXPOSURE_TIME) bLearnBakground = true;

        //Capture full background
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

/****************************************************************
 *	GPU Filters
 ****************************************************************/
    void applyGPUFilters(){

        //recapature the background until image/camera is fully exposed
        if((ofGetElapsedTimeMillis() - exposureStartTime) < CAMERA_EXPOSURE_TIME) bLearnBakground = true;

        if (bLearnBakground == true){

            gpuBGTex = copyFilter->apply(gpuSourceTex, gpuBGTex);
            bLearnBakground = false;
        }

        GLuint processedTex;

        processedTex = subtractFilter->apply(gpuSourceTex, gpuBGTex);

        if(bSmooth){//Smooth
            gaussHFilter->parameters["kernel_size"]->value = (float)smooth;
            gaussVFilter->parameters["kernel_size"]->value = (float)smooth;
            processedTex = gaussHFilter->apply(processedTex);
            processedTex = gaussVFilter->apply(processedTex);
        }

        if(bHighpass){//Highpass
            gaussHFilter2->parameters["kernel_size"]->value = (float)highpassBlur;
            gaussVFilter2->parameters["kernel_size"]->value = (float)highpassBlur;
            processedTex = gaussHFilter2->apply(processedTex);
            processedTex = gaussVFilter2->apply(processedTex);

            if(bSmooth)
                processedTex = subtractFilter2->apply(gaussVFilter->output_texture, processedTex);
            else
                processedTex = subtractFilter2->apply(subtractFilter->output_texture, processedTex);
        }

        if(bAmplify){}//amplify

        threshFilter->parameters["Threshold"]->value = (float)threshold / 255.0; //threshold
        processedTex = threshFilter->apply(processedTex);

        //convert to grayscale so readback is faster. maybe do this from the start?
        grayScale->apply(processedTex);

        //until the rest of the pipeline is fixed well just download the preprocessing result from the gpu and use that for the blob detection
        //TODO: make this part not super slow ;)
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, threshFilter->output_buffer);
        glReadPixels(0,0,camWidth, camHeight, GL_LUMINANCE, GL_UNSIGNED_BYTE, gpuReadBackBuffer);
        gpuReadBackImageGS.setFromPixels(gpuReadBackBuffer, camWidth, camHeight);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    }

/****************************************************************
 *	Draw Filter Images
 ****************************************************************/
    void draw()
    {
        grayImg.draw(30, 15, 320, 240);
        grayDiff.draw(375, 15, 320, 240);
        floatBgImg.draw(30, 392, 128, 96);
        subtractBg.draw(165, 392, 128, 96);
        highpassImg.draw(300, 392, 128, 96);
        ampImg.draw(435, 392, 128, 96);
    }

    void drawGPU()
    {
        drawGLTexture(30, 15, 320, 240, gpuSourceTex);
        drawGLTexture(30, 392, 128, 96, gpuBGTex);
        gaussVFilter->drawOutputTexture(165, 392, 128, 96);
        subtractFilter2->drawOutputTexture(300, 392, 128, 96);
        threshFilter->drawOutputTexture(435, 392, 128, 96); //this should be amplify filter but we don't have one yet
        gpuReadBackImageGS.draw(375, 15, 320, 240);
    }
};
#endif
