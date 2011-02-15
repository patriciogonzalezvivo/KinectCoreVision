#ifndef _TEST_APP
#define _TEST_APP

//if standalone mode/non-addon
#define STANDALONE

//main
#include "ofMain.h"
//addon
#include "ofxKCore.h"

class testApp : public ofBaseApp, public TouchListener{
public:
	testApp(int argc, char *argv[]) 
	{
		debug = false;
		TouchEvents.addListener(this);
		if(argc==2)
		{
			printf("Command Line Option Passed : %s\n",argv[1]);
			if(strcmp(argv[1],"-d")==0)
			{
				debug = true;
			}
		}
	}
	ofxKCoreVision * ckv;
	bool debug;

	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased();

	//Touch Events
	void TouchDown(Blob b);
	void TouchMoved(Blob b);
	void TouchUp(Blob b);
};

#endif

