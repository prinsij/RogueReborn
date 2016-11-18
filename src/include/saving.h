#pragma once

#include <string>
#include <tuple>

class PlayerChar;
class Level;

std::string encode(PlayerChar*, Level*);

std::tuple<PlayerChar*, Level*> decode(std::string);
