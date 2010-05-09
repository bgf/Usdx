PROJECT:=usdx
TOP:=.

headers:=$(wildcard $(TOP)/src/*/*/*.hpp) $(wildcard $(TOP)/src/*/*.hpp) $(wildcard $(TOP)/src/*.hpp)

sources:=$(wildcard $(TOP)/src/*/*/*.cpp) $(wildcard $(TOP)/src/*/*.cpp) $(wildcard $(TOP)/src/*.cpp)

deps:=$(sources:.cpp=.d)

CXXFLAGS:=-Wall -Werror -I$(TOP)/src -I$(TOP)/src/base -I$(TOP)/src/menu -I$(TOP)/src/media -I$(TOP)/src/screens -I$(TOP)/src/frames -g
LDFLAGS:=-lsqlite3 -lSDL -llog4cxx -lboost_program_options-mt -lboost_filesystem-mt -lboost_thread-mt -lSDL_image -lSDL_gfx -lcppunit -lGL
TARGET:=$(PROJECT)

objects:=$(sources:.cpp=.o)

##############################################################################

.PHONY:	all clean run

all:	$(TARGET)

clean:
	-$(RM) -r $(TARGET) $(TARGET-COVERAGE) $(objects) $(deps) $(coverage)

run:	$(TARGET)
	./$(TARGET)

ifneq ($(MAKECMDGOALS),clean)
-include $(deps)
endif

##############################################################################
# normal build

$(TARGET):	$(objects) $(deps)
	$(CXX) $(LDFLAGS) -o $(TARGET) $(objects)

%.o:		%.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

%.d:		%.cpp
	$(CXX) $(CXXFLAGS) -MM -c $< -MF $@
