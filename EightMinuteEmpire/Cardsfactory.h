#pragma once
#include "cards.h"

class Cardsfactory {
public:
	static Cards* Create(string, vector<string>, vector<string>);
private:
	Cardsfactory();
};

class MoveArmiesCard : public Cards {
public:
	MoveArmiesCard();
	MoveArmiesCard(string good, vector<string> action, vector<string> num);
	MoveArmiesCard(const MoveArmiesCard&);
	MoveArmiesCard& operator=(const MoveArmiesCard&);
	~MoveArmiesCard();
};

class WaterMoveArmiesCard : public Cards {
public:
	WaterMoveArmiesCard();
	WaterMoveArmiesCard(string good, vector<string> action, vector<string> num);
	WaterMoveArmiesCard(const WaterMoveArmiesCard&);
	WaterMoveArmiesCard& operator=(const WaterMoveArmiesCard&);
	~WaterMoveArmiesCard();
};

class PlaceArmiesCard : public Cards {
public:
	PlaceArmiesCard();
	PlaceArmiesCard(string good, vector<string> action, vector<string> num);
	PlaceArmiesCard(const PlaceArmiesCard&);
	PlaceArmiesCard& operator=(const PlaceArmiesCard&);
	~PlaceArmiesCard();
};

class DestroyArmiesCard : public Cards {
public:
	DestroyArmiesCard();
	DestroyArmiesCard(string good, vector<string> action, vector<string> num);
	DestroyArmiesCard(const DestroyArmiesCard&);
	DestroyArmiesCard& operator=(const DestroyArmiesCard&);
	~DestroyArmiesCard();
};

class CreateCityCard : public Cards {
public:
	CreateCityCard();
	CreateCityCard(string good, vector<string> action, vector<string> num);
	CreateCityCard(const CreateCityCard&);
	CreateCityCard& operator=(const CreateCityCard&);
	~CreateCityCard();
};

class AndCard : public Cards {
public:
	AndCard();
	AndCard(string good, vector<string> action, vector<string> num);
	AndCard(const AndCard&);
	AndCard& operator=(const AndCard&);
	~AndCard();
};

class OrCard : public Cards {
public:
	OrCard();
	OrCard(string good, vector<string> action, vector<string> num);
	OrCard(const OrCard&);
	OrCard& operator=(const OrCard&);
	~OrCard();
};