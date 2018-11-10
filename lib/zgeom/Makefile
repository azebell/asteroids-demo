
CC       = gcc
CXX      = g++
CFLAGS   = -Wall
CXXFLAGS = -std=c++11 -Wall
LDLIBS   = -lglut -lGL -lGLU -lm
INCLUDE  = -I./

SRCDIR  = src
OBJDIR  = obj
INCDIR  = include
LIBDIR  = lib
BINDIR  = $(LIBDIR)
TESTDIR = tests

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

TESTS    := $(wildcard $(TESTDIR)/*.test.cpp)
TESTOBJS := $(TESTS:$(TESTDIR)/%.cpp=$(OBJDIR)/%.o)

TARGET = $(BINDIR)/libzgeom.a
HEADERS  := $(INCLUDES:$(SRCDIR)/%.h=$(INCDIR)/zgeom/%.h)


all: $(OBJECTS) $(TARGET) $(HEADERS)
ifeq ($(LIBDEST),)
else
	cp -r $(LIBDIR)/* $(LIBDEST)
endif
ifeq ($(INCLUDEDEST),)
else
	cp -r $(INCDIR)/* $(INCLUDEDEST)
endif

build: $(OBJECTS)

docs: $(HEADERS)

tests: build docs $(TESTDIR)/catch.hpp unittests

$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	ar -rc $@ $^
	ranlib $@

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(HEADERS): $(INCDIR)/zgeom/%.h : $(SRCDIR)/%.h
	@mkdir -p $(INCDIR)/zgeom
	@echo "Auto-Documenting $<..."
	@echo "/////////////////////////////////////////////////" > $@
	@echo "// FILENAME: $(notdir $<)" >> $@
	@echo "//" >> $@
	@echo "// DESCRIPTION:" >> $@
	@sed -n -r "s/^\/\/\/ (.*)$$/\/\/\t\1/p" $< >> $@
	@echo "//" >> $@
	@echo "// FUNCTIONS:" >> $@
	@sed -n -r "s/^([a-zA-Z0-9]+.*;)$$/\/\/\t\1/p" $< >> $@
	@echo "//" >> $@
	@echo "/////////////////////////////////////////////////" >> $@
	@sed -e "/^\/\/\/.*$$/d" $< >> $@

unittests: $(OBJECTS) $(TESTOBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

$(TESTOBJS): $(OBJDIR)/%.o : $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I./$(TESTDIR) -I./$(INCDIR)

$(TESTDIR)/catch.hpp:
	wget -q -O $@ https://github.com/catchorg/Catch2/releases/download/v2.4.1/catch.hpp

clean:
	rm -f $(OBJDIR)/*.o

pristine: clean
	rm -rf $(OBJDIR)
	rm -f $(BINDIR)/*.out
	rm -f $(BINDIR)/*.exe
	rm -f *.exe
	rm -f $(BINDIR)/$(TARGET)
	rm -rf $(BINDIR)
	rm -f $(TESTDIR)/*.o
	rm -f $(TESTDIR)/catch.hpp
	rm -rf $(INCDIR)/zgeom

