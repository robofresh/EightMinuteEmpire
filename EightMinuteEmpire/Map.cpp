#include "Map.h"

//with each country as a class, our map nodes will be pointers to those classes on the heap


Map::Map()
{
}


Map::~Map()
{
}



Country::Country(string inputName)
{
	name = new string(inputName);
}


Country::~Country()
{
}

Continent::Continent()
{
}


Continent::~Continent()
{
}
