#include "include/coord.h"
#include "include/feature.h"
#include "include/trap.h"

Trap::Trap(Coord location, unsigned char type, bool visible)
	: Feature('.', location),
	  type(type),
	  visible(visible) {}