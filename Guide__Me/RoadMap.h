#pragma once
#include<iostream>
#include<string>
#include<list>
#include<stack>
#include<unordered_set>
#include<unordered_map>
#include<set>
#include<cctype>
#include<sstream>
#include<vector>
#include<fstream>
using namespace std;


struct Transportation
{
	// data members
	
	string vechile="";
	double price=0.0;
	Transportation(string m, int p) : vechile(m), price(p) {}
};


class RoadMap
{

private:
	// datamembers
	//      key=> name of source & value=> vector (transporation(source,destination,cost))  

	unordered_map<string, vector <pair<string, vector<Transportation>>>> _map;
	vector<Transportation>vehicle;

public:
	// constructors

	RoadMap();  // read map
	int numOfLines; // FOR FILESTREAM

	// methods

	// WRITE YOUR METHODS HERE, THEN IMPLEMENT THEM IN .CPP FILE 

	void updateTransportation(const string& source, const string& destination, const string& vehicle, double newPrice);

	//bool isComplete();
	void addEdge(string src, string dest, string method, int price);
	void addTransportation(string src, string dest, string method, int price);
	void displayGraph();
	void Add();
	bool cityExists(string s);
	bool ignoreCaseInsensitive(string str1, string str2);
	string toLower(string s);

	void deleteTransportation(string source, string destination);

	// destructor

	//~RoadMap();

};

