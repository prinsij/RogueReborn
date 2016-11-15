/**
 * @file feature.h
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member declarations for the Feature class
 */ 

#pragma once

#include "coord.h"

/** Models a 'thing' in the dungeon
 *  that has position and may be visible.
 * This is to provide a common superclass
 * to various classes that would otherwise
 * cause duplicate code, such as items, staircases,
 * traps, etc
 */
class Feature {
	public:
		/** Constructor for symbol, location. */
		Feature(char, Coord, bool visible=true);
		/** Getter for symbol.
		 * @see symbol
		 */
		char getSymbol();
		/** Getter for location.
		 * @see location
		 */
		Coord getLocation();
		/** Setter for location.
		 * @see location
		 */
		/** Getter for visibility.
		 * @see visible
		 */
		bool getVisible();
		void setLocation(Coord);
		/** Destructor. */
		virtual ~Feature();
	private:
		/** Position of the feature within the level. */
		Coord location;
		/** Character representing
		 *  the feature in the display.
		 */
		char symbol;
	protected:
		/** Whether the feature is visible to the player. */
		bool visible;
};
