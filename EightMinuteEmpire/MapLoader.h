#pragma once
#include <fstream>
#include "Map.h"
#include <string>

class MapLoader
{
public:
	MapLoader(string, Map*);
	~MapLoader();

};

