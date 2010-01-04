CXXFLAGS:=-Wall -Werror -lcppunit -I../src/ -I../src/base -I../src/menu -I../src/media -I../src/screens
LDFLAGS:=-lsqlite3 -lSDL

PROJECT:=usdx-tests
TARGET:=$(PROJECT)

zip:=$(PROJECT).rar
headers:=$(wildcard *.hpp) $(wildcard */*.hpp) $(wildcard ../src/*/*.hpp) $(wildcard ../src/*.hpp)
sources:=$(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard ../src/*/*.cpp) $(wildcard ../src/*.cpp)
objects:=$(sources:.cpp=.o)
deps:=$(sources:.cpp=.d)

all:	$(deps) $(TARGET)

ifneq ($(MAKECMDGOALS),clean)
-include $(deps)
endif

.PHONY:	all clean run zip

$(TARGET):	$(objects) $(deps)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(objects)

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

%.d:	%.cpp
	$(CXX) $(CXXFLAGS) -MMD -E -c $< -o $(@:.d=.tmp)
	rm $(@:.d=.tmp)

clean:
	-$(RM) $(TARGET) $(objects) $(deps)

run:	$(TARGET)
	./$(TARGET)

zip:
	-$(RM) $(zip)
	rar a -s -m5 -ap$(PROJECT) $(zip) $(headers) $(sources) Makefile
