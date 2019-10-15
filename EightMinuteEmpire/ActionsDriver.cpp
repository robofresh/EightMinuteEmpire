#include "Actions.h"

using namespace std;

int main()
{
	Deck *deck = new Deck();
	deck->initialDraw();
	Player* play1 = new Player("scott", 1, 1, "red");

	Actions* act = new Actions();

	act->processAction(play1, deck->drawingcards->faceupcards->at(2));
}