#include "cards.h"
#include "Cardsfactory.h"

Cards* Cardsfactory::Create(string good, vector<string> type, vector<string> num) {
	if (type.at(0) == "OR" || type.at(0) == "AND") {
		cout << "In Cardsfactory, creating new MultiActionCard (card with an '" << type.at(0) << "' action and a " << good << " good)."  << endl;
		return new MultiActionCard(good, type, num);
	}
	else {
		cout << "In Cardsfactory, creating new SingleActionCard (card with a '" << type.at(0) << "' action and a " << good << " good)." << endl;
		return new SingleActionCard(good, type, num);
	}
}

SingleActionCard::SingleActionCard() : Cards()
{/*Intentionally Empty*/ };

SingleActionCard::SingleActionCard(string good, vector<string> action, vector<string> num)
	: Cards(
		good,
		new vector<string*>{
			new string(action.at(0)), new string(num.at(0))
		}
	) {/*Intentionally Empty*/
};

SingleActionCard::SingleActionCard(const SingleActionCard& other) : Cards(other)
{/*Intentionally Empty*/};

SingleActionCard& SingleActionCard::operator=(const SingleActionCard& other)
{
	Cards::operator=(other);
	return *this;
};

SingleActionCard::~SingleActionCard()
{/*Intentionally Empty*/};

MultiActionCard::MultiActionCard() : Cards()
{/*Intentionally Empty*/ };

MultiActionCard::MultiActionCard(string good, vector<string> action, vector<string> num)
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

MultiActionCard::MultiActionCard(const MultiActionCard& other) : Cards(other)
{/*Intentionally Empty*/
};

MultiActionCard& MultiActionCard::operator=(const MultiActionCard& other)
{
	Cards::operator=(other);
	return *this;
};

MultiActionCard::~MultiActionCard()
{/*Intentionally Empty*/
};

