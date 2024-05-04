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

	fstream file;
	file.open("Input.txt", ios::in);

	int num; file >> num;
	file.ignore();

	numOfLines = num;

	while (num--)
	{
		string line, source, destination, strPrice;

		getline(file, line);       // read the whole line
		istringstream iss(line);

		//cout << line << " " << num << endl;

		getline(iss, source, ' ');  // read source

		getline(iss, line, ' ');  // to pass '-'


		getline(iss, destination, ' '); // read destination


		// now we read the list of transportations && push 

		vector<Transportation> trans;
		Transportation t;

		while (getline(iss, t.vechile, ' ')) {

			getline(iss, strPrice, ' ');
			t.price = stod(strPrice);

			trans.push_back(t);

		}

		// finally we add it.
		_map[source].push_back({ destination,trans });
		_map[destination].push_back({ source,trans });

	}



	/*
	//For printing the map if needed

	cout << _map.size() << endl;

	for (unordered_map<string, vector <pair<string, vector<Transportation>>>>::iterator start = _map.begin(); start != _map.end(); start++)
	{
		cout << start->first << endl;

		for (int i = 0; i < start->second.size(); i++)
		{
			cout << start->second[i].first << " ";

			for (int j = 0; j < start->second[i].second.size(); j++) {

				cout<< start->second[i].second[j].vechile << " "<< start->second[i].second[j].price<<"  ";
			}

			cout << endl;
		}

		cout<< endl;

	}

  */
	file.close();
}


RoadMap::~RoadMap()
{

	fstream file;
	file.open("Input.txt", ios::out);

	file << numOfLines << endl;

	set<pair<string, string>> isPrinted;


	for (unordered_map<string, vector <pair<string, vector<Transportation>>>>::iterator start = _map.begin(); start != _map.end(); start++)
	{

		//		file << start->first << " - ";   //source - //

		for (unordered_map<string, vector <pair<string, vector<Transportation>>>>::iterator dest = _map.begin(); dest != _map.end(); dest++)
		{

			for (int i = 0; i < start->second.size(); i++)
			{

				if (isPrinted.find({ dest->first,start->first }) != isPrinted.end())
				{
					break;
				}

				if (start->second[i].first == dest->first) {

					file << start->first << " - " << dest->first; // destination

					isPrinted.insert({ start->first ,dest->first });

					for (int j = 0; j < start->second[i].second.size(); j++) {

						file << " " << start->second[i].second[j].vechile << " " << start->second[i].second[j].price;

					}
					file << endl;
					break;

				}

			}


		}

	}

	file.close();
}



bool RoadMap::isComplete()
{
	stack<string> explore;
	unordered_set<string> visited;

	explore.push(_map.begin()->first);

	while (!explore.empty())
	{

		string curr_city = explore.top();
		explore.pop();

		if (visited.find(curr_city) == visited.end()) {

			visited.insert(curr_city);

			//cout << curr_city << endl;

			for (vector <pair<string, vector<Transportation>>>::iterator start = _map[curr_city].begin(); start != _map[curr_city].end(); start++)
			{
				if (visited.find(start->first) == visited.end())
				{
					explore.push(start->first);
				}

			}
		}
	}

	//cout << visited.size() << endl;


	return (_map.size() == visited.size());

}
