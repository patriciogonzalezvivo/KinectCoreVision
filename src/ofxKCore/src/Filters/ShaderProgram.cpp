/*
*  ShaderProgram.h
*  
*
*  Created on 2/2/09.
*  Copyright 2009 NUI Group. All rights reserved.
*
*/
#include "ShaderProgram.h"
#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable: 4996)  // unsafe fopen warning

//some helper functions...for reading textfile, compiling shader source and printing compile logs
//TODO:  either integrate them into the class or put them somewhere else
char* textFileRead(const char *fn) {
    FILE *fp;
    char *content = 0;
    
    int count=0;
    
    if (fn != 0) {
    	fp = fopen(fn,"rt");
        if (fp != 0) {
        	fseek(fp, 0, SEEK_END);
            count = ftell(fp);
            rewind(fp);
            if (count > 0) {
            	content = (char *)malloc(sizeof(char) * (count+1));
                count = fread(content,sizeof(char),count,fp);
                content[count] = '\0';
            }
            fclose(fp);
    	}
    	else{
        	printf("error reading shader input file %s", fn);
        	exit(1);
    	}
	}
    return content;
}


void printShaderInfoLog(GLuint obj)
{
    GLint infologLength = 0;
    GLint charsWritten  = 0;
    char *infoLog;
        
    glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);    
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
                printf("%s\n",infoLog);
        free(infoLog);
    }
}


void printProgramInfoLog(GLuint obj)
{
    GLint infologLength = 0;
    GLint charsWritten  = 0;
    char *infoLog;
        
    glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);    
    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
                printf("%s\n",infoLog);
        free(infoLog);
    }
}


GLuint loadShader( const char* sourceFile, GLenum shaderType){
    char * shader_source;
    GLuint shader_id;
    
    shader_id = glCreateShader(shaderType);
    
    shader_source = textFileRead(sourceFile);
    const char * ss  = shader_source;
    glShaderSource(shader_id, 1, &ss,0);
    glCompileShader(shader_id);
    free(shader_source);
    printShaderInfoLog(shader_id);
    
    return shader_id;
    
}

//ShaderProgram class implementation
ShaderProgram::ShaderProgram(const char* vertexSourceFile, const char* geometrySourceFile, const char* fragmentSourceFile){

    this->program  = glCreateProgram();
    
    printf("loading Shaders vs:%s, gs:%s, fs:%s\n", vertexSourceFile, geometrySourceFile, fragmentSourceFile);
    
    //compile and attach vertex shader
    if (vertexSourceFile != 0){
        this->vertex_shader_id = loadShader(vertexSourceFile, GL_VERTEX_SHADER);
        glAttachShader(this->program ,this->vertex_shader_id);
    }    
    
    //compile and attach geometry shader (sets default input/output type to GL_POINTS)
    if (geometrySourceFile != 0){
        this->geometry_shader_id= loadShader(geometrySourceFile, GL_GEOMETRY_SHADER_EXT);
        glAttachShader(program ,this->geometry_shader_id);
        
        GLint temp;
        glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT,&temp);
        glProgramParameteriEXT(this->program,GL_GEOMETRY_VERTICES_OUT_EXT,temp);
        glProgramParameteriEXT(this->program,GL_GEOMETRY_INPUT_TYPE_EXT,GL_POINTS);
        glProgramParameteriEXT(this->program,GL_GEOMETRY_OUTPUT_TYPE_EXT,GL_POINTS);
    } 
    
    //compile and attach fragment shader
    if (fragmentSourceFile != 0)
	{
        fragment_shader_id = loadShader(fragmentSourceFile, GL_FRAGMENT_SHADER);
        glAttachShader(this->program ,fragment_shader_id);
        
    } 
    glLinkProgram(program);
    printProgramInfoLog(program);
}

ShaderProgram::~ShaderProgram()
{
	//TODO: free resources
}
