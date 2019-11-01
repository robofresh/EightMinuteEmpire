#include "Actions.h"
#include "MapLoader.h"

using namespace std;

int main()
{
	Deck *deck = new Deck();
	deck->initialDraw();
	vector<Player*>* playersVector = new vector<Player*>();
	Player* play1 = new Player("scott", 1, 1, "red");
	playersVector->push_back(play1);
	Map* map = new Map();
	MapLoader* mapLoad = new MapLoader("map1.map", map);
	delete mapLoad;


	Actions* act = new Actions();


	act->processAction(play1, deck->drawingcards->exchange(0), map, playersVector);
	act->processAction(play1, deck->drawingcards->exchange(0), map, playersVector);
	act->processAction(play1, deck->drawingcards->exchange(0), map, playersVector);
	act->processAction(play1, deck->drawingcards->exchange(0), map, playersVector);
	act->processAction(play1, deck->drawingcards->exchange(0), map, playersVector);
	act->processAction(play1, deck->drawingcards->exchange(0), map, playersVector);
	act->processAction(play1, deck->drawingcards->exchange(0), map, playersVector);
	act->processAction(play1, deck->drawingcards->exchange(0), map, playersVector);
	act->processAction(play1, deck->drawingcards->exchange(0), map, playersVector);



	map->print();
	play1->printPlayer();

}