#include "RoadMap.h"

RoadMap::RoadMap()
{
	/*
	 4
Cairo - Giza Metro 30 Bus 60 Uber 230
Dahab - Giza Bus 500 Microbus 345
Cairo - BeniSuef Microbus 20 Bus 15
Asyut - Cairo Train 250 Bus 450 
    */

	/*
	* 
	* For printing the map if needed
	*   
	cout << map.size() << endl;
   
	for (unordered_map<string, vector <Tranporation>>::iterator start = map.begin(); start != map.end(); start++)
	{
		cout << start->first << endl;

		for (int i = 0; i < start->second.size(); i++)
		{
			cout << start->second[i].destination << " " << start->second[i].vechile << " "
				<< start->second[i].price << "// ";
		}
		cout << endl;

	}
  */ 

	file.close();
}


RoadMap::~RoadMap()
{
/*
	fstream file;
	file.open("Input.txt", ios::out);

	file << numOfLines << endl;

	set<pair<string, string>> isPrinted;


	for (unordered_map<string, vector <Tranporation>>::iterator start = map.begin(); start != map.end(); start++)
	{

//		file << start->first << " - ";   //source - //
		
		for (unordered_map<string, vector <Tranporation>>::iterator dest = map.begin(); dest != map.end(); dest++)
		{
            bool hasEdge = false;
			for (int i = 0; i < start->second.size(); i++)
			{
				
				if (isPrinted.find({dest->first,start->first}) != isPrinted.end())
				{
					break;
				}
			
				if (start->second[i].destination == dest->first) {
					
					if (!hasEdge)
					{
						file << start->first << " - "<< dest->first; // destination
						isPrinted.insert({start->first ,dest->first});
						hasEdge = 1;
					}

					file <<" "<<start->second[i].vechile << " " << start->second[i].price;
				}
			
			}

			if(hasEdge) file << endl;
		}

	}

	file.close();
*/
}


