/*
*  CalibrationUtils.cpp
*
*
*  Created on 2/2/09.
*  Copyright 2009 NUI Group. All rights reserved.
*
*/

#include "CalibrationUtils.h"
#include <cmath>


//set some default values
CalibrationUtils::CalibrationUtils()
{
	//Default values
	_camWidth = 320;
	_camHeight = 240;
}

CalibrationUtils::~CalibrationUtils()
{
    delete screenPoints;
	delete cameraPoints;
    delete triangles;
	delete cameraToScreenMap;
}

//--------------------------------------------------------------
//	Load Settings from the config.xml file
//--------------------------------------------------------------
void CalibrationUtils::loadXMLSettings()
{
	bGoToNextStep = false;

	// Can this load via http?
	if( calibrationXML.loadFile("calibration.xml"))
		//WOOT!
		message = "Calibration Loaded!";
	else
		//FAIL!
		message = "No calibration Found...";
		// GENERATE DEFAULT XML DATA WHICH WILL BE SAVED INTO THE CONFIG

	bool bboxRoot = true;
	bool screenRoot = true;

	bCalibrating = false;
	calibrationStep = 0;

	//Set grid and init everything that relates to teh grid
	GRID_X		= calibrationXML.getValue("SCREEN:GRIDMESH:GRIDX", 50);
	GRID_Y		= calibrationXML.getValue("SCREEN:GRIDMESH:GRIDY", 50);

	setGrid(GRID_X, GRID_Y);

	//Bounding Box Points
	if(bboxRoot)
	{
	    vector2df ul(calibrationXML.getValue("SCREEN:BOUNDINGBOX:ulx", 0.000000),calibrationXML.getValue("SCREEN:BOUNDINGBOX:uly", 0.000000));
	    vector2df lr(calibrationXML.getValue("SCREEN:BOUNDINGBOX:lrx", 1.000000),calibrationXML.getValue("SCREEN:BOUNDINGBOX:lry", 1.000000));
		rect2df boundingbox(ul, lr);
		setScreenBBox(boundingbox);
	}
	else
		setScreenScale(1.0f);

	//Calibration Points
	if(screenRoot)
	{
		//lets see how many <STROKE> </STROKE> tags there are in the xml file
		int numDragTags = calibrationXML.getNumTags("SCREEN:POINT");

		//if there is at least one <POINT> tag we can read the list of points
		if(numDragTags > 0)
		{
			//we push into the last POINT tag this temporarirly treats the tag as the document root.
			calibrationXML.pushTag("SCREEN:POINT", numDragTags-1);

			//we see how many points we have stored in <POINT> tags
			int numPtTags = calibrationXML.getNumTags("POINT");

			if(numPtTags > 0)
			{
				//We then read those x y values into our array
				for(int i = 0; i < numPtTags; i++)
				{
					//the last argument of getValue can be used to specify
					//which tag out of multiple tags you are refering to.
					int x = calibrationXML.getValue("POINT:X", 0.000000, i);
					int y = calibrationXML.getValue("POINT:Y", 0.000000, i);

					cameraPoints[i] = vector2df(x,y);
					printf("Calibration: %f, %f\n", cameraPoints[i].X, cameraPoints[i].Y);

					bscreenPoints = true;
					bcameraPoints = true;
				}
			}
			calibrationXML.popTag(); //Set XML root back to highest level
		}
	}
	//End calibrationXML Calibration Settings

	//Set the camera calibated box.
	calculateBox();
//	computeCameraToScreenMap();
}


/*****************************************************************************
 * Start of Calibration Methods
 *****************************************************************************/

//Bounding Box Size
void CalibrationUtils::setScreenBBox(rect2df &box)
{
	screenBB = box;
	initScreenPoints();
}

//Compute a map of camera to screen coordinates
void CalibrationUtils::computeCameraToScreenMap()
{
	cameraToScreenMap = new vector2df[_camWidth * _camHeight];

	int p = 0;
	for(int y = 0; y < _camHeight; y++)
	{
		for(int x = 0; x < _camWidth; x++)
		{
			//cast to float
			float transformedX = (float)x;
			float transformedY = (float)y;

			//convert camera to screen space for all possible camera positions
			cameraToScreenSpace(transformedX, transformedY);
			//save these into a map of transformed camera to screen space positions
			cameraToScreenMap[p] = vector2df(transformedX, transformedY);
			p++;
		}
	}
}

void CalibrationUtils::setGrid(int x, int y)
{
	GRID_Y = y;
	GRID_X = x;

	GRID_POINTS = ((GRID_X+1) * (GRID_Y+1));
    GRID_INDICES = (GRID_X * GRID_Y * 3 * 2);

	screenPoints = new vector2df[GRID_POINTS];
	cameraPoints = new vector2df[GRID_POINTS];
	triangles    = new int[GRID_INDICES];

	initTriangles();

	if(bscreenPoints && bcameraPoints)
	{
		initScreenPoints();
		initCameraPoints(_camWidth, _camHeight);
	}
}

void CalibrationUtils::setCamRes(int camWidth = 320, int camHeight = 240)
{
	_camWidth = camWidth;
	_camHeight = camHeight;
}

void CalibrationUtils::initTriangles()
{
	int t = 0;
	for(int j = 0; j < GRID_Y; j++)
	{
		for(int i = 0; i < GRID_X; i++)
		{
			triangles[t+0] = (i+0) + ((j+0) * (GRID_X+1));
			triangles[t+1] = (i+1) + ((j+0) * (GRID_X+1));
			triangles[t+2] = (i+0) + ((j+1) * (GRID_X+1));

			t += 3;

			triangles[t+0] = (i+1) + ((j+0) * (GRID_X+1));
			triangles[t+1] = (i+1) + ((j+1) * (GRID_X+1));
			triangles[t+2] = (i+0) + ((j+1) * (GRID_X+1));

			t += 3;
		}
	}
}

//Initialize Points
void CalibrationUtils::initScreenPoints()
{
	int p = 0;

	vector2df xd(screenBB.lowerRightCorner.X-screenBB.upperLeftCorner.X,0.0f);
	vector2df yd(0.0f, screenBB.lowerRightCorner.Y-screenBB.upperLeftCorner.Y);

	xd /= (float) GRID_X;
	yd /= (float) GRID_Y;

	for(int j = 0; j <= GRID_Y; j++)
	{
		for(int i = 0; i <= GRID_X; i++)
		{
			screenPoints[p] = screenBB.upperLeftCorner + xd*i + yd*j;
			//printf("(%d, %d) = (%f, %f)\n", i, j, screenPoints[p].X, screenPoints[p].Y);
			p++;
		}
	}
}

void CalibrationUtils::initCameraPoints(int camWidth, int camHeight)
{
	int p = 0;
	for(int j = 0; j <= GRID_Y; j++)
	{
		for(int i = 0; i <= GRID_X; i++)
		{
			cameraPoints[p] = vector2df((i * camWidth) / (float)GRID_X, (j * camHeight) / (float)GRID_Y);
			p++;
		}
	}
}

void CalibrationUtils::setScreenScale(float s)
{
	// legacy
	float offset = (1.0f - s) * 0.5f;
	screenBB = rect2df(vector2df(offset,offset),vector2df(1.0f-offset,1.0f-offset));
	initScreenPoints();
}

float CalibrationUtils::getScreenScale()
{
	// legacy, take the minimum scale value that fits inside the bounding box
	float minValL = MIN(screenBB.lowerRightCorner.X,screenBB.lowerRightCorner.Y);
	minValL = 1.0f - minValL;
	float minValU = MAX(screenBB.upperLeftCorner.X,screenBB.upperLeftCorner.Y);
	float minVal = MIN(minValL,minValU);
	return 1.0f - (2.0f * minVal);
}

void CalibrationUtils::cameraToScreenPosition(float &x, float &y)
{
	cameraToScreenSpace(x, y);

	//is this right to avoid boundingbox overflow? this overflow occurs due to new angle box
// 	if(y > _camHeight) y = _camHeight;
// 	if(y < 0) y = 0;
// 	if(x > _camWidth) x = _camWidth;
// 	if(x < 0) x = 0;
// 
// 	int pos = (int)y * (int)_camWidth + (int)x;
// 
// 	x = cameraToScreenMap[pos].X;
// 	y = cameraToScreenMap[pos].Y;
}

void CalibrationUtils::transformDimension(float &width, float &height)
{
	//Transform width/height
    float halfX = width * 0.5f;
    float halfY = height * 0.5f;

	//Take all blobs as if they're from the center of calibrated region
	float centerX = ((maxBoxX - minBoxX)/2) + minBoxX;
	float centerY = ((maxBoxY - minBoxY)/2) + minBoxY;

	//Calculate x/y position of upper left and lower right x/y positions
    float ulX = centerX - halfX;
    float ulY = centerY - halfY;
    float lrX = centerX + halfX;
    float lrY = centerY + halfY;

	//Transform these x/y positions to screen space
	cameraToScreenPosition(ulX, ulY);
	cameraToScreenPosition(lrX, lrY);

	//Calculate new height/width
	width = std::fabs(lrX - ulX);
	height = std::fabs(ulY - lrY);
}

void CalibrationUtils::calculateBox()
{
	//reset variables
	maxBoxX = 0;
	minBoxX = _camWidth;
	maxBoxY = 0;
	minBoxY = _camHeight;
	// Calculate the max/min points based on cameraPoints
	for(int i = 0; i < GRID_POINTS; i++)
	{
		if(cameraPoints[i].X > maxBoxX)			maxBoxX = cameraPoints[i].X;
		else if(cameraPoints[i].X < minBoxX)	minBoxX = cameraPoints[i].X;
		if(cameraPoints[i].Y > maxBoxY)			maxBoxY = cameraPoints[i].Y;
		else if(cameraPoints[i].Y < minBoxY)	minBoxY = cameraPoints[i].Y;
	}
}

// Transforms a camera space coordinate into a screen space coord
void CalibrationUtils::cameraToScreenSpace(float &x, float &y)
{
	vector2df pt(x, y);
	int t = findTriangleWithin(pt);
	if(t != -1)
	{
		vector2df A = cameraPoints[triangles[t+0]];
		vector2df B = cameraPoints[triangles[t+1]];
		vector2df C = cameraPoints[triangles[t+2]];
		float total_area = (A.X - B.X) * (A.Y - C.Y) - (A.Y - B.Y) * (A.X - C.X);

		// pt,B,C
		float area_A = (pt.X - B.X) * (pt.Y - C.Y) - (pt.Y - B.Y) * (pt.X - C.X);

		// A,pt,C
		float area_B = (A.X - pt.X) * (A.Y - C.Y) - (A.Y - pt.Y) * (A.X - C.X);

		float bary_A = area_A / total_area;
		float bary_B = area_B / total_area;
		float bary_C = 1.0f - bary_A - bary_B;	// bary_A + bary_B + bary_C = 1

		vector2df sA = screenPoints[triangles[t+0]];
		vector2df sB = screenPoints[triangles[t+1]];
		vector2df sC = screenPoints[triangles[t+2]];

		vector2df transformedPos;

		transformedPos = (sA*bary_A) + (sB*bary_B) + (sC*bary_C);

		x = transformedPos.X;
		y = transformedPos.Y;
		return;
	}
	x = 0;
	y = 0;
	// FIXME: what to do in the case that it's outside the mesh?
}

bool CalibrationUtils::isPointInTriangle(vector2df p, vector2df a, vector2df b, vector2df c)
{
	if (vector2df::isOnSameSide(p,a, b,c) && vector2df::isOnSameSide(p,b, a,c) && vector2df::isOnSameSide(p, c, a, b))
		return true;
    else
		return false;
}

int CalibrationUtils::findTriangleWithin(vector2df pt)
{
	for(int t = 0; t < GRID_INDICES; t += 3)
	{
		if(isPointInTriangle(pt, cameraPoints[triangles[t]], cameraPoints[triangles[t+1]], cameraPoints[triangles[t+2]]) )
			return t;
	}
	return -1;
}

void CalibrationUtils::beginCalibration()
{
	 bCalibrating = true;
	 calibrationStep = 0;
}

void CalibrationUtils::nextCalibrationStep()
{
	if(bCalibrating)
	{
		calibrationStep++;
		if(calibrationStep >= GRID_POINTS)
		{
			bCalibrating = false;
			calibrationStep = 0;
			saveCalibration();
			calculateBox();
// 			computeCameraToScreenMap();

            saveCalibration();
		}
	}
}

void CalibrationUtils::revertCalibrationStep()
{
	if(bCalibrating)
	{
		calibrationStep--;
		if(calibrationStep < 0)
		{
			calibrationStep = 0;
		}
	}
}

//Save Calibration Points to file
void CalibrationUtils::saveCalibration()
{
	// -------------------------------- SAVE STATE ON EXIT

	//lets see how many <STROKE> </STROKE> tags there are in the xml file
	int numDragTags = calibrationXML.getNumTags("SCREEN:POINT");

	//if there is at least one <POINT> tag we can read the list of points
	if(numDragTags > 0)
	{
		//we push into the last POINT tag this temporarirly treats the tag as the document root.
		calibrationXML.pushTag("SCREEN:POINT", numDragTags-1);

		calibrationXML.clear();

		//Save the Grid Mesh X/Y
		calibrationXML.setValue("GRIDMESH:GRIDX", GRID_X);
	    calibrationXML.setValue("GRIDMESH:GRIDY", GRID_Y);

		//Save the Bounding Box
		calibrationXML.setValue("BOUNDINGBOX:ulx", screenBB.upperLeftCorner.X);
		calibrationXML.setValue("BOUNDINGBOX:uly", screenBB.upperLeftCorner.Y);
		calibrationXML.setValue("BOUNDINGBOX:lrx", screenBB.lowerRightCorner.X);
		calibrationXML.setValue("BOUNDINGBOX:lry", screenBB.lowerRightCorner.Y);

		//Save all the Calibration Points
		if(GRID_POINTS > 0)
		{
			//We then read those x y values into our array
			for(int i = 0; i < GRID_POINTS; i++)
			{
				//the last argument of getValue can be used to specify
				//which tag out of multiple tags you are refering to.
				calibrationXML.setValue("POINT:X", cameraPoints[i].X, i);
				calibrationXML.setValue("POINT:Y", cameraPoints[i].Y, i);
			}
		}
		calibrationXML.popTag(); //Set XML root back to highest level
	}
	calibrationXML.saveFile("calibration.xml");
}
