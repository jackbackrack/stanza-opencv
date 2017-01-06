LIBS += ${GEN}/opencv.o -lopencv_core -lopencv_highgui -lopencv_video  -lopencv_imgproc

stanza_opencv_all: ${GEN}/opencv.pkg

ALL_PKG_DEPS += stanza_opencv_all

${GEN}/opencv.o: stanza-gui/opencv.c
	cc $(CFLAGS) -c stanza-gui/opencv.c -o $@

${GEN}/opencv.pkg: stanza-gui/opencv.stanza ${GEN}/gl.pkg 
	stanza $< $(STZ_FLAGS)



