/*
* Blob.h
*
*
* A blob is a homogenous patch represented by a polygonal contour.
* Typically a blob tracker uses the contour to figure out the blob's
* persistence and "upgrades" it with ids and other temporal
* information.
*
*/

#ifndef BLOB_H
#define BLOB_H

#include <vector>

class Blob {

    public: 

        vector <ofPoint>    pts;     // the contour of the blob
        int                 nPts;    // number of pts;
		int					id;
	    float               area;
        float               length;
		float               angle;
		float				maccel;  //distance traveled since last frame
		float				age;     //how long the blob has been at war
		float				sitting; //how long hes been sitting in the same place
		float				downTime;
		float				lastTimeTimeWasChecked;
	    ofRectangle         boundingRect;
		ofRectangle         angleBoundingRect;
		CvBox2D				angleBoundingBox;
		ofPoint             centroid, lastCentroid, D;
		bool				simulated;
		bool				isObject;
		bool                hole;
		int					color;				

        //----------------------------------------
        Blob() 
		{
            area 		= 0.0f;
            length 		= 0.0f;
            hole 		= false;
            nPts        = 0;
			simulated	= false;
			age			= 0.0f;
			sitting		= 0.0f;
			color		= 0xFFFFFF;
			isObject	= false;
			
			//freakishly long variable name (ala Apple)
			lastTimeTimeWasChecked = ofGetElapsedTimeMillis(); //get current time as of creation
        }

        //----------------------------------------
        void drawContours(float x = 0, float y = 0, float inputWidth = ofGetWidth(), float inputHeight = ofGetHeight(), float outputWidth = ofGetWidth(), float outputHeight = ofGetHeight()) 
		{
            glPushMatrix();
                glTranslatef(x + angleBoundingRect.x/inputWidth * outputWidth, y + angleBoundingRect.y/inputHeight * outputHeight, 0.0f);
                glRotatef(-angle, 0.0f, 0.0f, 1.0f);
                glTranslatef(-(x + angleBoundingRect.x/inputWidth * outputWidth), -(y + angleBoundingRect.y/inputHeight * outputHeight), 0.0f);                
				
					//ofSetColor(0xFFFFFF);
					//ofRect(x + (angleBoundingRect.x - angleBoundingRect.width/2)/inputWidth * outputWidth, y + (angleBoundingRect.y - angleBoundingRect.height/2)/inputHeight * outputHeight, angleBoundingRect.width/inputWidth * outputWidth, angleBoundingRect.height/inputHeight * outputHeight);
				
					ofSetColor(0x0099FF);
					ofRect(x + (angleBoundingRect.x/inputWidth) * outputWidth, y + ((angleBoundingRect.y - angleBoundingRect.height)/inputHeight) * outputHeight, 1, (angleBoundingRect.height * 2)/inputHeight * outputHeight); //Vertical Plus
					ofRect(x + ((angleBoundingRect.x - angleBoundingRect.width)/inputWidth) * outputWidth, y + (angleBoundingRect.y/inputHeight) * outputHeight, (angleBoundingRect.width * 2)/inputWidth * outputWidth, 1); //Horizontal Plus

            glPopMatrix();

			//draw contours
			ofNoFill();
            ofSetColor(0xFF0099);
            ofBeginShape();
            for (int i = 0; i < nPts; i++)
                   ofVertex(x + pts[i].x/inputWidth * outputWidth, y + pts[i].y/(inputHeight) * outputHeight);
            ofEndShape(true);	
        }

		void drawBox(float x = 0, float y = 0, float inputWidth = ofGetWidth(), float inputHeight = ofGetHeight(), float outputWidth = ofGetWidth(), float outputHeight = ofGetHeight())
		{		
         glPushMatrix();
         glTranslatef(x + angleBoundingRect.x/inputWidth * outputWidth, y + angleBoundingRect.y/inputHeight * outputHeight, 0.0f);
         glRotatef(-angle, 0.0f, 0.0f, 1.0f);
         glTranslatef(-(x + angleBoundingRect.x/inputWidth * outputWidth), -(y + angleBoundingRect.y/inputHeight * outputHeight), 0.0f);                
		 ofNoFill();
		 
		 ofSetColor(0xFFFFFF);
		 ofRect(x + (angleBoundingRect.x - angleBoundingRect.width/2)/inputWidth * outputWidth, y + (angleBoundingRect.y - angleBoundingRect.height/2)/inputHeight * outputHeight, angleBoundingRect.width/inputWidth * outputWidth, angleBoundingRect.height/inputHeight * outputHeight);

		 glPopMatrix();
		}
};
#endif


