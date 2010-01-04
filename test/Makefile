CXXFLAGS:=-Wall -Werror -lcppunit -I../src/ -I../src/base -I../src/menu -I../src/media -I../src/screens
LDFLAGS:=-lsqlite3 -lSDL

PROJECT:=usdx-tests
TARGET:=$(PROJECT)

zip:=$(PROJECT).rar
headers:=$(wildcard *.hpp) $(wildcard */*.hpp) $(wildcard ../src/*/*.hpp) $(wildcard ../src/*.hpp)
sources:=$(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard ../src/*/*.cpp) $(wildcard ../src/*.cpp)
objects:=$(sources:.cpp=.o)

all:	$(TARGET)

.PHONY:	all clean run zip

$(TARGET):	$(objects)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(objects)

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

clean:
	-$(RM) $(TARGET) $(objects)

run:	$(TARGET)
	./$(TARGET)

zip:
	-$(RM) $(zip)
	rar a -s -m5 -ap$(PROJECT) $(zip) $(headers) $(sources) Makefile
