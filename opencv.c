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

static void cv_grab_frame (IplImage *image) {
  GLint view_port[4];
  GLint last_buffer;
  glGetIntegerv(GL_VIEWPORT, view_port);
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glPixelStorei(GL_PACK_ROW_LENGTH, 0);
  glPixelStorei(GL_PACK_SKIP_ROWS, 0);
  glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
  glGetIntegerv(GL_READ_BUFFER, &last_buffer);
  glReadBuffer(GL_FRONT);
  glReadPixels
    (0, 0, view_port[2], view_port[3], 
     GL_BGR_EXT, GL_UNSIGNED_BYTE, image->imageData);
  glReadBuffer(last_buffer);
  cvFlip(image, image, 0);
}

#include <time.h>

IplImage *pic_image;

void cv_dump_viewport (void) {
  if (!pic_image) {
    GLint view_port[4];
    glGetIntegerv(GL_VIEWPORT, view_port);
    CvSize sz = cvSize(view_port[2], view_port[3]);
    pic_image = cvCreateImage( sz, 8, 3 );
  }
  cv_grab_frame(pic_image);
  char filename[256];
  time_t rawtime;
  struct tm * timeinfo;
  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  strftime(filename,sizeof(filename),"./dump/%Y-%m-%d-%H-%M-%S-pic.jpg", timeinfo);
  int res = cvSaveImage(filename, pic_image, 0);
}

/*
CvVideoWriter* dumper  = 0;
int fourcc = -1;
IplImage *dump_image;
// int fourcc = CV_FOURCC('A', 'V', 'C', '1'); // h.264
// int fourcc = CV_FOURCC('D','I','V','X'); // mp4
// int fourcc = CV_FOURCC('H','F','Y','U');

void cv_write_avi_out (void) {
  if (num_frames % speed == 0) {
    grab_frame(dump_image);
    if (is_dumping_avi) {
      post("WRITING FRAME %d\n", num_dumped_frames);
      cvWriteToAVI(dumper, dump_image);
    } else if (is_dumping_jpgs) {
      char filename[256];
      sprintf(filename, "%s%04d.jpg", dump_filename, num_dumped_frames);
      int res = cvSaveImage(filename, dump_image, 0);
    }
    num_dumped_frames += 1;
  }
  num_frames += 1;
  if (num_frames > 0 && (num_frames % (int)(num_data(target_fps)*speed)) == 0) {
    int secs = num_frames / (num_data(target_fps)*speed);
    post("T=%02d:%02d\n", secs / 60, secs % 60);
  }
}
*/
