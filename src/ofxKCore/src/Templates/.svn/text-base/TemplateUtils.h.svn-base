#ifndef TEMPLATEUTILS_H
#define TEMPLATEUTILS_H

#include "Template.h"
#include "ofMain.h"
#include "ofxXmlSettings.h"

#define MAX_NUM_TEMPLATES 20

class TemplateUtils	{

public:

	TemplateUtils()
	{
		idCounter	= 180;
		isLoaded	= false;
	}

	~TemplateUtils()
	{
	}

	int getId()
	{
		bool hasId=false;
		int i;

		for(i=0;i<assignedIds.size();i++)
		{
			if(idCounter==assignedIds[i])
			{
				idCounter++;
				i=0;
				continue;
			}
		}
		if(idCounter<200)
		{
			assignedIds.push_back(idCounter);
			return idCounter;
		}
		else
		{
			return -1;
		}
	}

	//Functions 
	bool loadTemplateXml();
	void saveTemplateXml();
	void addTemplate(ofRectangle rect,ofRectangle minRect, ofRectangle maxRect,float scaleX ,float scaleY);
	int getTemplateId(float width,float height);

	//Variables
	bool	isLoaded;
	int		idCounter;

	std::vector<Template>		templates;
	ofxXmlSettings				XML;
	vector<int>					assignedIds;

};

#endif