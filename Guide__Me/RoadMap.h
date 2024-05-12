#pragma once
#include<iostream>
#include<string>
#include<list>
#include<stack>
#include<unordered_set>
#include<unordered_map>
#include<set>
#include<queue>
#include<cctype>
#include<sstream>
#include<vector>
#include<fstream>
#include<QString>
using namespace std;


struct Transportation
{
	// data members
	string vehicle = "";
	double price = 0.0;
	Transportation(string m, double p) : vehicle(m), price(p) {}
	Transportation() {}
};


class RoadMap
{

private:

	// datamembers

	vector<Transportation>vehicle;

	string source, destination;
	double targetmoney;

	unordered_map<string, bool>vis;
	vector<pair<string, string>>path;
	set<pair<double, vector<pair<string, string>>>>routs;

	//dfs
	stack<string> dfs_stack;
	queue<string> dfsout;
	//bfs
	queue<string> bfs_queue;
	queue<string> bfsout;


public:

	//   key=> name of source & value=> vector (transporation(source,destination,cost))  
	unordered_map<string, unordered_map<string, vector<Transportation>>> map;

	// constructors

	RoadMap();  // Read map (Filestream)

	// methods
	void updateTransportation(string source, string destination, string vehicle, double newPrice);

	void isComplete();

	void addEdge(string src, string dest, string method, double price);
	void addTransportation(string src, string dest, string method, double price);
	bool transportationExists(string src, string dest, string method);
	
	//void displayGraph();
	//bool cityExists(string s);

	void deleteTransportation(string source, string destination, string transport);

	void ALLAVALIABLEPATHS(string node, double cost);
	QString outputofpaths(string source, string destination, double targetmoney);

	QString DisplayEdges(string source, string destination);

	QString dfs(string str);
	QString bfs(string str);

	// destructor
	~RoadMap(); // Save map (Filestream)

};
