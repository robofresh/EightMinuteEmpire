#include "MapLoader.h"
#include "Map.h"

void cleanString(string*);
void processFile(ifstream*, Map*);
bool validateString(string*);

//to be used with the map1.map file

/*How the .map file is read:

There are two sections: "Continents" and "Connections".
Continents must come first as that is when the countries will be added to the map.
Connections is optional but must come after Continents or it will return an error.

Each tab and each new line is important as given in the example.
No tabs signifies the beginning of a new section.
One tab signifies and element in that section.
And two tabs will signify a sub element in that section.
In graph terms you could say two tabs in the “Continents” represents a node, and one tab represents the beginning of a subgraph.
And in the “Connections” section, you could say one tab represents a node in the graph, and two tabs represents the edges of a node.

E.g. as shown in the file two tabs, in "Continents" will mean the line should be a country inside an already stated continent.

*/

MapLoaderException::MapLoaderException() : message("")
{/*Intentionally Empty*/
}

MapLoaderException::MapLoaderException(string msg) : message(msg)
{/*Intentionally Empty*/}

MapLoaderException::~MapLoaderException()
{/*Intentionally Empty*/}

MapLoader::MapLoader()
{/*Intentionally Empty*/}

//map loader simply takes the file string and a map object pointer.
//this is to simplify the verification of the files existence and to not have a whole long file operation(s) in one large if statment
MapLoader::MapLoader(string file, Map* map)
{
	ifstream* mapFile = new ifstream(file);

	if (mapFile->is_open())
	{
		processFile(mapFile, map);
	}
	else { throw MapLoaderException("File not found."); }
}

//takes in a ifstream pointer and the map sent to the loader
void processFile(ifstream* mapFile, Map* map)
{

	string* fileString = new string;
	bool contOrder = false;

	//loop through each line
	while (getline(*mapFile, *fileString, '\n'))
	{
		//continue loop if the line is 0 or 1 characters long
		if (fileString->length() == 1 || fileString->length() == 0)
			continue;

		//clean up the string to minimize errors or confusion
		cleanString(fileString);

		Continent* cont = nullptr; // a reused pointer to the continent being created
		bool createdCont = false; //used to make sure the "Continent" section comes before the "Connections"

		//if the line matches "Continents"
		if (string("Continents").compare(*fileString) == 0)
		{
			//say that the section order is correct
			contOrder = true;

			//go through each line again
			while (getline(*mapFile, *fileString, '\n'))
			{
				if (fileString->length() == 1 || fileString->length() == 0)
					continue;

				//if the line does not have a tab as the first character, break out of this loop and continue the first loop
				if (fileString->at(0) != '\t')
					break;

				//if the first character is a tab and second characters isnt
				if (fileString->at(0) == '\t' && fileString->at(1) != '\t')
				{
					cleanString(fileString);

					if (!validateString(fileString))
						continue;

					//if the continent does not already exist in the map
					if (map->getContinent(*fileString) == nullptr)
					{
						cont = map->createContinent(*fileString);
						createdCont = true; //flag to track if a continent has been made in this loop
					}
					else
					{
						cout << '\"' << *fileString << '\"' << " already exists in the map; it will not be added again." << endl;
					}

					continue;
				}

				bool isStartCountry = false;

				//if the first and second characters are tabs (this means the string should be a country)
				if (fileString->at(0) == '\t' && fileString->at(1) == '\t' && createdCont)
				{
					cleanString(fileString);

					if (fileString->size() < 1)
						continue;

					if (fileString->at(0) == '*')
					{
						isStartCountry = true;
						fileString->erase(0, 1);
					}

					if (!validateString(fileString))
						continue;

					//if the country with said name doesnt exist in the map yet, add it and make its parent continent the continent from this loop
					if (map->getCountry(*fileString) == nullptr)
					{
						Country* country = map->createCountry(*fileString, cont);
						cont->containedCountries->push_back(country);
						country->parentContinent = cont;
						if (isStartCountry)
						{
							*country->isStartingCountry = true;
							map->startingCountry = country;
						}
					}
					else
					{
						cout << '\"' << *fileString << '\"' << " already exists in the map; it will not be added again." << endl;
					}

					continue;
				}
			}
		}

		Country* country = nullptr; //pointer to the loop's country
		bool insideCountry = false;

		//if this line says "Connections"
		if (string("Connections").compare(*fileString) == 0)
		{
			//if the file has put the sections in the wrong order
			if (!contOrder)
			{
				throw MapLoaderException("INVALID MAP: The map file is incorrectly formatted. Be sure \'Continents\' comes before \'Connections\'.");
				return;
			}

			//go through each line
			while (getline(*mapFile, *fileString, '\n'))
			{
				if (fileString->length() == 1 || fileString->length() == 0)
					continue;

				if (fileString->at(0) != '\t')
					break;

				//if the first character is a tab and second characters isnt (this means it should be a country)
				if (fileString->at(0) == '\t' && fileString->at(1) != '\t')
				{
					cleanString(fileString);

					if (!validateString(fileString))
						continue;

					//if the country is already in the map
					if (map->getCountry(*fileString) != nullptr)
					{
						insideCountry = true; // to check if we are making the connections of a country
						country = map->getCountry(*fileString);
					}
					else
					{
						throw MapLoaderException("INVALID MAP: \"" + *fileString + "\" does not exist as a country in the map.");
						return;
					}
					continue;
				}

				//if the first two characters are tabs and we are making the connections of a country
				if (fileString->at(0) == '\t' && fileString->at(1) == '\t' && insideCountry)
				{
					cleanString(fileString);

					if (!validateString(fileString))
						continue;

					//if the country is in the map
					if (map->getCountry(*fileString) != nullptr)
					{
						country->adjCountries->push_back(map->getCountry(*fileString));
					}
					else
					{
						throw MapLoaderException("INVALID MAP: \"" + *fileString + "\" does not exist as a country in the map.");
						return;
					}
					continue;
				}

			}
		}
	}

	mapFile->close();

}

void cleanString(string* str)
{
	//if the string has no characters
	if (str->length() == 0)
		return;

	//if the end of a string has a space
	if (str->back() == ' ')
	{
		str->pop_back();
	}

	//clean up line to get rid of tabs or new lines
	for (int i = 0; i < str->length(); )
	{
		if (str->at(i) == '\t' || str->at(i) == '\n')
		{
			str->erase(i, 1); 
			continue;
		}
		i++;
	}
}

bool validateString(string* str)
{
	//if the string doesnt just have alphabet characters, return false
	size_t found = str->find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
	if (found == string::npos)
	{
		return false;
	}
	return true;
}

MapLoader::~MapLoader()
{/*Intentionally Empty*/}
