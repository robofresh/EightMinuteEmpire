#pragma once
#include "GameEngine.h"
#include <string>
#include <vector>
#include "global.h"

using namespace std;
//Exception struct of Wrong input type
struct InputException : public exception
{
	const char* what() const throw()
	{
		return "Your input is invalid.";
	}
};

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


//Iterate and create players for the game
//Only called for TournamentMode
void GameEngine::createPlayers()
{
	for (int i = 0; i < *NUM_PLAYERS; i++)
	{
	
		string name;
		int age;
		int answer;
		cout << "New player, enter your name: ";
		cin >> name;
		
		while (true)
		{
			cout << "Enter your age: ";
			try
			{
				cin >> age;
				if (cin.fail()||age>100||age<1)
					throw InputException();
			}
			catch (InputException e)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << e.what() << endl;
			}
			if (age > 0 && age < 100)
				break;
		}
		//Selection of strategy
		while (true)
		{
			cout << "Select a strategy for the new player:" << endl;
			cout << "1. Greedy Strategy" << endl;
			cout << "2. Moderate Strategy" << endl;
			try
			{
				cin >> answer;
				if (cin.fail())
					throw InputException();
				if (answer == 1 || answer == 2)
					break;
				else
					throw InputException();
			}
			catch (InputException e)
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << e.what() << endl;
			}
		}

		Player* player = new Player(name, age, *NUM_COINS_PER_PLAYER, global::COLORS[i], deck);
		if (answer == 1)
			player->set_strategy(new Greedy());
		if (answer == 2)
			player->set_strategy(new Greedy());
		players->push_back(player);
		player->printPlayer();
		player = NULL;
		delete player;
	}
}

GameEngine::GameEngine() 
{
	mode= new Mode( GameEngine::Mode::single);
	global::map = map = nullptr;
	global::main_deck = deck = nullptr;
	global::supply= supply = nullptr;
	global::players = players = new vector<Player*>();
	startingCountry = nullptr;
	NUM_PLAYERS = nullptr;
	NUM_COINS_PER_PLAYER = nullptr;
	strategy = nullptr;

}

GameEngine::GameEngine(string modeChosen) 
{
	mode = new Mode(modeChosen == "tournament" ? GameEngine::Mode::tournament: GameEngine::Mode::single);//default mode will be single game
	global::map = map = nullptr;
	global::main_deck=deck = nullptr;
	global::supply= supply = nullptr;
	global::players = players = new vector<Player*>();
	startingCountry = nullptr;
	NUM_PLAYERS = nullptr;
	NUM_COINS_PER_PLAYER = nullptr;
	strategy = nullptr;
	if (modeChosen == "tournament")
		set_strategy(new TournamentMode());
	if (modeChosen == "single")
		set_strategy(new SingleMode());

}

GameEngine::~GameEngine()
{
	delete map, mode, deck, supply, players, startingCountry, NUM_COINS_PER_PLAYER, NUM_PLAYERS, strategy;
	map = NULL;
	mode = NULL;
	deck = NULL;
	supply = NULL;
	players = NULL;
	startingCountry = NULL;
	NUM_COINS_PER_PLAYER = NULL;
	NUM_PLAYERS = NULL;
	strategy = NULL;
}

void GameEngine::setMode(string modeChosen)
{
	if (modeChosen == "tournament")
		mode =new Mode(GameEngine::Mode:: tournament);
	if (modeChosen == "single")
		mode = new Mode(GameEngine::Mode::single);
}

int GameEngine::getMode()
{
	return static_cast<int>(*this->mode);
}

void GameEngine::setStartingCountry(Country* country)
{
	startingCountry = country;
}

Country* GameEngine::getStartingCountry()
{
	return startingCountry;
}

void GameEngine::chooseMap()
{
	// Select map from list of files.
	global::map = map = Map::getInstance();
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
	delete mapLoader;
}
//Retrieve numbers of players for the game
 void GameEngine::setNumOfPlayers()
{
	int playerInput;
	while (true)
	{
		cout << "Enter the number of players [2-5] who will be playing this game: ";
		cin >> playerInput;
		if (cin.fail() || playerInput < 2 || playerInput > 5)
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
	NUM_PLAYERS = new int(playerInput);
	setNumCoinsPerPlayer(*NUM_PLAYERS);
}

 int* GameEngine::getNumCoinsPerPlayer()
 {
	 return NUM_COINS_PER_PLAYER;
 }

 void GameEngine::setNumCoinsPerPlayer(const int numPlayers)
 {
	 int numCoinsPerPlayer = 0;
	 switch (numPlayers)
	 {
	 case 2:
		 numCoinsPerPlayer = 14;
		 break;
	 case 3:
		 numCoinsPerPlayer = 11;
		 break;
	 case 4:
		 numCoinsPerPlayer = 9;
		 break;
	 case 5:
		 numCoinsPerPlayer = 8;
		 break;
	 default:
		 break;
	 }
	NUM_COINS_PER_PLAYER = new int(numCoinsPerPlayer);
 }

 int* GameEngine::getNumOfPlayers()
 {
	 return NUM_PLAYERS;
 }

 Deck* GameEngine::getDeck()
 {
	 return deck;
 }

 void GameEngine::setSupply()
 {
	 supply = new int (44 - (*NUM_COINS_PER_PLAYER * *NUM_PLAYERS));
	 global::supply = supply;
	 cout << "Total supply of coins was 44, but since each player took " << *NUM_COINS_PER_PLAYER << " coins, supply is now at " << *supply << " coins.\n" << endl;
 }

 int* GameEngine::getSupply()
 {
	 return supply;
 }
//New choosePlayers
 void GameEngine::choosePlayers()
{
	 setNumOfPlayers();
	 createPlayers();//+ set their strategy

}

 void GameEngine::set_strategy(StrategyG* mode)
 {
	 delete strategy;
	 strategy = mode;
 }

 void GameEngine::execute_strategy()
 {
	 strategy->execute(*this);
 }

 StrategyG* GameEngine::get_strategy()
 {
	 return strategy;
 }