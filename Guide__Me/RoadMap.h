#pragma once
#include<string>
#include<list>
#include<stack>
#include<unordered_set>
#include<unordered_map>
#include<set>
#include<iostream>
#include<sstream>
#include<fstream>
using namespace std;

struct Transportation 
{
	// data members
	string vechile="";
	double price=0.0;
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

	bool isComplete();

	// destructor

	~RoadMap();

};

