#ifndef _TEXTURELOADING_FOR_SHADERS_2013__
#define _TEXTURELOADING_FOR_SHADERS_2013__
#include <stdio.h>
#include <math.h>
#ifdef WIN32
#include <windows.h>
#include <gl/glew.h>
#include <gl/gl.h>
#include <gl/glut.h>
#else // MAC OS X
#include <OpenGL/OpenGL.h> 
#include <GLUT/GLUT.h> 
#endif

GLuint setTexture(char *filename);
void setTwoTextures(char *filename1, char *filename2, GLuint *tex1, GLuint *tex2);

#endif