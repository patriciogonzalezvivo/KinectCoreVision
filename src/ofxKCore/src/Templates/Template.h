#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "ofMain.h"

class Template {
	
public:
	Template() 
	{
	}

	//The ID of the template
	int			id;
	int			trueId;

	//Rectangle Specifications
	float			height;
	float			width;
	float			minHeight;
	float			minWidth;
	float			maxHeight;
	float			maxWidth;

	bool matchWithTemplate(Template t);
};

#endif