PROJECT:=usdx-tests
TOP:=..

headers:=$(wildcard *.hpp) $(wildcard */*.hpp) $(wildcard $(TOP)/src/*/*/*.hpp) \
		$(wildcard $(TOP)/src/*/*.hpp) $(wildcard $(TOP)/src/*.hpp)

sources:=$(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard $(TOP)/src/*/*/*.cpp) \
		$(wildcard $(TOP)/src/*/*.cpp) $(wildcard $(TOP)/src/*.cpp)

deps:=$(sources:.cpp=.d)

CXXFLAGS:=-Wall -Werror -I$(TOP)/src -I$(TOP)/src/base -I$(TOP)/src/menu -I$(TOP)/src/media -I$(TOP)/src/screens -g
LDFLAGS:=-lsqlite3 -lSDL -llog4cxx -lboost_program_options-mt -lboost_filesystem-mt -lSDL_image -lcppunit -lGL
TARGET:=$(PROJECT)

objects:=$(sources:.cpp=.o)

CXXFLAGS-COVERAGE:=-fprofile-arcs -ftest-coverage
LDFLAGS-COVERAGE:=-coverage
TARGET-COVERAGE:=$(TARGET)-coverage
COVERAGE-DIR:=$(TOP)/coverage

objects-coverage:=$(patsubst %,$(COVERAGE-DIR)/obj/test/%,$(sources:.cpp=.o))
coverage:=$(COVERAGE-DIR)/coverage.info.tmp $(COVERAGE-DIR)/coverage.info \
		$(objects-coverage:.o=.gcda) $(objects-coverage:.o=.gcno) \
		$(COVERAGE-DIR)/obj/

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

##############################################################################
# build and execute tests with code coverage and build nice html pages 

test-with-coverage:			$(COVERAGE-DIR)/html/index.html
	@test ! -e .error

$(COVERAGE-DIR)/html/index.html:	$(COVERAGE-DIR)/coverage.info
	genhtml $(COVERAGE-DIR)/coverage.info -o $(COVERAGE-DIR)/html/ -p \
		"$(realpath ./$(TOP)/src)"

$(COVERAGE-DIR)/coverage.info:		$(COVERAGE-DIR)/coverage.info.tmp
	lcov --extract $(COVERAGE-DIR)/coverage.info.tmp \
		"$(realpath ./$(TOP))/src/*" \
		-o $(COVERAGE-DIR)/coverage.info

$(COVERAGE-DIR)/coverage.info.tmp:	$(TARGET-COVERAGE)
	-$(RM) .error
	lcov --directory $(TOP) --zerocounters
	./$(TARGET-COVERAGE) || touch .error
	lcov --directory $(TOP) --capture \
		--output-file $(COVERAGE-DIR)/coverage.info.tmp -b .

$(TARGET-COVERAGE):			$(objects-coverage) $(deps)
	$(CXX) $(LDFLAGS) $(LDFLAGS-COVERAGE) -o $(TARGET-COVERAGE) \
		$(objects-coverage)

$(COVERAGE-DIR)/obj/test/%.o:		%.cpp
	@[ -d $(dir $@) ] || mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CXXFLAGS-COVERAGE) -MMD -c $< -o $@

