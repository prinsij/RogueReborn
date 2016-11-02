
.PHONY: default clean recall link compile ready

default: link

ready:

	#Setting up...

	@#Bring over the libtcod reqs
	@cp ./libtcod/*.so .

	@#Copy to the srcstore
	@rm -rf .srcstore/
	@mkdir .srcstore
	@cp *.cpp .srcstore/

	@#Rename to src.*
	@bash .srcmv

	@#Bring over the tests
	@cp test/*.cpp .

compile: ready

	#Compiling...
	@g++ -g -c *.cpp -I./libtcod/include -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall -std=c++11

	@# Remove *.cpp and bring back the old ones (could also just rename src.*.cpp -> *.cpp)
	@rm -f *.cpp
	@cp .srcstore/*.cpp .

link: compile

	#Linking source...
	@g++ -g -o RogueReborn.exe src.*.o *.so -I./libtcod/include -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall -std=c++11

	@rm -f src.main.o

	#Linking tests...
	@g++ -g -o Test.exe *.o *.so -I./libtcod/include -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall -std=c++11

	#Removing objects
	@rm -f *.o

sane:
	@cp ./libtcod/*.so .
	@g++ *.cpp -o RogueRebon.exe -I./libtcod/include -L. -ltcod -ltcodxx -Wl,-rpath=. -Wall -std=c++11

recall:
	@bash .recall

clean:
	@rm -f *.exe *.so *.o scores.txt
