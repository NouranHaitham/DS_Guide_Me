#include "RoadMap.h"

//RoadMap::RoadMap()
//{
//	/*
//	 4
//Cairo - Giza Metro 30 Bus 60 Uber 230
//Dahab - Giza Bus 500 Microbus 345
//Cairo - BeniSuef Microbus 20 Bus 15
//Asyut - Cairo Train 250 Bus 450 
//    */
//
//	/*
//	* 
//	* For printing the map if needed
//	*   
//	cout << map.size() << endl;
//   
//	for (unordered_map<string, vector <Tranporation>>::iterator start = map.begin(); start != map.end(); start++)
//	{
//		cout << start->first << endl;
//
//		for (int i = 0; i < start->second.size(); i++)
//		{
//			cout << start->second[i].destination << " " << start->second[i].vechile << " "
//				<< start->second[i].price << "// ";
//		}
//		cout << endl;
//
//	}
//  */ 
//}

RoadMap::RoadMap(){
// original map
addEdge("Asyut", "Cairo", "Trian", 250);
addEdge("Asyut", "Cairo", "Bus", 450);
addEdge("Cairo", "BeniSuef", "Microbus", 20);
addEdge("Cairo", "BeniSuef", "Bus", 15);
addEdge("BeniSuef", "Dahab", "Microbus", 200);
addEdge("BeniSuef", "Dahab", "Bus", 315);
addEdge("Dahab", "Giza", "Bus", 500);
addEdge("Dahab", "Giza", "Microbus", 345);
addEdge("Giza", "Cairo", "Metro", 30);
addEdge("Giza", "Cairo", "Bus", 60);
addEdge("Giza", "Cairo", "Uber", 230);

}


void RoadMap::addEdge(string src, string dest, string method, int price) {
    // undirected graph
    vector<Transportation> transVector;
    transVector.push_back(Transportation(method, price));
    adjList[src].push_back(make_pair(dest, transVector));
    adjList[dest].push_back(make_pair(src, transVector));
}

void RoadMap::addTransportation(string src, string dest, string method, int price) {
    for (auto& pair : adjList[src]) { // checks if the edge already exists
        if (ignoreCaseInsensitive(pair.first, dest)) { // checks if the dest entered by the user exists
            for (auto& transPair : pair.second) {
                if (ignoreCaseInsensitive(transPair.vehicle, method)) { // checks if the method exits
                    cout << "Transportation already exists!\n";
                    return;
                }
            }
        }
    }
    addEdge(src, dest, method, price); // If the edge doesn't exist -> add new edge
    cout << "New Transportation has been added!\n";
}

void RoadMap::displayGraph() {
    unordered_map<string, vector<pair<string, vector<Transportation>>>>::iterator it;
    cout << "Main map: \n";
    for (it = adjList.begin(); it != adjList.end(); ++it) {
        cout << "City: " << it->first << " -> \n";
        for (auto& pair : it->second) {
            cout << pair.first << " [";
            for (auto& trans : pair.second) {
                cout << "(" << trans.vehicle << ", " << trans.price << ")";
            }
            cout << "] ";
        }
        cout << endl;
        cout << endl;
    }
}

void RoadMap::Add() {
    displayGraph();
    //cout << adjList.size();

    string c = "";
    do {
        string src, dest, trans;
        int price;

        cout << "Enter the source city: ";
        getline(cin, src);

        cout << "Enter the destination city: ";
        getline(cin, dest);

        if (cityExists(toLower(src)) && cityExists(toLower(dest))) {
            cout << "Enter the transportation method: ";
            getline(cin, trans);

            cout << "Enter the price: ";
            cin >> price;

            /*addTransportation(graph, &src, &dest, &trans, &price);*/
            addTransportation(src, dest, trans, price);
            displayGraph();
        }

        else {
            cout << "The city does not exist in the list.\n";
        }

        cout << "Do you want to add a new transportation? \n";
        cin >> c;
        cin.ignore(); // prevents a new line encounter

    } while (c == "y" || c == "Y");
}

bool RoadMap::cityExists(string s) {
    vector<string> cities = { "Asyut", "Cairo", "BeniSuef", "Dahab", "Giza" };  // List of cities

    for (char& c : s) {
        c = tolower(c);
    }

    for (string& city : cities) {
        for (char& c : city) {
            c = tolower(c);
        }

        if (city == s) {
            return true; // City exists
        }
    }
}

bool RoadMap::ignoreCaseInsensitive(string str1, string str2) { // compares two strings
    if (str1.length() != str2.length()) {
        return false; // If lengths are different, strings are not equal
    }

    for (int i = 0; i < str1.length() && i < str2.length(); ++i) { // check for other string1 length and string2 length
        if (tolower(str1[i]) != tolower(str2[i])) {
            return false; // If characters are different, strings are not equal
        }
    }

    return true; // Strings are equal
}

string RoadMap::toLower(string s) {
    string result = s;

    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}


//RoadMap::~RoadMap()
//{
///*
//	fstream file;
//	file.open("Input.txt", ios::out);
//
//	file << numOfLines << endl;
//
//	set<pair<string, string>> isPrinted;
//
//
//	for (unordered_map<string, vector <Tranporation>>::iterator start = map.begin(); start != map.end(); start++)
//	{
//
////		file << start->first << " - ";   //source - //
//		
//		for (unordered_map<string, vector <Tranporation>>::iterator dest = map.begin(); dest != map.end(); dest++)
//		{
//            bool hasEdge = false;
//			for (int i = 0; i < start->second.size(); i++)
//			{
//				
//				if (isPrinted.find({dest->first,start->first}) != isPrinted.end())
//				{
//					break;
//				}
//			
//				if (start->second[i].destination == dest->first) {
//					
//					if (!hasEdge)
//					{
//						file << start->first << " - "<< dest->first; // destination
//						isPrinted.insert({start->first ,dest->first});
//						hasEdge = 1;
//					}
//
//					file <<" "<<start->second[i].vechile << " " << start->second[i].price;
//				}
//			
//			}
//
//			if(hasEdge) file << endl;
//		}
//
//	}
//
//	file.close();
//*/
//}


