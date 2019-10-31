#pragma once
#include <fstream>
#include "Map.h"
#include <string>

class MapLoader
{
public:
	MapLoader();
	MapLoader(string, Map*);
	~MapLoader();
};

class MapLoaderException
{
public:
	string message;
	MapLoaderException();
	MapLoaderException(string);
	~MapLoaderException();
};

