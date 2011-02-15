#include "boxAlign.h"


CBoxAligner::CBoxAligner()
{

}
//--------------------------------------------------------------
CBoxAligner::~CBoxAligner()
{

}
//--------------------------------------------------------------
void CBoxAligner::setup()
{	  
       for(int i = 0; i < 4; i++)
       {
               fHandles[i].x = 0.0f;
               fHandles[i].y = 0.0f;
       }
       
       fDrawOffset.x = 0.0f;
       fDrawOffset.y = 0.0f;        
}
//--------------------------------------------------------------
void CBoxAligner::setup( int x, int y, float w, float h, float resW, float resH)
{
       
       
       // sets up the handles to be a box from 0,0 to the width and height of the image
       
       fHandles[0].x = 0.0f;
       fHandles[0].y = h;
       
       fHandles[1].x = w;
       fHandles[1].y = h;
       
       fHandles[2].x = w;
       fHandles[2].y = 0.0f;
       
       fHandles[3].x = 0.0f;
       fHandles[3].y = 0.0f;
       
       // this indicates the offset from 0,0 that the image is draw to the screen
       
       fDrawOffset.x = x;
       fDrawOffset.y = y;

	   resWidth = resW;
	   resHeight = resH;
       
}
//--------------------------------------------------------------
void CBoxAligner::adjustHandle(float mouseX, float mouseY)
{	 
   	
    // find out which handle is closest to mouse and adjust that one   
    int iHandle = 	findClosestHandle( mouseX * resWidth,  mouseY * resHeight);
   	
   	// account for the offset in mouse position based on where the handles are drawn
    fHandles[iHandle].x = (mouseX * resWidth) - (fDrawOffset.x * resWidth);
    fHandles[iHandle].y = (mouseY * resHeight) - (fDrawOffset.y * resHeight);
    
        
}
//--------------------------------------------------------------
float CBoxAligner::findSelectionDistance(float mouseX, float mouseY)
{
// subtract the draw position so that mouse input makes sense
   mouseX -= fDrawOffset.x;
   mouseY -= fDrawOffset.y;
        
   float     closeDist    = sqrt( (fHandles[0].x-mouseX)*(fHandles[0].x-mouseX) + (fHandles[0].y-mouseY)*(fHandles[0].y-mouseY) );
   
   for( int i = 1; i < 4; i++)
   {
        float d = sqrt( (fHandles[i].x-mouseX)*(fHandles[i].x-mouseX) + (fHandles[i].y-mouseY)*(fHandles[i].y-mouseY) );
        if( d < closeDist )
        {
         closeDist = d;
        }
        
   }
    
   return closeDist;	
}
//--------------------------------------------------------------
int  CBoxAligner::findClosestHandle(float mouseX, float mouseY)
{	 
   
   // subtract the draw position so that mouse input makes sense
   mouseX -= fDrawOffset.x;
   mouseY -= fDrawOffset.y;
        
   // start with the first handle
   int       iCloseId      = 0;
   float     fCloseDist    = sqrt( (fHandles[0].x-mouseX)*(fHandles[0].x-mouseX) + (fHandles[0].y-mouseY)*(fHandles[0].y-mouseY) );
   
   // loop to see which is closest
   for( int i = 1; i < 4; i++)
   {
        
        float fDist = sqrt( (fHandles[i].x-mouseX)*(fHandles[i].x-mouseX) + (fHandles[i].y-mouseY)*(fHandles[i].y-mouseY) );
        
        if( fDist < fCloseDist )
        {
         fCloseDist = fDist;
         iCloseId   = i;
        }
        
   }
   
   // return id of closest 
   return iCloseId;		
}
//--------------------------------------------------------------
void CBoxAligner::draw( int x, int y, float radius )
{	 
		glPushMatrix();
        
        glTranslatef(fDrawOffset.x,fDrawOffset.y,0.0f);
        
        ofSetColor(0x89ff41);
        
        // draw box
		glBegin( GL_LINE_STRIP );
		         glVertex2f(fHandles[0].x/resWidth, fHandles[0].y/resHeight);
		         glVertex2f(fHandles[1].x/resWidth, fHandles[1].y/resHeight);
	             glVertex2f(fHandles[2].x/resWidth, fHandles[2].y/resHeight);
		         glVertex2f(fHandles[3].x/resWidth, fHandles[3].y/resHeight);
		         glVertex2f(fHandles[0].x/resWidth, fHandles[0].y/resHeight);
        glEnd();
		
		// draw handles
		for( int i = 0; i < 4; i++)
        {  
             ofCircle( fHandles[i].x/resWidth, fHandles[i].y/resHeight, radius);
        }
		
		glPopMatrix();
}
