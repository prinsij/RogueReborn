/**
 * @file feature.h
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Member declarations for the Feature class
 */ 

#pragma once

#include "coord.h"
#include "../libtcod/include/libtcod.hpp"
#include <vector>

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
		Feature(char, Coord, bool visible=true, TCODColor fcolor=TCODColor::white);
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
		/** Setter for visibility.
		 * @see visible
		 */
		void setVisible(bool);
		/** Setter for location.
		 * @see location
		 */
		void setLocation(Coord);
		/**
		 * @brief	Getter for the foreground color.
		 * @see		fcolor
		 * @return	Foreground color of the feature.
		 */
		TCODColor getFColor();
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
		/** Foreground color the feature. */
		TCODColor fcolor;
		/** Set of possible colors for randomly colored features. */
		const static std::vector<TCODColor> possibleColors;

};
