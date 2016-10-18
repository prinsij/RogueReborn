
#include "include/terrain.h"
#include "include/tiles.h"
#include "include/level.h"
#include "include/coord.h"
#include <vector>
#include <queue>
#include <map>
#include <math.h>

Algs::Algs(){}

void Algs::addPerps(Coord current, &std::vector<Coord> deltas, Level& lvl, std::map<Coord, Coord>& parents){
	
	Coord target;

	target = current + Coord(1, 0);
	tryAdd(current, delta, lvl, parents, target);

	target = current + Coord(-1, 0);
	tryAdd(current, delta, lvl, parents, target);

	target = current + Coord(0, 1);
	tryAdd(current, delta, lvl, parents, target);

	target = current + Coord(0, -1);
	tryAdd(current, delta, lvl, parents, target);
}

void Algs::addDiags(Coord current, std::vector<Coord>& deltas, Level& lvl, std::map<Coord, Coord>& parents){
	
	Coord target;

	target = current + Coord(1, 1);
	tryAdd(current, delta, lvl, parents, target);

	target = current + Coord(-1, 1);
	tryAdd(current, delta, lvl, parents, target);

	target = current + Coord(-1, -1);
	tryAdd(current, delta, lvl, parents, target);

	target = current + Coord(1, -1);
	tryAdd(current, delta, lvl, parents, target);
}

void Algs::tryAdd(Coord current, std::vector<Coord>& deltas, Level& lvl, std::map<Coord, Coord>& parents, Coord target){

	if(lvl[target].isPassable() == Terrain::Passable && !lvl[target].checked){
		delta.push_back(target);
		lvl[target].checked = true;
		parents[target, current];
	}
}

std::vector<Coord> Algs::bfsDiag(Coord start, Coord end, Level& lvl){

	std::map<Coord, Coord> parents;
	std::queue<Coord> delta;
	delta.push(start.copy());

	while(!delta.empty()){

		Coord current = delta.front();
		delta.pop();

		if (current == end){
			break;
		}

		addPerps(current, delta, lvl, parents);
		addDiags(current, delta, lvl, parents);

	}
}

std::vector<Coord> Algs::bfsPerp(Coord start, Coord end){

}

std::vector<Coord> Algs::getPath(std::vector<Coord> delta, Coord start){

}