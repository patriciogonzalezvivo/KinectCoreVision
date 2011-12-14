#include "TemplateUtils.h"

//Adds template data to the vector
void TemplateUtils::addTemplate(ofRectangle rect,ofRectangle minRect, ofRectangle maxRect,float scaleX=1.0f ,float scaleY=1.0f) 
{
	if(templates.size() < MAX_NUM_TEMPLATES)
	{
		Template temp = Template();
		temp.width = rect.width * scaleX;
		temp.height = rect.height * scaleY;
		temp.maxWidth = maxRect.width * scaleX;
		temp.maxHeight = maxRect.height * scaleY;
		temp.minWidth = minRect.width * scaleX;
		temp.minHeight = minRect.height * scaleY;
		temp.id = getId();
		temp.trueId = 0;
	
		templates.push_back(temp);
		//printf("Template added. Number of templates = %d\n",templates.size());
	}
}

//Loads the XML file from templates.xml file. This returns false if the file does not exist
bool TemplateUtils::loadTemplateXml()
{
	if( XML.loadFile("templates.xml") )
	{
		templates.clear();
		int numTags=XML.getNumTags("TEMPLATE");
		if( numTags > 0 )
		{
			int total = MIN(numTags,MAX_NUM_TEMPLATES);
			;
			for(int i=0; i < total; i++)
			{
				float width =(float) XML.getValue("TEMPLATE:WIDTH",0,i);
				float height =(float)XML.getValue("TEMPLATE:HEIGHT",0,i);
				float minWidth =(float)  XML.getValue("TEMPLATE:MINWIDTH",0,i);
				float minHeight = (float) XML.getValue("TEMPLATE:MINHEIGHT",0,i);
				float maxWidth = (float) XML.getValue("TEMPLATE:MAXWIDTH",0,i);
				float maxHeight =(float) XML.getValue("TEMPLATE:MAXHEIGHT",0,i);
				int	trueId = XML.getValue("TEMPLATE:TRUEID",0,i);
				int id;
				if(trueId)
				{
					id = XML.getValue("TEMPLATE:ID",0,i);
					assignedIds.push_back(id);
				}
				else
				{
					id = getId();
				}

				if(width !=0 && height != 0 && minWidth != 0 && minHeight != 0 && maxWidth != 0 && maxHeight != 0)
				{//Only then add a template

					Template temp = Template();
					temp.width = width;
					temp.height = height;
					temp.maxWidth = maxWidth;
					temp.maxHeight = maxHeight;
					temp.minWidth = minWidth;
					temp.minHeight = minHeight;
					temp.trueId = trueId;
					temp.id = id;

					templates.push_back(temp);
				}
			}
			isLoaded = true;// <- This is inside the if statement so that if the file exists but no xml data in it,this will still be false
		}
		return true;
	}
	else
	{
		printf("\nTemplates.xml could not be loaded. Make sure it is there in data folder\n");
		templates.clear();
		return false;
	}
}

//Saves into XML file from the template vector.
void TemplateUtils::saveTemplateXml()
{
	XML.clear();

	for(int i = 0 ; i < templates.size() ; i++ )
	{
		int tagNum=XML.addTag("TEMPLATE");

		XML.setValue("TEMPLATE:WIDTH",templates[i].width,tagNum);
		XML.setValue("TEMPLATE:HEIGHT",templates[i].height,tagNum);
		XML.setValue("TEMPLATE:MINWIDTH",templates[i].minWidth,tagNum);
		XML.setValue("TEMPLATE:MINHEIGHT",templates[i].minHeight,tagNum);
		XML.setValue("TEMPLATE:MAXWIDTH",templates[i].maxWidth,tagNum);
		XML.setValue("TEMPLATE:MAXHEIGHT",templates[i].maxHeight,tagNum);
		XML.setValue("TEMPLATE:TRUEID",templates[i].trueId,tagNum);
		XML.setValue("TEMPLATE:ID",templates[i].id,tagNum);
		
		XML.popTag();	
	}
	XML.saveFile("templates.xml");
	printf("Template is saved\n");
}


// Better funtion to be implemented
int TemplateUtils::getTemplateId(float width,float height)
{
	int id = -1;
	if(templates.size()==0)
	{
		return -1;
	}
	for(int i = 0 ; i < templates.size() ; i++ )
	{
		if(width < templates[i].maxWidth && width > templates[i].minWidth && height < templates[i].maxHeight && height > templates[i].minHeight)
		{
			return templates[i].id;
		}
	}
	return id;
}