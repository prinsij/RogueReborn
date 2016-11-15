/**
 * @file terrain.h
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member declarations for the Terrain class
 */ 

#pragma once

#include "coord.h"
#include "../libtcod/include/libtcod.hpp"

/** Represents a tile in the dungeon. */
class Terrain {
	public:
		/** Tiles can be walk-through-able or not. */
		enum Passability {Blocked, Passable};
		/** Tiles can have full, limited (Corridor), or no
		 *  visibility.
		 */
		enum Visibility {Opaque, Corridor, Transparent};
		/** Whether the player has previous seen the tile. */
		enum Mapped {Seen, UnSeen};
		/** Constructor. */
		Terrain(char, Visibility, Passability);
		/** Alternative constructor for tiles with a specific color. */
		Terrain(char, Visibility, Passability, TCODColor);
		/** Getter for character.
		 * @see character
		 */
		char getSymbol();
		/** Getter for passable.
		 * @see passable
		 */
		Passability isPassable();
		/** Getter for foreground color.
		 * @see color
		 */
		TCODColor getColor();
		/** Getter for seen.
		 * @see seen
		 */
		Mapped isSeen();
		/** Getter for visible
		 * @see visible
		 */
		Visibility getVisibility();
		/** Used by other modules for various searches.
		 * @see parent
		 */
		bool checked = false;
		/** Used by other modules for various searches.
		 * @see checked
		 */
		Coord parent;
		/** Setter for seen.
		 * @see seen
		 */
		void setIsSeen(Mapped);
	private:
		/** Symbol which represents the tile on the display. */
		char character;
		/** Degree of transparent of the tile. */
		Visibility visible;
		/** Whether the tile can be walked through. */
		Passability passable;
		/** Whether the tile has been seen by the player. */
		Mapped seen;
		/** Color the tile will be displayed with (foreground). */
		TCODColor color;
};
