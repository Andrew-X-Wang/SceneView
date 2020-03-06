#Makefile for assignment 2
CXX           = $(shell fltk-config --cxx)
CXXFLAGS      = $(shell fltk-config --cxxflags)
LINKFLTK_FLGS = $(shell fltk-config --ldflags --use-gl --use-images)
POSTBUILD     = fltk-config --post #build .app for osx. (does nothing on pc)

all: a2

%.o: %.cpp
	$(CXX) -c $< $(CXXFLAGS)

a2:  main.o MyGLCanvas.o Camera.o 
	$(CXX) -o $@ main.o MyGLCanvas.o Camera.o $(LINKFLTK_FLGS) && $(POSTBUILD) $@ && if test -d $@.app; then sed -i '' -e 's|<true/>|<false/>|' "$@.app/Contents/Info.plist"; fi

clean:
	@rm -rf a2.app a2 *.o *~

