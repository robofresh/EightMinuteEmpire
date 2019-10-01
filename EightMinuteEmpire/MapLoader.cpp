#include "MapLoader.h"
#include "Map.h"

void cleanString(string*);
void processFile(ifstream*, Map*);


MapLoader::MapLoader(string file, Map* map)
{
	ifstream* mapFile = new ifstream(file);

	if (mapFile->is_open())
	{
		processFile(mapFile, map);
	}
	else { cout << "no file found" << endl; }
}

void processFile(ifstream* mapFile, Map* map)
{

	string* fileString = new string;

	while (getline(*mapFile, *fileString, '\n'))
	{
		if (fileString->length() == 1 || fileString->length() == 0)
			continue;

		cleanString(fileString);

		Continent* cont = nullptr;
		bool createdCont = false;

		if (string("Continents").compare(*fileString) == 0)
		{
			while (getline(*mapFile, *fileString, '\n'))
			{
				if (fileString->length() == 1 || fileString->length() == 0)
					continue;

				if (fileString->at(0) != '\t')
					break;


				if (fileString->at(0) == '\t' && fileString->at(1) != '\t')
				{
					cleanString(fileString);
					if (map->getContinent(*fileString) == nullptr)
					{
						cont = map->createContinent(*fileString);
						createdCont = true;
					}
					else
					{
						cout << '\"' << *fileString << '\"' << " already exists in the map; it will not be added again." << endl;
					}

					continue;

				}


				if (fileString->at(0) == '\t' && fileString->at(1) == '\t' && createdCont)
				{
					cleanString(fileString);

					if (map->getCountry(*fileString) == nullptr)
					{
						Country* country = map->createCountry(*fileString, cont);
						cont->containedCountries->push_back(country);
						country->parentContinent = cont;
					}
					else
					{
						cout << '\"' << *fileString << '\"' << " already exists in the map; it will not be added again." << endl;
					}

					continue;
				}
			}
		}

		Country* country = nullptr;
		bool insideCountry = false;


		if (string("Connections").compare(*fileString) == 0)
		{
			while (getline(*mapFile, *fileString, '\n'))
			{
				if (fileString->length() == 1 || fileString->length() == 0)
					continue;

				if (fileString->at(0) != '\t')
					break;


				if (fileString->at(0) == '\t' && fileString->at(1) != '\t')
				{
					cleanString(fileString);

					if (map->getCountry(*fileString) != nullptr)
					{
						insideCountry = true;
						country = map->getCountry(*fileString);
					}
					else
					{
						cout << '\"' << *fileString << '\"' << " does not exist as a country in the map." << endl;
					}
					continue;
				}

				if (fileString->at(0) == '\t' && fileString->at(1) == '\t' && insideCountry)
				{
					cleanString(fileString);

					if (map->getCountry(*fileString) != nullptr)
					{
						country->adjCountries->push_back(map->getCountry(*fileString));
					}
					else
					{
						cout << '\"' << *fileString << '\"' << " does not exist as a country in the map." << endl;
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
	if (str->length() == 0)
		return;

	//clean up line
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

MapLoader::~MapLoader()
{
}
