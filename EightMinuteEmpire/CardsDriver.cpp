//#include <iostream>
//#include "Cards.h"
//
//int main()
//{
//    Deck* deck = new Deck(); //make a deck object
//	//Testing purpose
//	Cards* cards0 = new Cards("0", "invade");
//	Cards* cards1 = new Cards("1", "invade");
//	Cards* cards2 = new Cards("2", "invade");
//	Cards* cards3 = new Cards("3", "invade"); 
//	Cards* cards4 = new Cards("4", "invade"); 
//	Cards* cards5 = new Cards("5", "invade"); 
//	Cards* cards6 = new Cards("6", "invade");
//
//	deck->stackofCards->push(cards0);
//	deck->stackofCards->push(cards1);
//	deck->stackofCards->push(cards2);
//	deck->stackofCards->push(cards3);
//	deck->stackofCards->push(cards4);
//	deck->stackofCards->push(cards5);
//	deck->stackofCards->push(cards6);
//
//	deck->initialDraw();
//
//	for (int i = 0; i < deck->drawingcards->faceupcards->size(); i++)
//	{
//		cout << *deck->drawingcards->faceupcards->at(i)->good << endl;
//	}
//
//	deck->drawingcards->exchange(3);
//
//	for (int i = 0; i < deck->drawingcards->faceupcards->size(); i++)
//	{
//		cout << *deck->drawingcards->faceupcards->at(i)->good << endl;
//	}
//}