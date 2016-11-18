/**
 * @file globals.h
 * @author Team Rogue++
 * @date November 14, 2016
 *
 * @brief Global members
 */ 

#pragma once

#include <string>

#include "../libtcod/include/libtcod.hpp"
#include "random.h"

//please don't put mutable state here

const int NUM_LEVELS = 26;
const int NAME_LENGTH = 10;
const std::string VALID_NAME =   "abcdefghijklmnopqrstuvwxyz _.ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string HALLUC_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int TURN_TIME = 50;
const int SLOW_TIME = 103;
const int FAST_TIME = 23;
const std::string VICTORY_STR = "Retrieved the Amulet of Yendor";
