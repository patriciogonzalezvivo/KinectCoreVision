#ifndef _CBOXALIGN_
#define _CBOXALIGN_


#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxVectorMath.h"

/*
Creates a grid of 4 handles that can be moved around to define a projection area

0-----1
|     | 
|     |
3-----2

*/

class CBoxAligner {
	
	public:
		
		CBoxAligner();
		~CBoxAligner();
		
		void           setup();
		void           setup( int x, int y, float w, float h, float resW, float resH);
        
        // moves a handle to mouse position
        void           adjustHandle(float mouseX, float mouseY );
         
        // returns the id of the handle that is closest to the mouse position
        int            findClosestHandle(float mouseX, float mouseY);
        
        // returns the  distance of mouse pointer to closest handle
        float          findSelectionDistance(float mouseX, float mouseY);
        
        // draw handles to screen and sets draw offsets to x,y
        void           draw( int x, int y, float radius = 4.0f );
        
        
        float          getTopLeftX(){ return fHandles[0].x; }
        float          getTopLeftY(){ return fHandles[0].y; }
        float          getBottomLeftX(){ return fHandles[3].x; }
        float          getBottomLeftY(){ return fHandles[3].y; }
        float          getTopRightX(){ return fHandles[1].x; }
        float          getTopRightY(){ return fHandles[1].y; }
        float          getBottomRightX(){ return fHandles[2].x; }
        float          getBottomRightY(){ return fHandles[2].y; }
        
		float			resWidth;
		float			resHeight;
       
	   		
        ofxPoint2f      fHandles[4];
        ofxPoint2f      fDrawOffset;
       
		 
      
}; 

#endif	
