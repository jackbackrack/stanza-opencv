#include <stdio.h>
#include "opencv/cv.h"
#include "opencv/highgui.h"


#ifdef MACOSX
#include <GLUT/glut.h> 
#else
#include <GL/glut.h> // Linux, Windows
#endif
#include <GLFW/glfw3.h>

int jglGenTexture (void) {
  unsigned int tex;
  glGenTextures(1, &tex);
  return tex;
}

int jglBindTexture (int kind, int tex) {
  glBindTexture(kind, tex);
  return 0;
}

int jglTexParameteri (int a, int b, int c) {
  glTexParameteri(a, b, c);
  return 0;
}

int jglTexImage2D (int target, int level, int internalFormat, int width, int height, int border, int format, int type, void* data) {
  glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);
  return 0;
}

int cv_get_size (IplImage* img, int* size) {
  CvSize sz = cvGetSize(img);
  size[0] = sz.width;
  size[1] = sz.height;
  return 0;
}

char* cv_image_dat (IplImage* img) {
  return img->imageData;
}

IplImage* cv_create_image (int* size, int depth, int columns) {
  IplImage* res = cvCreateImage(cvSize(size[0], size[1]), depth, columns);
  return res;
}

