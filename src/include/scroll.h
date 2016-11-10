/**
 * @file scroll.h
 * @author Team Rogue++
 * @date November 09, 2016
 *
 * @brief Member declarations for the Scroll class
 */ 

#pragma once

#include <string>
#include <vector>

#include "coord.h"
#include "item.h"

// <Name>
using SCROLL_TUPLE_TYPE = std::tuple<std::string>;

class Level;

class Scroll : public Item {
	public:
		static std::vector<std::string> initializeScrollNames();

		Scroll(Coord);
		Scroll(Coord, Item::Context, int);
		bool activate(Level*);

	private:
		static std::vector<SCROLL_TUPLE_TYPE > typeVector;
		static std::vector<std::string> nameVector;
		static std::vector<std::string> syllableVector;
};