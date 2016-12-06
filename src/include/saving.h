/**
 * @file saving.h
 * @author Team Rogue++
 * @date December 06, 2016
 *
 * @brief Global members
 */ 

#pragma once

#include <string>
#include <tuple>

class PlayerChar;
class Level;

std::string encode(PlayerChar*, Level*);

std::tuple<PlayerChar*, Level*> decode(std::string);
