#include <iostream>
#include "Map.h"

using namespace std;

int main()
{
	cout << "Calling Map::getInstance() to create the map." << endl;
	Map* map1 = Map::getInstance();
	cout << "Lets try calling Map::getInstance() again." << endl;
	Map* map2 = Map::getInstance();
	cout << "A new map was not created; the same instance was returned!" << endl;

	if (map1 == map2) {
		cout << "Both map objects are referencing the same address!" << endl;
	}

	delete map1;
	map1 = NULL;
	map2 = NULL;
}
