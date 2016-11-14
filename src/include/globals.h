/**
 * @file globals.h
 * @author Team Rogue++
 * @date November 13, 2016
 *
 * @brief Global members
 */ 

#pragma once

#include <string>

#include "random.h"
#include "../libtcod/include/libtcod.hpp"

//please don't put mutable state here

const int NUM_LEVELS = 26;
const int NAME_LENGTH = 10;
const std::string VALID_NAME =   "abcdefghijklmnopqrstuvwxyz _ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string HALLUC_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const int TURN_TIME = 50;
