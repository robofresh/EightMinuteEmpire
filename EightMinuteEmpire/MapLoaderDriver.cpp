#include "MapLoader.h"
#include "Map.h"
#include <fstream>
#include <algorithm>

int main()
{
	Map* map = new Map();

	MapLoader *mapLoader = new MapLoader("map1.txt", map);

	map->print();

}