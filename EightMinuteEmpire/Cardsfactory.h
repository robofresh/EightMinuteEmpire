#pragma once
#include "cards.h"

class Cardsfactory {
public:
	static Cards* Create(string, vector<string>, vector<string>);
private:
	Cardsfactory();
};

class SingleActionCard : public Cards {
public:
	SingleActionCard();
	SingleActionCard(string good, vector<string> action, vector<string> num);
	SingleActionCard(const SingleActionCard&);
	SingleActionCard& operator=(const SingleActionCard&);
	~SingleActionCard();
};

class MultiActionCard : public Cards {
public:
	MultiActionCard();
	MultiActionCard(string good, vector<string> action, vector<string> num);
	MultiActionCard(const MultiActionCard&);
	MultiActionCard& operator=(const MultiActionCard&);
	~MultiActionCard();
};