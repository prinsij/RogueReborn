/**
 * Rogue Reborn Project
 * Team Rogue++
 * 
 * File: feature.h
 */ 

#pragma once

#include "coord.h"

class Feature {
	public:
		Feature(char, Coord);
		char getSymbol();
		Coord getLocation();
		void setLocation(Coord);
		virtual ~Feature();
	private:
		Coord location;
		char symbol;
};