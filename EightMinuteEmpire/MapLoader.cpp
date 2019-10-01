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

	vector<string>* fileContinents = new vector<string>;
	vector<string>* fileCountries = new vector<string>;

	//string fileString((std::istreambuf_iterator<char>(*mapFile)), (std::istreambuf_iterator<char>()));
	//cout << fileString;

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

					cont = map->createContinent(*fileString);
					createdCont = true;
					//cout << "new continent: " << *fileString << endl;
					continue;
				}


				if (fileString->at(0) == '\t' && fileString->at(1) == '\t' && createdCont)
				{
					cleanString(fileString);

					Country *country = map->createCountry(*fileString, cont);
					cont->containedCountries->push_back(country);

					//cout << "\t" << "new country: " << *fileString << endl;
					continue;
				}


			}
		}

		if (string("Connections").compare(*fileString) == 0)
		{
			while (getline(*mapFile, *fileString, '\n'))
			{
				if (fileString->length() == 1 || fileString->length() == 0)
					continue;

				if (fileString->at(0) != '\t')
					break;

				if (fileString->at(0) == '\t' && fileString->at(1) == '\t')
				{
					cleanString(fileString);
					//cout << *fileString << endl;

					continue;
				}

				if (fileString->at(0) == '\t')
				{
					cleanString(fileString);
					//cout << *fileString << " connects with: " << endl;

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
	for (int i = 0; i < str->length(); i++)
	{
		if (str->at(i) == '\t' || str->at(i) == '\n')
		{
			str->erase(i, 1);
		}
	}
}

MapLoader::~MapLoader()
{
}
