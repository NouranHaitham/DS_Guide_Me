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
	deque<pair<string, string>>path;
	vector<pair<double, queue<pair<string, string>>>>routs;

	//dfs
	stack<string> dfs_stack;
	queue<string> dfsout;
	//bfs
	queue<string> bfs_queue;
	queue<string> bfsout;


public:

	//   key=> name of source & value=> vector (transporation(source,destination,cost))  
	unordered_map<string, vector <pair<string, vector<Transportation>>>> map;

	// constructors

	RoadMap();  // Read map (Filestream)

	// methods
	void updateTransportation(const string& source, const string& destination, const string& vehicle, double newPrice);

	void isComplete();

	void addEdge(string src, string dest, string method, double price);
	void addTransportation(string src, string dest, string method, double price);
	bool ignoreCaseInsensitive(string str1, string str2);
	string toLower(string s);
	
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
