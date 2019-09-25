#include <iostream>
#include "Map.h"


//still dont know what the assignment means by subgraph
//dont know what "testing for valid/invalid maps" means, surely that goes in the map loader

int main()
{
	//input will take all countries, continents, adjacecnt countries etc.
	
	//will make a vector of country pointers and have that pointed to by map
	//will make a vector of countries' adjacent countries and have each country point to their own
	//will make a vector of countries in each continent and point to that in each contitnent


	Map *map = new Map(); // make a map object


	//simulate input...
	for (int i = 0; i < 10; i++)
	{
		Continent* cont = new Continent("Contitnent " + to_string(i/2), map);
		Country* country = new Country("Country " + to_string(i), cont, map);
	}

	for (int i = 0; i < map->mapCountries->size(); i++)
	{
		cout << map->mapCountries->at(i)->name->c_str() << endl;
	}


	for (int i = 0; i < map->mapContinents->size(); i++)
	{
		cout << map->mapContinents->at(i)->name->c_str() << endl;
	}


	//cout << map->mapCountries->at(0)->name->c_str() << endl; //print string from a coutry via map


}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file