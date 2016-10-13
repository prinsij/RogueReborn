
#include "include/tunnel.h"
#include "include/terrain.h"
#include <vector>
#include "include/tiles.h"
#include "include/level.h"
#include "include/coord.h"
#include "include/room.h"
#include "include/random.h"

Tunnel::Tunnel(Room* p, Room* q) 
	: p(p)
	, q(q)
{}