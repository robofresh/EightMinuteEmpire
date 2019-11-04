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
//
//using namespace std;
//void shuffleCards(vector<Cards*>*);
//void shuffleCards(vector<Cards*>* listCard)
//{
//
//	for (int i = 0; i < listCard->size(); i++)
//	{
//		swap(listCard->at(i), listCard->at(rand() % listCard->size()));
//	}
//}
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
//
//	for (int i = 0; i < allCards->size(); i++)
//	{
//		int* temp;
//		cout << " Card " << (i + 1) << endl;
//		cout << "Good is : " << *allCards->at(i)->good << endl;
//		cout << "Action is : ";
//		temp = new int(allCards->at(i)->actions->size());
//
//		if (temp != 0)
//		{
//			for (int j = 0; j < *temp; j++)
//			{
//				cout << *allCards->at(i)->actions->at(j) << " ";
//			}
//			cout << endl;
//		}
//	}
//
//	shuffleCards(allCards);
//
//	cout << "AFTER SHUFFLINGGGG" << endl;
//
//
//	for (int i = 0; i < allCards->size(); i++)
//	{
//		int* temp;
//		cout << " Card " << (i + 1) << endl;
//		cout << "Good is : " << *allCards->at(i)->good << endl;
//		cout << "Action is : ";
//		temp = new int(allCards->at(i)->actions->size());
//
//		if (temp != 0)
//		{
//			for (int j = 0; j < *temp; j++)
//			{
//				cout << *allCards->at(i)->actions->at(j) << " ";
//			}
//			cout << endl;
//		}
//	}
//
//
//
//
//}
//
//
