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
#include "include/terrain.h"
#include "include/mob.h"
#include "include/feature.h"

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

std::vector<Feature*>& Level::getFeatures() {
	return features;
}

int Level::getDepth() {
	return depth;
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

std::vector<Room>& Level::getRooms() {
	return rooms;
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
		if (gen.rand() > ROOM_EXIST_CHANCE){
			roomSize = Coord(1,1);
			dne = true;
		}

		Coord roomPosition = Coord( gen.intFromRange(legalTopLeft[0], legalBottomRight[0] - roomSize[0] + 1),
							  gen.intFromRange(legalTopLeft[1], legalBottomRight[1] - roomSize[1] + 1));

		//Really not sure what the purpose of this line is. Why is this being decided randomly?
		Room::Darkness isDark = gen.intFromRange(0, 10) < depth - 1 ? Room::DARK : Room::LIT;


		Room curRoom = Room(roomPosition, roomPosition + roomSize - Coord(1,1), isDark, Room::WORTHLESS, Room::VISIBLE, Coord(i%3, i/3), !dne);

		curRoom.dig(*this);

		/*

		//put gold in current room
		if (!dne && gen() < GOLD_CHANCE && (!player.hasAmulet() || depth >= player.maxDelved())) {
			Coord goldPos = gen.randPosition(curRoom[0], curRoom[1]);
			int goldAmount = genGoldAmount(gen);
			golds.push_back(GoldPile(goldPos, goldAmount));
		}

		*/

		//put monsters in current room
		rooms.push_back(curRoom);
	}

	//Used to say: If A -> B, then B -> A
	bool symmetric [MAX_ROOMS_DEF][MAX_ROOMS_DEF] = {};//Take care of non-existent rooms

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

void Level::tryAddPassable(Coord current, std::queue<Coord>& q, Coord target){

	if (target[0] > 0 && target[0] < size[0] && target[1] > 0 && target[1] < size[1]){

		if(tiles[target[0]][target[1]].isPassable() == Terrain::Passable && !(tiles[target[0]][target[1]].checked)){

			Coord c_ = current.copy();
			Coord p_ = target.copy();

			q.push(p_);

			tiles[target[0]][target[1]].checked = true;
			tiles[target[0]][target[1]].parent = c_;
		}
	}
}

void Level::tryAdd(Coord current, std::queue<Coord>& q, Coord target){

	if (target[0] > 0 && target[0] < size[0] && target[1] > 0 && target[1] < size[1]){

		if(!(tiles[target[0]][target[1]].checked)){

			Coord c_ = current.copy();
			Coord p_ = target.copy();

			q.push(p_);

			tiles[target[0]][target[1]].checked = true;
			tiles[target[0]][target[1]].parent = c_;
		}
	}
}

std::vector<Coord> Level::bfsDiag(Coord start, Coord end){

	resetPF();

	std::queue<Coord> q;
	q.push(start.copy());

	while(!q.empty()){

		Coord current = q.front().copy();
		q.pop();

		if (current == end){
			break;
		}
	
		Coord target;

		target = current + Coord(1, 0);
		tryAddPassable(current, q, target);

		target = current + Coord(-1, 0);
		tryAddPassable(current, q, target);

		target = current + Coord(0, 1);
		tryAddPassable(current, q, target);

		target = current + Coord(0, -1);
		tryAddPassable(current, q, target);
	
		target = current + Coord(1, 1);
		tryAddPassable(current, q, target);

		target = current + Coord(-1, 1);
		tryAddPassable(current, q, target);

		target = current + Coord(1, -1);
		tryAddPassable(current, q, target);

		target = current + Coord(-1, -1);
		tryAddPassable(current, q, target);
	}

	std::vector<Coord> path = traceBack(end, start);
	return path;
}

std::vector<Coord> Level::bfsPerp(Coord start, Coord end){

	resetPF();

	std::queue<Coord> q;
	q.push(start.copy());

	while(!q.empty()){

		Coord current = q.front().copy();
		q.pop();

		if (current == end){
			break;
		}
	
		Coord target;

		target = current + Coord(1, 0);
		tryAdd(current, q, target);

		target = current + Coord(-1, 0);
		tryAdd(current, q, target);

		target = current + Coord(0, 1);
		tryAdd(current, q, target);

		target = current + Coord(0, -1);
		tryAdd(current, q, target);
	}

	std::vector<Coord> path = traceBack(end, start);
	return path;
}

void Level::resetPF(){

	for (auto x=0; x < size[0]; x++) {
		for (auto y=0; y < size[1]; y++) {
			tiles[x][y].checked = false;
			tiles[x][y].parent = Coord(0,0);
		}
	}
}

std::vector<Coord> Level::traceBack(Coord end, Coord start){

	std::vector<Coord> path;
	Coord current = end.copy();  

	int count = 0;

	while(current != start){

		Coord c_ = current.copy();

		path.push_back(c_);
		current = tiles[current[0]][current[1]].parent.copy();

		count++;

		if (count == 100 || current == Coord(0,0)){
			std::cout << "Oops" << std::endl;
			break;
		}
	}

	path.push_back(start.copy());

	return path;
}

std::vector<Coord> Level::getAdjPassable(Coord s){

	std::vector<Coord> sample;

	return sample;
	
}

Coord Level::throwLocation(Coord start, Coord dir){

	Coord step = start.copy();

	while((*this)[step].isPassable() && !monsterAt(step)){
		step = step + dir;
	}

	return step;
}

bool Level::monsterAt(Coord s){

	for (ClockItem c : mobs){
		if (c.mob->getLocation() == s){
			return true;
		}
	}

	return false;
}
