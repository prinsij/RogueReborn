

#include "include/terrain.h"
#include "include/mob.h"
#include <vector>
#include <queue>
#include <map>
#include <math.h>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "include/tiles.h"
#include "include/level.h"
#include "include/coord.h"
#include "include/room.h"
#include "include/random.h"
#include "include/playerchar.h"
#include "include/tunnel.h"

Level::Level(int depth) 
	: size(getSize())
	, depth(depth) 
{
	for (auto x=0; x < size[0]; x++) {
		tiles.push_back(std::vector<Terrain>());
		for (auto y=0; y < size[1]; y++) {
			tiles[x].push_back(Wall());
		}
	}
}

Terrain& Level::operator[](Coord coord) {
	return tileAt(coord);
}

Terrain& Level::tileAt(Coord coord) {
	return tiles[coord[0]][coord[1]];
}

bool Level::contains(Coord pos) {
	return pos[0] >= 0 && pos[1] >= 0 && pos[0] < size[0] && pos[1] < size[1]; 
}

int Level::genGoldAmount(Generator gen) {
	return 2 + gen.intFromRange(0, 50 + 10 * depth);
}

void Level::registerMob(Mob* mob) {
	mobs.push_back(ClockItem(mob, 0));
}

Mob* Level::popTurnClock() {
	if (mobs.empty()) {
		return NULL;
	}
	auto difference = mobs.back().delay;
	if (difference > 0) {
		for (auto &item : mobs) {
			 item.delay -= difference;
		}
	}
	return mobs.back().mob;
}

void Level::pushMob(Mob* which, int delay) {
	auto newTime = delay;
	for (auto it=mobs.begin(); it != mobs.end(); ++it) {
		auto& item = *it;
		if (item.mob == which) {
			mobs.erase(it);
			newTime += item.delay;
			break;
		}
	}
	if (mobs.empty()) {
		mobs.push_back(ClockItem(which, newTime));
		return;
	}
	for (auto it=mobs.begin(); it != mobs.end(); ++it) {
		auto& item = *it;
		if (item.delay <= newTime) {
			mobs.insert(it, ClockItem(which, newTime));
			return;
		}
	}
}

std::vector<Mob*> Level::getMobs() {
	std::vector<Mob*> result;
	for (auto &item : mobs) {
		result.push_back(item.mob);
	}
	return result;
}

void Level::generate(PlayerChar player) {

	Generator gen = Generator();
	Coord maxRoomSize = Coord(size[0]/3, size[1]/3);
	for (auto i=0; i < MAX_ROOMS; i++) {

			//Define upper left corner 
		Coord totalTopLeft = Coord((i%3)*maxRoomSize[0], i/3*maxRoomSize[1]);

		Coord padding = Coord(ROOM_PADDING, ROOM_PADDING);

		//These two are INCLUSIVE legal constraints (<= and >=)
		Coord legalTopLeft = totalTopLeft + padding;
		Coord legalBottomRight = totalTopLeft + maxRoomSize - padding - Coord(1,1);

		Coord roomSize = Coord( gen.intFromRange(MIN_ROOM_DIM, legalBottomRight[0] - legalTopLeft[0] + 1),
								gen.intFromRange(MIN_ROOM_DIM, legalBottomRight[1] - legalTopLeft[1] + 1));

		bool dne = false;

		//If room DNE, set its size to 1x1
		if (gen() > ROOM_EXIST_CHANCE){
			roomSize = Coord(1,1);
			dne = true;
		}

		Coord roomPosition = Coord( gen.intFromRange(legalTopLeft[0], legalBottomRight[0] - roomSize[0] + 1),
							  gen.intFromRange(legalTopLeft[1], legalBottomRight[1] - roomSize[1] + 1));

		//Really not sure what the purpose of this line is. Why is this being decided randomly?
		Room::Darkness isDark = gen.intFromRange(0, 10) < depth - 1 ? Room::DARK : Room::LIT;


		Room curRoom = Room(roomPosition, roomPosition + roomSize - Coord(1,1), isDark, Room::WORTHLESS, Room::VISIBLE, Coord(i%3, i/3), !dne);

		curRoom.dig(*this);

		//put gold in current room
		if (!dne && gen() < GOLD_CHANCE && (!player.hasAmulet() || depth >= player.maxDelved())) {
			Coord goldPos = gen.randPosition(curRoom[0], curRoom[1]);
			int goldAmount = genGoldAmount(gen);
			golds.push_back(GoldPile(goldPos, goldAmount));
		}

		//put monsters in current room
		rooms.push_back(curRoom);
	}

	//Used to say: If A -> B, then B -> A
	bool symmetric [MAX_ROOMS][MAX_ROOMS];//Take care of non-existent rooms

	for (auto i=0; i < MAX_ROOMS; i++){

		int j;

		//Down
		j = i + 3;
		if (j <= 8){
			addTunnel(i, j, &symmetric[i][j], &symmetric[j][i], gen);
		}

		//Up
		j = i - 3;
		if (j >= 0){
			addTunnel(i, j, &symmetric[i][j], &symmetric[j][i], gen);
		}

		//Left
		j = i - 1;
		if (j >= 0 && i / 3 == j / 3){
			addTunnel(i, j, &symmetric[i][j], &symmetric[j][i], gen);
		}

		//Right
		j = i + 1;
		if (j >= 0 && i / 3 == j / 3){
			addTunnel(i, j, &symmetric[i][j], &symmetric[j][i], gen);
		}
	}

	std::cout << "I'm made " << tunnels.size() << " tunnels" << std::endl;

	for (Tunnel t : tunnels){
		t.dig(*this);
	}
}

void Level::addTunnel(int i, int j, bool* a, bool* b, Generator gen){
	if (!(*a)){
		*a = true;
		*b = true;
		tunnels.push_back(Tunnel(&rooms[i], &rooms[j], gen));
	}
}

void Level::addPerps(Coord current, std::queue<Coord>& deltas, std::map<Coord, Coord>& parents){
	
	Coord target;

	target = current + Coord(1, 0);
	tryAdd(current, deltas, parents, target);

	target = current + Coord(-1, 0);
	tryAdd(current, deltas, parents, target);

	target = current + Coord(0, 1);
	tryAdd(current, deltas, parents, target);

	target = current + Coord(0, -1);
	tryAdd(current, deltas, parents, target);
}

void Level::addDiags(Coord current, std::queue<Coord>& deltas, std::map<Coord, Coord>& parents){
	
	Coord target;

	target = current + Coord(1, 1);
	tryAdd(current, deltas, parents, target);

	target = current + Coord(-1, 1);
	tryAdd(current, deltas, parents, target);

	target = current + Coord(-1, -1);
	tryAdd(current, deltas, parents, target);

	target = current + Coord(1, -1);
	tryAdd(current, deltas, parents, target);
}

void Level::tryAddPassable(Coord current, std::queue<Coord>& deltas, std::map<Coord, Coord>& parents, Coord target){

	if (target[0] > 0 && target[0] < size[0] && target[1] > 0 && target[1] < size[1]){

		if(tiles[target[0]][target[1]].isPassable() == Terrain::Passable && !tiles[target[0]][target[1]].checked){
			deltas.push(target.copy());
			tiles[target[0]][target[1]].checked = true;
			Coord t_ = target.copy();
			Coord c_ = current.copy();

			parents.insert(std::make_pair(t_, c_));
		}
	}
}

void Level::tryAdd(Coord current, std::queue<Coord>& deltas, std::map<Coord, Coord>& parents, Coord target){

	if (target[0] > 0 && target[0] < size[0] && target[1] > 0 && target[1] < size[1]){

		if(!tiles[target[0]][target[1]].checked){

			Coord t_ = target.copy();
			Coord c_ = current.copy();
			Coord p_ = target.copy();

			deltas.push(p_);

			tiles[target[0]][target[1]].checked = true;

			parents.insert(std::make_pair(t_, c_));
		}
	}
}

std::vector<Coord> Level::bfsDiag(Coord start, Coord end){

	for (auto x=0; x < size[0]; x++) {
		for (auto y=0; y < size[1]; y++) {
			tiles[x][y].checked = false;
		}
	}

	std::map<Coord, Coord> parents;
	std::queue<Coord> delta;
	delta.push(start.copy());

	while(!delta.empty()){

		Coord current = delta.front();
		delta.pop();

		if (current == end){
			break;
		}

		addPerps(current, delta, parents);
		addDiags(current, delta, parents);
	}

	//TODO: Put this into its own function
	std::vector<Coord> path;
	Coord current = end.copy();
	while(current != start){

		path.push_back(current);
		current = parents[current].copy();
	}
	path.push_back(start.copy());

	return path;
}

std::vector<Coord> Level::bfsPerp(Coord start, Coord end){

	for (auto x=0; x < size[0]; x++) {
		for (auto y=0; y < size[1]; y++) {
			tiles[x][y].checked = false;
		}
	}

	std::map<Coord, Coord> parents;
	std::queue<Coord> delta;
	delta.push(start.copy());

	while(!delta.empty()){

		Coord current = delta.front();
		delta.pop();

		if (current == end){
			break;
		}
	
		Coord target;

		target = current + Coord(1, 0);
		tryAdd(current, delta, parents, target);

		target = current + Coord(-1, 0);
		tryAdd(current, delta, parents, target);

		target = current + Coord(0, 1);
		tryAdd(current, delta, parents, target);

		target = current + Coord(0, -1);
		tryAdd(current, delta, parents, target);
	}

	//TODO: Put this into its own function
	std::vector<Coord> path;
	Coord current = end.copy();
	
	/*

	std::cout << "Parents:" << std::endl;
	std::map<Coord, Coord>::iterator it = parents.begin();
	while(it != parents.end())
    {
        std::cout << (it->first.toString()) << " ---> " << (it->second.toString()) << "    (" << ((it->second)-(it->first)).toString() << ")" << std::endl;
        it++;
    }

	std::cout << "Going from: " << start[0] << ", " << start[1] << std::endl;
	std::cout << "Going to: " << end[0] << ", " << end[1] << std::endl;

    */

	int count = 0;


	//std::cout << current[0] << ", " << current[1] << std::endl;
	while(current != start){

		Coord c_ = current.copy();

		path.push_back(c_);
		current = parents[current].copy();

		//std::cout << current[0] << ", " << current[1] << std::endl;

		count++;

		if (count == 100 || current == Coord(0,0)){
			std::cout << "Oops" << std::endl;
			break;
		}
	}

	path.push_back(start.copy());

	return path;

}

std::vector<Coord> Level::getDeltas(std::vector<Coord> path, Coord start){

	std::vector<Coord> deltas;
	std::reverse(path.begin(), path.end());

	if (start != path[0]){
		std::cout << "Start != path[0]" << std::endl;
	}

	for (int i = 0; i < path.size()-1; i++){
		Coord delta = path[i+1]-path[i];
		deltas.push_back(delta);
	}	

	return deltas;
}