#pragma once
#include "GameObservers.h"
#include "Player.h"
#include "cards.h"


Observer::Observer()
{/*Intentionally Empty*/
}

Observer::~Observer()
{/*Intentionally Empty*/
}

Subject::Subject()
{
	observers = new list<Observer*>;
}


Subject::~Subject()
{
	delete observers;
}

void Subject::Attach(Observer* ob)
{
	observers->push_back(ob);
}

void Subject::Detach(Observer* ob)
{
	observers->remove(ob);
}

void Subject::Notify()
{
	list<Observer*>::iterator i = observers->begin();
	for (; i != observers->end(); i++)
	{
		
		(*i)->Update();
	}
}

PlayerObserver::PlayerObserver()
{}

PlayerObserver::PlayerObserver(Player* player, int* index)
{
	_playerSubject = player;
	_playerSubject->Attach(this);
	_index = index;
}

PlayerObserver::~PlayerObserver()
{
	_playerSubject->Detach(this);
	delete _index;
	_index = NULL;
}

void PlayerObserver::Update()
{
	display();
}

void PlayerObserver::display()
{
	cout << "**********Player "<<*this->_index  <<" " 
		<< *_playerSubject->name << "'s turn.**********" << endl;

}

CurrentPOb::CurrentPOb()
{}

CurrentPOb::CurrentPOb(Player* player, Cards* chosen, int* position, int* supply)
{
	_playerSubject = player;
	_playerSubject->Attach(this);
	_cardChosen = chosen;
	this->position = position;
	_supply = supply;
}

CurrentPOb::~CurrentPOb()
{
	_playerSubject->Detach(this);
}

void CurrentPOb::Update()
{
	display();
}

//void CurrentPOb::display()
//{
//	cout << "dislay observer from currentPOb" << endl;
//	this->_cardChosen->print();
//}

void CurrentPOb::display()
{
	cout << "*************dislay observer from currentPOb************" << endl;
	cout<< "Player " <<*this->_playerSubject->name
		<< " selects the " << *this->position 
		<< "th card from the left." <<endl;
	this->_cardChosen->print();
}

PayOb::PayOb()
{}

PayOb::PayOb(Player* player, int* cost, int*supply)
{
	_playerSubject = player;
	_playerSubject->Attach(this);
	this->cost = cost;
	this->supply = supply;

}

PayOb::~PayOb()
{
	_playerSubject->Detach(this);
}
void PayOb::display()
{
	cout << "************Inside payOb display***************" << endl;
	cout << *(_playerSubject->name) << " is paying " << *cost << " coins." << endl;
	cout << *(_playerSubject->name) << " now has " << *(_playerSubject->numCoins) << " coins." << endl;
	cout << "The Game Supply now has : " << *supply << " coins." << endl;
}

void PayOb::Update()
{
	display();
}

ActionOb::ActionOb(){}

ActionOb::ActionOb(Player* player, Cards* card)
{
	_playerSubject = player;
	_cardChosen = card;
	card->Attach(this);
	_action = new vector<string*>();
	_amount = new vector<int*>();

}

ActionOb::ActionOb(Player* player, Cards* card, string* action)
{
	_playerSubject = player;
	_cardChosen = card;
	card->Attach(this);
	_action = new vector<string*>();

	for (int i = 0; i < _cardChosen->actions->size(); i++)
	{
		_action->push_back(_cardChosen->actions->at(i));
	}
	_amount = new vector<int*>();;


}

//TODO: Modify args
ActionOb::ActionOb(Player* player, Cards* card, string* action, int* amount)
{
	_playerSubject = player;
	_cardChosen = card;
	card->Attach(this);
	_action = new vector<string*>();
	for (int i = 0; i < _cardChosen->actions->size(); i++)
	{
		_action->push_back(_cardChosen->actions->at(i));
	}
	_amount = new vector<int*>();


}

ActionOb::~ActionOb()
{

}

void ActionOb::setAction(string* action)
{
	//for (int i = 0; i < _cardChosen->actions->size(); i++)
	//{
	//	_action->push_back(_cardChosen->actions->at(i));
	//}
	this->_action->push_back(action);

}

void ActionOb::setAmount(int* amount)
{
	_amount->push_back(amount);
}

void ActionOb::display()
{
	cout << "****** INSIDE ACTION OB******" << endl;
	cout << "Chosen card is : " << endl;

	cout << "[Good is : " << *_cardChosen->good;
	cout << ", Action is : ";
	const int temp = _cardChosen->actions->size();

	if (temp != 0)
	{
		for (int j = 0; j < temp; j++)
		{
			cout << *_cardChosen->actions->at(j) << " ";
		}
		cout << "]";

	}
	cout << endl;
	cout << endl;
	for (int i = 0; i < _action->size(); i++)
	{

		if (*_action->at(i) == "Ignore")
		{
			cout << "~ACTION TAKEN : Player " << *this->_playerSubject->name
				<< " choose to ignore the card.~" << endl;
			return;
		}

		if ("placeArmies" == *_action->at(i))
		{
			if (*_amount->at(i) > 1)
			{
				cout << "~ACTION TAKEN : Place " << *_amount->at(i) << " armies"<<endl;
				return;
			}
			cout << "~ACTION TAKEN : Place " << *_amount->at(i) << " army" << endl;;
		}

		if ("move" == *_action->at(i))
		{
			if (*_amount->at(i) > 1)
			{
				cout << "~ACTION TAKEN : Move " << *_amount->at(i) << " armies~" << endl;
				return;
			}
			cout << "~ACTION TAKEN : Move " << *_amount->at(i) << " army~"<<endl;
		}
		if ("createCity" == *_action->at(i))
		{
			if (*_amount->at(i) > 1)
			{
				cout << "~ACTION TAKEN :Create " << *_amount->at(i) << " cities~";
				return;
			}
			cout << "~ACTION TAKEN :Create " << *_amount->at(i) << " city~";
		}
		if ("waterMove" == *_action->at(i))
		{
			if (*_amount->at(i) > 1)
			{
				cout << "~ACTION TAKEN : Move " << *_amount->at(i) << " armies across water/land"<< endl;
				return;
			}
			cout << "~ACTION TAKEN : Move " << *_amount->at(i) << " army across water/land" << endl;
		}
		if ("destroyArmies" == *_action->at(i))
		{
			if (*_amount->at(i) > 1)
			{
				cout << "~ACTION TAKEN :Destroy " << *_amount->at(i) << " armies" << endl;
				return;
			}
			cout << "~ACTION TAKEN :Destroy " << *_amount->at(i) << " army"<<endl;
		}
	}




}

void ActionOb::Update()
{
	display();
}