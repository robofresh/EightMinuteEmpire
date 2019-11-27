#pragma once
#include "GameEngine.h"

//getMapFileName returns the name of the file
string getMapFileName()
{
	string mapFileName = "";
	int fileSelectInput;

	cout << "The following map choices exist for the game:" << endl;
	cout << "\t[1] map1.map" << endl;
	cout << "\t[2] invalidMap.map" << endl;
	cout << "\t[3] nonexistantMap.map" << endl;
	while (true)
	{
		cout << "Enter the number of the map to use for the game: ";
		cin >> fileSelectInput;
		if (fileSelectInput < 1 || fileSelectInput > 3)
		{
			cout << "You've entered a number outside of the correct range. Try again." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // See [1]
		}
		else
		{
			cout << endl;
			break;
		}
	}
	switch (fileSelectInput)
	{
	case 1:
		mapFileName = "map1.map";
		break;
	case 2:
		mapFileName = "invalidMap.map";
		break;
	case 3:
		mapFileName = "nonexistantMap.map";
		break;
	default:
		break;
	}
	return mapFileName;
}

GameEngine::GameEngine() 
{
	mode = NULL;
	map = nullptr;
	mapLoader = nullptr;
	deck = nullptr;
	supply = nullptr;
	players = nullptr;

}

GameEngine::GameEngine(mode modeChosen) 
{
	mode = (modeChosen == tournament ? tournament : single);//default mode will be single game
	map = nullptr;
	mapLoader = nullptr;
	deck = nullptr;
	supply = nullptr;
	players = nullptr;
}

GameEngine::~GameEngine()
{
	delete mode, map, mapLoader, deck, supply, players;
	mode = NULL;
	map = NULL;
	mapLoader = NULL;
	deck = NULL;
	supply = NULL;
	players = NULL;
}

GameEngine::setMode(mode modeChosen)
{
	if (modeChosen == tournament)
		mode = tournament;
	if (modeChosen == single)
		mode = single;
	else
		cout << "Mode invalid" << endl;// TODO: Need to handle this exception
}

GameEngine::setStartingCountry(Country* country)
{
	startingCountry = country;

}

GameEngine::chooseMap()
{
	// Select map from list of files.
	map = Map::getInstance();
	MapLoader* mapLoader = nullptr;
	while (true)
	{
		string mapFileName = getMapFileName();
		try
		{
			mapLoader = new MapLoader(mapFileName, map);
			break;
		}
		catch (const MapLoaderException & e)
		{
			cout << e.message << endl;
			cout << "Try again." << endl;
			cout << endl;
			delete mapLoader;
		}
	}
	cout << "You've selected the following map: " << endl;
	map->print();
	cout << endl;
	setStartingCountry(map->startingCountry); //Starting country is loaded from map
}