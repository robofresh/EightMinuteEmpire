#include "MapLoader.h"
#include "Map.h"
#include <fstream>

void processFile(ifstream*);

int main()
{
	ifstream *mapFile = new ifstream("map1.json");

	if (mapFile->is_open())
	{
		processFile(mapFile);
	}
	else { cout << "no file found" << endl; }
}




void processFile(ifstream* mapFile)
{

	vector<string>* fileContinents = new vector<string>;
	vector<string>* fileCountries = new vector<string>;

	string fileString((std::istreambuf_iterator<char>(*mapFile)), (std::istreambuf_iterator<char>()));
	cout << fileString;



	/*while (getline(mapfile, line))
{
	cout << line << '\n';
	}*/

	mapFile->close();

}