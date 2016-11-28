CXX = g++
CXXFLAGS = -O1 -g -I./libtcod/include -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall -std=c++11
LDFLAGS = 
TARGET = RogueReborn.exe
TESTTARGET = Test.exe

SRCSNOMAIN=amulet.cpp armor.cpp coord.cpp feature.cpp food.cpp goldpile.cpp helpscreen.cpp invscreen.cpp item.cpp itemzone.cpp level.cpp mainmenu.cpp mastercontroller.cpp mob.cpp monster.cpp playerchar.cpp playstate.cpp potion.cpp random.cpp ring.cpp ripscreen.cpp room.cpp scroll.cpp stairs.cpp terrain.cpp tiles.cpp trap.cpp tunnel.cpp uistate.cpp wand.cpp weapon.cpp logscreen.cpp symbolscreen.cpp statusscreen.cpp saving.cpp savescreen.cpp
SRCS=$(SRCSNOMAIN) main.cpp
TESTSRCS=$(SRCSNOMAIN) $(wildcard test.*.cpp)

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.depends)

TESTOBJS = $(TESTSRCS:.cpp=.o)
TESTDEPS = $(TESTSRCS:.cpp=.depends)

.PHONY: clean all doxy

all: dodeps $(TARGET) $(TESTTARGET)

$(TARGET): $(OBJS) dodeps
	@cp -n ./libtcod/*.so .
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) *.so -o $(TARGET)

$(TESTTARGET): $(TESTOBJS) dodeps
	@cp -n ./libtcod/*.so .
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(TESTOBJS) *.so -o $(TESTTARGET)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.depends: %.cpp
	$(CXX) -M $(CXXFLAGS) $< > $@

doxy:
	doxygen Doxyfile

dodeps: $(DEPS) $(TESTDEPS)
	@echo "Dependency files generated"

clean: 
	rm -f $(OBJS) $(DEPS) $(TARGET) $(TESTOBJS) $(TESTDEPS) $(TESTTARGET) *.so
