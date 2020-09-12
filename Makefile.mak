CPP    = g++
WINDRES= windres
RM     = rm -f
OBJS   = classes/display.o \
         classes/glwindow.o \
         obj_viewer/main.o \
         obj_viewer/texture.o \
         obj_viewer/texturemanager.o \
         obj_viewer/objloader.o \
         obj_viewer/vertex.o \
         obj_viewer/object.o \
         obj_viewer/model.o \
         obj_viewer/scenemanager.o \
         obj_viewer/util.o \
         obj_viewer/tiny_obj_loader.o \
         obj_viewer/choosedlg.o \
         obj_viewer/camera.o \
         obj_viewer/player.o \
         AppResource.res

LIBS   = -mwindows -static -lmingw32 -lSOIL -lSDLmain -lSDL -lOpenGL32 -lglu32 -lwinmm -ldxguid
CFLAGS = -I..\OpenGL

.PHONY: ObjectViewer.exe clean

all: ObjectViewer.exe

clean:
	$(RM) $(OBJS) ObjectViewer.exe

ObjectViewer.exe: $(OBJS)
	$(CPP) -Wall -s -O2 -o $@ $(OBJS) $(LIBS)

classes/display.o: classes/display.cpp classes/display.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

classes/glwindow.o: classes/glwindow.cpp classes/glwindow.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

obj_viewer/main.o: obj_viewer/main.cpp obj_viewer/choosedlg.h classes/glwindow.h obj_viewer/util.h obj_viewer/texturemanager.h obj_viewer/scenemanager.h obj_viewer/model.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

obj_viewer/texture.o: obj_viewer/texture.cpp obj_viewer/texture.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

obj_viewer/texturemanager.o: obj_viewer/texturemanager.cpp obj_viewer/texturemanager.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

obj_viewer/objloader.o: obj_viewer/objloader.cpp obj_viewer/objloader.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

obj_viewer/vertex.o: obj_viewer/vertex.cpp obj_viewer/vertex.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

obj_viewer/object.o: obj_viewer/object.cpp obj_viewer/object.h obj_viewer/util.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

obj_viewer/model.o: obj_viewer/model.cpp obj_viewer/model.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

obj_viewer/scenemanager.o: obj_viewer/scenemanager.cpp obj_viewer/scenemanager.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

obj_viewer/util.o: obj_viewer/util.cpp obj_viewer/util.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

obj_viewer/tiny_obj_loader.o: obj_viewer/tiny_obj_loader.cc obj_viewer/tiny_obj_loader.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

obj_viewer/choosedlg.o: obj_viewer/choosedlg.cpp obj_viewer/choosedlg.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

obj_viewer/camera.o: obj_viewer/camera.cpp obj_viewer/camera.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

obj_viewer/player.o: obj_viewer/player.cpp obj_viewer/player.h
	$(CPP) -Wall -s -O2 -c $< -o $@ $(CFLAGS)

AppResource.res: AppResource.rc
	$(WINDRES) -i AppResource.rc -J rc -o AppResource.res -O coff

