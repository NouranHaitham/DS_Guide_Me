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

RoadMap::RoadMap() {
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


void RoadMap::updateTransportation(const string& source, const string& destination, const string& vehicle, double newPrice) {
    // Check if the source exists in the map
    auto sourceIter = _map.find(source);
    if (sourceIter == _map.end()) {
        cout << "Source city not found in the map." << endl;
        return;
    }

    // Find the transportation options for the specified destination from the source
    auto& destinations = sourceIter->second;
    for (auto& destinationPair : destinations) {
        if (destinationPair.first == destination) {
            // Search for the transportation option with the given vehicle
            for (auto& transport : destinationPair.second) {
                if (transport.vehicle == vehicle) {
                    // Update the price of the transportation option
                    transport.price = newPrice;
                    cout << "Transportation price updated successfully." << endl;
                    return;
                }
            }
            cout << "Transportation vehicle not found for the given source and destination." << endl;
            return;
        }
    }

    cout << "Destination city not found for the given source." << endl;
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
