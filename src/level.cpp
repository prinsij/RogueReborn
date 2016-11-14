/**
 * @file level.cpp
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member definitions for the Level class
 */ 

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <math.h>
#include <queue>
#include <vector>

#include "include/coord.h"
#include "include/feature.h"
#include "include/food.h"
#include "include/goldpile.h"
#include "include/level.h"
#include "include/mob.h"
#include "include/monster.h"
#include "include/playerchar.h"
#include "include/potion.h"
#include "include/random.h"
#include "include/room.h"
#include "include/stairs.h"
#include "include/terrain.h"
#include "include/tiles.h"
#include "include/trap.h"
#include "include/tunnel.h"

Level::Level(int depth, PlayerChar* player)
	: player(player)
	, size(getSize())
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

PlayerChar* Level::getPlayer() {
	return player;
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

void Level::removeMob(Mob* mob) {
	for (auto it=mobs.begin(); it != mobs.end(); ++it) {
		if (it->mob == mob) {
			mobs.erase(it);
			break;
		}
	}
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
	/*for (ClockItem& item : mobs) {
		std::cout << item.mob->getName() << " " << item.delay << "\n";
	}*/
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
	mobs.insert(mobs.end(), ClockItem(which, newTime));
}

std::vector<Mob*> Level::getMobs() {
	std::vector<Mob*> result;
	for (auto &item : mobs) {
		result.push_back(item.mob);
	}
	return result;
}

void Level::generate() {

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
	// Place mobs
	for (int i=0; i < 40; i++) {
		Coord randPos = Coord(gen.intFromRange(0, X_SIZE-1),
							  gen.intFromRange(0, Y_SIZE-1));
		if (tileAt(randPos).isPassable() == Terrain::Passable && !monsterAt(randPos)) {
			std::vector<char> monsterSymbols = Monster::getSymbolsForLevel(depth);
			char monsterSymbol = monsterSymbols[Generator::intFromRange(0, monsterSymbols.size() - 1)];

			Mob* m = new Monster(monsterSymbol, randPos);
			std::cout << "Creating " << m->getName() << " at: " << randPos.toString() << std::endl;
			registerMob(m);
		}
	}
	// Place staircase
	while (true) {
		Coord randPos = Coord(gen.intFromRange(0, X_SIZE-1),
							  gen.intFromRange(0, Y_SIZE-1));
		if (tileAt(randPos).isPassable() == Terrain::Passable) {
			for (Room& r : rooms) {
				if (r.contains(randPos)) {
					features.push_back(new Stairs(randPos, true));
					goto stair_exit;
				}
			}
		}
	}
	stair_exit:;
	// Place gold
	int i = 0;
	while (i < 15) {
		Coord randPos = Coord(gen.intFromRange(0, X_SIZE-1),
							  gen.intFromRange(0, Y_SIZE-1));
		if (tileAt(randPos).isPassable() == Terrain::Passable) {
			features.push_back(new GoldPile(randPos, gen.intFromRange(1, 35)));
			++i;
		}
	}
	i = 0;
	while (i < 15) {
		Coord randPos = Coord(gen.intFromRange(0, X_SIZE-1),
							  gen.intFromRange(0, Y_SIZE-1));
		if (tileAt(randPos).isPassable() == Terrain::Passable) {
			features.push_back(new Potion(randPos));
			++i;
		}
	}
	i = 0;
	while (i < 15) {
		Coord randPos = Coord(gen.intFromRange(0, X_SIZE-1),
							  gen.intFromRange(0, Y_SIZE-1));
		if (tileAt(randPos).isPassable() == Terrain::Passable) {
			features.push_back(new Trap(randPos, 0, true));
			++i;
		}
	}
	i = 0;
	while (i < 15) {
		Coord randPos = Coord(gen.intFromRange(0, X_SIZE-1),
							  gen.intFromRange(0, Y_SIZE-1));
		if (tileAt(randPos).isPassable() == Terrain::Passable) {
			features.push_back(new Food(randPos, Item::FLOOR));
			++i;
		}
	}
	this->placePlayerInStartingPosition();
	this->brother = this;
}

void Level::addTunnel(int i, int j, bool* a, bool* b, Generator gen){
	if (!(*a)){
		*a = true;
		*b = true;
		tunnels.push_back(Tunnel(&rooms[i], &rooms[j], gen));
	}
}

Level* Level::getBro(){
	return this->brother;
}

void Level::setBro(Level* l){
	this->brother = l;
}

void Level::tryAddPassable(Coord current, std::queue<Coord>& q, Coord target, Coord end){

	if (target[0] > 0 && target[0] < size[0] && target[1] > 0 && target[1] < size[1]){

		if(tiles[target[0]][target[1]].isPassable() == Terrain::Passable && !(tiles[target[0]][target[1]].checked) && ( end == target || !monsterAt(target))){

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
		tryAddPassable(current, q, target, end);

		target = current + Coord(-1, 0);
		tryAddPassable(current, q, target, end);

		target = current + Coord(0, 1);
		tryAddPassable(current, q, target, end);

		target = current + Coord(0, -1);
		tryAddPassable(current, q, target, end);

		target = current + Coord(1, 1);
		tryAddPassable(current, q, target, end);

		target = current + Coord(-1, 1);
		tryAddPassable(current, q, target, end);

		target = current + Coord(1, -1);
		tryAddPassable(current, q, target, end);

		target = current + Coord(-1, -1);
		tryAddPassable(current, q, target, end);
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
			std::cout << "Oops " << count << std::endl;
			break;
		}
	}

	path.push_back(start.copy());
	std::reverse(path.begin(), path.end());
	return path;
}

std::vector<Coord> Level::getAdjPassable(Coord ori){

	std::vector<Coord> sample;
	for (Coord& ortho : Coord::ORTHO) {
		Coord adj = ortho + ori;
		if (contains(adj) && tileAt(adj).isPassable() == Terrain::Passable && !monsterAt(adj) ) {
			sample.push_back(adj);
		}
	}

	return sample;

}

bool Level::canSee(Coord a, Coord b){

	for (auto r : rooms){
		if (r.contains(a) && r.contains(b)){
			return true;
		}
	}

	return false;
}

Coord Level::throwLocation(Coord start, Coord dir){

	Coord step = start.copy();

	while((*this)[step].isPassable() && !monsterAt(step)){
		step = step + dir;
	}

	return step;
}

Mob* Level::monsterAt(Coord s){

	for (ClockItem c : mobs){
		if (c.mob->getLocation() == s){
			return c.mob;
		}
	}

	return NULL;
}



Level::~Level() {
	for (Feature* feat : features) {
		delete feat;
	}
	for (auto& item : mobs) {
		auto* pc = dynamic_cast<PlayerChar*>(item.mob);
		if (pc == NULL) {
			delete item.mob;
		}
	}
}

std::vector<Coord> Level::getNearestGold(Coord ori) {

	std::vector<std::vector<Coord> > paths;

	uint mindex = 999;
	uint minlen = 999;

	for (uint i = 0; i < golds.size(); ++i){

		paths.push_back(bfsDiag(ori, golds[i].getLocation()));

		if (paths[i].size() < minlen){
			minlen = paths[i].size();
			mindex = i;
		}
	}

	if (mindex != 999){
		return paths[mindex];
	} else {
		return {};
	}
}

void Level::removeFeature(Feature* feat) {
	features.erase(std::find(
			features.begin(),
			features.end(), feat));
}

void Level::addFeature(Feature* feat) {
	features.push_back(feat);
}

void Level::placePlayerInStartingPosition() {

	int roomIndex = 0;
	int count = 0;

	do {
		roomIndex = Generator::intFromRange(0,rooms.size()-1);
		count++;
	} while (!rooms[roomIndex].exists() || count < 100);

	player->move(Generator::randPosition(rooms[roomIndex].getPosition1(), rooms[roomIndex].getPosition2()));

}
