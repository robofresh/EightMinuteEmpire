#pragma once
#include <fstream>
#include "Map.h"
#include <string>

class MapLoader
{
public:
	MapLoader() = default;
	MapLoader(const string&, Map*);
	~MapLoader() = default;
};

class MapLoaderException
{
public:
	string message;
	MapLoaderException();
	MapLoaderException(string);
	~MapLoaderException() = default;
};

