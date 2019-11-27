#include "cards.h"
#include "Cardsfactory.h"

Cards* Cardsfactory::Create(string good, vector<string> type, vector<string> num) {
	if (type.at(0) == "AND") {
		cout << "In Cardsfactory, creating new AndCard (card with a '" << type.at(1) << " " << type.at(0) << " " << type.at(2) << "' action and a " << good << " good)."  << endl;
		return new AndCard(good, type, num);
	}
	else if (type.at(0) == "OR") {
		cout << "In Cardsfactory, creating new OrCard (card with a '" << type.at(1) << " " << type.at(0) << " " << type.at(2) << "' action and a " << good << " good)." << endl;
		return new OrCard(good, type, num);
	}
	else if (type.at(0) == "move") {
		cout << "In Cardsfactory, creating new MoveArmiesCard (card with a '" << type.at(0) << "' action and a " << good << " good)." << endl;
		return new MoveArmiesCard(good, type, num);
	}
	else if (type.at(0) == "waterMove") {
		cout << "In Cardsfactory, creating new WaterMoveArmiesCard (card with a '" << type.at(0) << "' action and a " << good << " good)." << endl;
		return new WaterMoveArmiesCard(good, type, num);
	}
	else if (type.at(0) == "placeArmies") {
		cout << "In Cardsfactory, creating new PlaceArmiesCard (card with a '" << type.at(0) << "' action and a " << good << " good)." << endl;
		return new PlaceArmiesCard(good, type, num);
	}
	else if (type.at(0) == "destroyArmies") {
		cout << "In Cardsfactory, creating new DestroyArmiesCard (card with a '" << type.at(0) << "' action and a " << good << " good)." << endl;
		return new DestroyArmiesCard(good, type, num);
	}
	else if (type.at(0) == "createCity") {
		cout << "In Cardsfactory, creating new CreateCityCard (card with a '" << type.at(0) << "' action and a " << good << " good)." << endl;
		return new CreateCityCard(good, type, num);
	}
}

// ############################################
//			MoveArmiesCard
// ############################################

MoveArmiesCard::MoveArmiesCard() : Cards()
{/*Intentionally Empty*/
};

MoveArmiesCard::MoveArmiesCard(string good, vector<string> action, vector<string> num)
	: Cards(
		good,
		new vector<string*>{
			new string(action.at(0)), new string(num.at(0))
		}
	) {/*Intentionally Empty*/
};

MoveArmiesCard::MoveArmiesCard(const MoveArmiesCard& other) : Cards(other)
{/*Intentionally Empty*/
};

MoveArmiesCard& MoveArmiesCard::operator=(const MoveArmiesCard& other)
{
	Cards::operator=(other);
	return *this;
};

MoveArmiesCard::~MoveArmiesCard()
{/*Intentionally Empty*/
};

// ############################################
//			WaterMoveArmiesCard
// ############################################

WaterMoveArmiesCard::WaterMoveArmiesCard() : Cards()
{/*Intentionally Empty*/
};

WaterMoveArmiesCard::WaterMoveArmiesCard(string good, vector<string> action, vector<string> num)
	: Cards(
		good,
		new vector<string*>{
			new string(action.at(0)), new string(num.at(0))
		}
	) {/*Intentionally Empty*/
};

WaterMoveArmiesCard::WaterMoveArmiesCard(const WaterMoveArmiesCard& other) : Cards(other)
{/*Intentionally Empty*/
};

WaterMoveArmiesCard& WaterMoveArmiesCard::operator=(const WaterMoveArmiesCard& other)
{
	Cards::operator=(other);
	return *this;
};

WaterMoveArmiesCard::~WaterMoveArmiesCard()
{/*Intentionally Empty*/
};

// ############################################
//			PlaceArmiesCard
// ############################################

PlaceArmiesCard::PlaceArmiesCard() : Cards()
{/*Intentionally Empty*/
};

PlaceArmiesCard::PlaceArmiesCard(string good, vector<string> action, vector<string> num)
	: Cards(
		good,
		new vector<string*>{
			new string(action.at(0)), new string(num.at(0))
		}
	) {/*Intentionally Empty*/
};

PlaceArmiesCard::PlaceArmiesCard(const PlaceArmiesCard& other) : Cards(other)
{/*Intentionally Empty*/
};

PlaceArmiesCard& PlaceArmiesCard::operator=(const PlaceArmiesCard& other)
{
	Cards::operator=(other);
	return *this;
};

PlaceArmiesCard::~PlaceArmiesCard()
{/*Intentionally Empty*/
};

// ############################################
//			DestroyArmiesCard
// ############################################

DestroyArmiesCard::DestroyArmiesCard() : Cards()
{/*Intentionally Empty*/
};

DestroyArmiesCard::DestroyArmiesCard(string good, vector<string> action, vector<string> num)
	: Cards(
		good,
		new vector<string*>{
			new string(action.at(0)), new string(num.at(0))
		}
	) {/*Intentionally Empty*/
};

DestroyArmiesCard::DestroyArmiesCard(const DestroyArmiesCard& other) : Cards(other)
{/*Intentionally Empty*/
};

DestroyArmiesCard& DestroyArmiesCard::operator=(const DestroyArmiesCard& other)
{
	Cards::operator=(other);
	return *this;
};

DestroyArmiesCard::~DestroyArmiesCard()
{/*Intentionally Empty*/
};

// ############################################
//			CreateCityCard
// ############################################

CreateCityCard::CreateCityCard() : Cards()
{/*Intentionally Empty*/ };

CreateCityCard::CreateCityCard(string good, vector<string> action, vector<string> num)
	: Cards(
		good,
		new vector<string*>{
			new string(action.at(0)), new string(num.at(0))
		}
	) {/*Intentionally Empty*/
};

CreateCityCard::CreateCityCard(const CreateCityCard& other) : Cards(other)
{/*Intentionally Empty*/};

CreateCityCard& CreateCityCard::operator=(const CreateCityCard& other)
{
	Cards::operator=(other);
	return *this;
};

CreateCityCard::~CreateCityCard()
{/*Intentionally Empty*/};

// ############################################
//			AndCard
// ############################################
AndCard::AndCard() : Cards()
{/*Intentionally Empty*/ };

AndCard::AndCard(string good, vector<string> action, vector<string> num)
	: Cards(
		good,
		new vector<string*>{
			new string(action.at(1)),
			new string(num.at(0)),
			new string(action.at(0)),
			new string(action.at(2)),
			new string(num.at(1))
		}
	) {/*Intentionally Empty*/
};

AndCard::AndCard(const AndCard& other) : Cards(other)
{/*Intentionally Empty*/
};

AndCard& AndCard::operator=(const AndCard& other)
{
	Cards::operator=(other);
	return *this;
};

AndCard::~AndCard()
{/*Intentionally Empty*/
};

// ############################################
//			OrCard
// ############################################
OrCard::OrCard() : Cards()
{/*Intentionally Empty*/
};

OrCard::OrCard(string good, vector<string> action, vector<string> num)
	: Cards(
		good,
		new vector<string*>{
			new string(action.at(1)),
			new string(num.at(0)),
			new string(action.at(0)),
			new string(action.at(2)),
			new string(num.at(1))
		}
	) {/*Intentionally Empty*/
};

OrCard::OrCard(const OrCard& other) : Cards(other)
{/*Intentionally Empty*/
};

OrCard& OrCard::operator=(const OrCard& other)
{
	Cards::operator=(other);
	return *this;
};

OrCard::~OrCard()
{/*Intentionally Empty*/
};

