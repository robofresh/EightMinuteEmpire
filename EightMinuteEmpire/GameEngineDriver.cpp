#include <iostream>
#include <limits>
#include <vector>
#include "cards.h"
#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include "Actions.h"
#include "computeScore.h"
#include "GameEngine.h"
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

//Exception struct if insufficient Coins
struct InsufficientCoinsException : public exception
{
	const char* what() const throw()
	{
		return "Player does not have enough coins.";
	}
};



//Determine the amount of cards per player to reach to end the game
int determineMaxCards(int num_player)
{
	const int MAX_CARDS2 = 13;
	const int MAX_CARDS3 = 10;
	const int MAX_CARDS4 = 8;
	const int MAX_CARDS5 = 7;

	switch (num_player)
	{
	case 2:
		return MAX_CARDS2;
	case 3:
		return MAX_CARDS3;
	case 4:
		return MAX_CARDS4;
	default:
		return MAX_CARDS5;

	}
}


//Placing initial player's armies
void placeInitialPlayerArmies(vector<Player*>* players, Country* startingCountry)
{
	cout << "Each player must now place 3 of their army cubes on the starting country." << endl;
	for (int i = 0; i < players->size(); i++)
	{
		players->at(i)->placeNewArmies(startingCountry, 3);
	}
	cout << *(startingCountry->name) << ", the starting country, holds the following:" << endl;
	for (int i = 0; i < startingCountry->occupyingArmies->size(); i++)
	{
		cout << "A " << *(startingCountry->occupyingArmies->at(i)->player->color) << " army cube belonging to ";
		cout << *(startingCountry->occupyingArmies->at(i)->player->name) << endl;
	}
	cout << endl;
}

int main()
{
	// ######################################################################
	//				Part 1: Game Start and Setup
	// ######################################################################

	cout << "########################################" << endl;
	cout << "\tEight Minute Empire" << endl;
	cout << "########################################\n" << endl;

	string answerMode;

	cout << "Game starts!" << endl;

	//Selection of mode of Game
	cout << " Select mode " << endl;
	cin >> answerMode;
	GameEngine* game = new GameEngine(answerMode);
	cout << "GameEngine mode set to :" << game->getMode() << endl;
	if (game->getMode() == 1)
		game->set_strategy(new TournamentMode());
	else
		game->set_strategy(new SingleMode());

	//Selection of Map
	game->chooseMap();

	// Create deck with 42 cards. Shuffle method is done when creating a deck
	global::main_deck = new Deck();
	cout << "All " << global::main_deck->stackofCards->size() << " cards are shuffled and then putted into a deck and assigned to the game.\n" << endl;

	//Selection of Players by executing strategy
	game->execute_strategy();

	//Preparation for starting the game
	global::action = new Actions();
	placeInitialPlayerArmies(global::players, game->getStartingCountry());
	global::main_deck->initialDraw();

	//Set info for ending the game
	bool endGame = false;
	const int MAX_CARDS = determineMaxCards(*game->getNumOfPlayers());








	//Keep track of the last player of each round
	Player* lastPlayer;
	int lastIndex = (*global::currentPlayerIndex + *game->getNumOfPlayers() - 1) % *game->getNumOfPlayers();
	lastPlayer = global::players->at(lastIndex);

	//Attach PlayerOb on each player with their index
	PlayerObserver* observeP;
	int* track = new int(*global::currentPlayerIndex);
	int* turn = new int(1);

	do
	{
		observeP = new PlayerObserver(global::players->at(*track), turn);
		track = new int((*track + 1 + *game->getNumOfPlayers()) % *game->getNumOfPlayers());
		turn = new int(*turn + 1);
		observeP = NULL;


	} while (*track != *global::currentPlayerIndex);

	delete track;
	track = NULL;

	cout << "Let the game begin!\n" << endl;
	global::currentPlayer->Notify();


	// #################################################
	//				Part 2: Main Game Loop
	// #################################################

	int newIndex;
	do
	{
		global::currentPlayer->execute_strategy();
		
		cout << *(global::currentPlayer->name) << " now has "
			<< global::currentPlayer->hand->faceupcards->size()
			<< " cards" << endl;

		// #################################################
		//				Part 3: After Action
		// #################################################

		//Loop to the next player
		newIndex = *global::currentPlayerIndex + 1;//Increasing the index position is clockwise 
		*global::currentPlayerIndex = newIndex % *game->getNumOfPlayers();
		global::currentPlayer = global::players->at(*global::currentPlayerIndex);//update current player

		cout << endl;
		cout << "************************************************************" << endl;
		cout << endl;
		global::currentPlayer->Notify();
	
		// #################################################
		//			Part 6: Game End, Compute Score
		// #################################################

		if (lastPlayer->hand->faceupcards->size() >= MAX_CARDS)
		{
			cout << "Every Players has ";
			cout << global::currentPlayer->hand->faceupcards->size() << " cards. " << endl;
			cout << "Max cards each player can own has been reach. " << endl;
			endGame = true;
		}

	} while (!endGame);
	cout << endl;
	cout << "****************END OF GAME****************" << endl;

	//Compute Scores
	computeScore score = computeScore();
	Player* winner = score.determineWinner(global::players);

	cout << "The winner is " << *winner->name << endl;//Print the winner of the game
	
	for (int i = 0; i < global::players->size(); i++)//Prints all the players
	{
		global::players->at(i)->printPlayer();
	}


	// #################################################
	//						Cleanup
	// #################################################

	for (int i = 0; i < *game->getNumOfPlayers(); i++)
	{
		delete global::players->at(i);
	}
	delete global::players;
	global::players = NULL;
	delete global::main_deck;
	global::main_deck = NULL;
	delete Map::getInstance();
	global::supply = NULL;
	global::currentPlayer = NULL;
	delete global::currentPlayerIndex;
	global::currentPlayerIndex = NULL;
	lastPlayer = NULL;
	delete global::action;
	global::action = NULL;
	winner = NULL;
	delete observeP;
	observeP = NULL;
	delete turn;
	turn = NULL;



}

//Run program: Ctrl + F5 or Debug > Start Without Debugging menu
//Debug program: F5 or Debug > Start Debugging menu

//Tips for Getting Started: 
//  1. Use the Solution Explorer window to add/manage files
//  2. Use the Team Explorer window to connect to source control
//  3. Use the Output window to see build output and other messages
//  4. Use the Error List window to view errors
//  5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//  6. In the future, to open this project again, go to File > Open > Project and select the .sln file

// References
// [1] https://www.hackerearth.com/practice/notes/validating-user-input-in-c/
