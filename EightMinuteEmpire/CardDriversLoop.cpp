//#include "Actions.h"
//#include "MapLoader.h"
//#include "cards.h"
//#include "Player.h"
//#include <vector>
//#include <string>
//#include <algorithm>
//#include <random>
//#include <iostream>
//#include <stack>
//#include <ctime>
//
//using namespace std;
//
//
//int main()
//{
//	Deck* deck = new Deck();
//
//	vector<Cards*>* allCards = new vector<Cards*>();
//
//	allCards->push_back
//	(
//		new Cards(
//			"wild",
//			new vector<string*>
//			{
//				new string("waterMove"), new string("2")
//			}
//		)
//	);
//
//	allCards->push_back
//	(
//		new Cards(
//			"coal",
//			new vector<string*>
//			{
//				new string("placeArmies"), new string("3")
//			}
//		)
//	);
//
//	allCards->push_back
//	(
//		new Cards(
//			"coal",
//			new vector<string*>
//			{
//				new string("waterMove"), new string("2")
//			}
//		)
//	);
//
//	allCards->push_back
//	(
//		new Cards(
//			"coal",
//			new vector<string*>
//			{
//				new string("waterMove"), new string("2")
//			}
//		)
//	);
//
//	allCards->push_back
//	(
//		new Cards(
//			"coal",
//			new vector<string*>
//			{
//				new string("waterMove"), new string("3")
//			}
//		)
//	);
//
//	allCards->push_back
//	(
//		new Cards(
//			"gem",
//			new vector<string*>
//			{
//				new string("placeArmies"), new string("2")
//			}
//		)
//	);
//
//	allCards->push_back
//	(
//		new Cards(
//			"gem",
//			new vector<string*>
//			{
//				new string("placeArmies"), new string("2")
//			}
//		)
//	);
//
//	Cards* temp;
//	Cards* test = new Cards(
//		"TESTING",
//		new vector<string*>
//		{
//			new string("placeArmies"), new string("2")
//		}
//	);
//	deck->initialDraw();
//
//	deck->cardsSpace->print();
//
//	deck->updateCardsSpace(deck, 5);
//
//
//	cout << "AFTERRR UPDATING" << endl;
//
//
//	deck->cardsSpace->print();
//
//
//}
//
//
//
////int main() {
////
////	Cards* card1;
////
////	card1 = new Cards(
////		"Original",
////		new vector<string*>
////		{
////			new string("waterMove"), new string("2")
////		}
////	);
////
////	Cards* cCopy;
////
////	cCopy = new Cards(*card1);
////
////	cout << card1 << endl;
////	cout << cCopy << endl;
////
////	card1->print();
////	cCopy->print();
////
////}
