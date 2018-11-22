
SRCDIR = src
OBJDIR = obj
INCDIR = include
LIBDIR = lib
BINDIR = bin

CC       = gcc
CXX      = g++
CXXFLAGS = -std=c++11 -Wall -I$(INCDIR)
LDLIBS   = -lglut -lGL -lGLU -lm -L$(LIBDIR) -lzgeom

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

TARGET = demo

export LIBDEST = "$(shell pwd)/$(LIBDIR)"
export INCLUDEDEST = "$(shell pwd)/$(INCDIR)"

all: libzgeom $(BINDIR)/$(TARGET)

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDLIBS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY:
libzgeom:
	$(MAKE) -C lib/zgeom

clean:
	rm -f $(OBJDIR)/*.o
	$(MAKE) clean -C lib/zgeom

pristine: clean
	rm -f $(BINDIR)/*.out
	rm -f $(BINDIR)/*.exe
	rm -f $(BINDIR)/$(TARGET)
	rm -rf $(OBJDIR)
	rm -f lib/libzgeom.a
	rm -rf include/zgeom*
	$(MAKE) pristine -C lib/zgeom

