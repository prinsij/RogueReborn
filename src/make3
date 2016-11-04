CXX = g++
CXXFLAGS = -O1 -g -I./libtcod/include -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall -std=c++11
LDFLAGS = 
TARGET = RogueReborn.exe
TESTTARGET = Test.exe

SRCS=amulet.cpp armor.cpp coord.cpp feature.cpp food.cpp goldpile.cpp helpscreen.cpp invscreen.cpp item.cpp itemzone.cpp level.cpp main.cpp mainmenu.cpp mastercontroller.cpp mob.cpp monster.cpp playerchar.cpp playstate.cpp potion.cpp random.cpp ring.cpp ripscreen.cpp room.cpp scroll.cpp stairs.cpp terrain.cpp tiles.cpp trap.cpp tunnel.cpp uistate.cpp wand.cpp weapon.cpp

TESTSRCS=test/test.armor.cpp test/test.main.cpp test/test.testable.cpp

OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.depends)

TESTOBJS = $(TESTSRCS:.cpp=.o)
TESTDEPS = $(TESTSRCS:.cpp=.depends)

.PHONY: clean all

all: $(TARGET) $(TESTTARGET)

$(TARGET): $(OBJS)
	@cp -n ./libtcod/*.so .
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) *.so -o $(TARGET)

$(TESTTARGET): $(TESTOBJS)
	@cp -n ./libtcod/*.so .
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(TESTOBJS) *.so -o $(TESTTARGET)

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.depends: %.cpp
	$(CXX) -M $(CXXFLAGS) $< > $@

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET) $(TESTOBJS) $(TESTDEPS) $(TESTTARGET)

-include $(DEPS) $(TESTDEPS)
