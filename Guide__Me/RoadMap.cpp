#include "RoadMap.h"
using namespace std;
//////////////////////////////////////////////
RoadMap::RoadMap()
{
    /*
5
Cairo - Giza Metro 30 Bus 60 Uber 230
Dahab - Giza Bus 500 Microbus 345
Cairo - BeniSuef Microbus 20 Bus 15
Asyut - Cairo Train 250 Bus 450
Dahab - BeniSuef Microbus 200 Bus 315

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

        while (getline(iss, t.vehicle, ' ')) {

            getline(iss, strPrice, ' ');
            t.price = stod(strPrice);

            trans.push_back(t);

        }

        // finally we add it.
        map[source].push_back({ destination,trans });
        map[destination].push_back({ source,trans });

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

    for (unordered_map<string, vector <pair<string, vector<Transportation>>>>::iterator start = map.begin(); start != map.end(); start++)
    {

        //		file << start->first << " - ";   //source - //

        for (unordered_map<string, vector <pair<string, vector<Transportation>>>>::iterator dest = map.begin(); dest != map.end(); dest++)
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

                        file << " " << start->second[i].second[j].vehicle << " " << start->second[i].second[j].price;

                    }
                    file << endl;
                    break;

                }

            }
        }
    }
    file.close();
}
/////////////////////////////////////////////

void RoadMap::addEdge(string src, string dest, string method, int price) {
    // undirected graph
    vector<Transportation> transVector;
    transVector.push_back(Transportation(method, price));
    map[src].push_back(make_pair(dest, transVector));
    map[dest].push_back(make_pair(src, transVector));
}
void RoadMap::addTransportation(string src, string dest, string method, int price) {
    for (auto& pair : map[src]) { // checks if the edge already exists
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
void RoadMap::displayGraph() {
    unordered_map<string, vector<pair<string, vector<Transportation>>>>::iterator it;
    cout << "Main map: \n";
    for (it = map.begin(); it != map.end(); ++it) {
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
string RoadMap::toLower(string s) {
    string result = s;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}
////////////////////////////////////////////////


void RoadMap::updateTransportation(const string& source, const string& destination, const string& vehicle, double newPrice) {
    // Check if the source exists in the map
    auto sourceIter = map.find(source);
    if (sourceIter == map.end()) {
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

/////////////////////////////////////////////////
void RoadMap::deleteTransportation(string source, string destination)
{
    string transport = "";
    while (true)
    {
        // Display all edges
        auto sourceCity = map.find(source);
        if (sourceCity != map.end())
        {
            for (auto& desCity : sourceCity->second)
            {
                if (desCity.first == destination && !desCity.second.empty())
                {
                    for (auto trans = desCity.second.begin(); trans != desCity.second.end(); trans++)
                    {
                        cout << "Edge from " << source << " to " << destination << " : vehicle = " << trans->vehicle << " : price = " << trans->price << endl;
                    }
                }
            }

            cout << "Choose one Transportation to Delete or enter 'q' to quit:- " << endl;
            cin >> transport;

            if (transport == "q") return;

            // Delete the edge from the source node
            for (auto& desCity : sourceCity->second)
            {
                if (desCity.first == destination)
                {
                    for (auto trans = desCity.second.begin(); trans != desCity.second.end(); trans++)
                    {
                        if (trans->vehicle == transport)
                        {
                            desCity.second.erase(trans);
                            break;
                        }
                    }

                }
            }

            // Delete the edge from the destination node
            sourceCity = map.find(destination);
            if (sourceCity != map.end())
            {
                for (auto& desCity : sourceCity->second)
                {
                    if (desCity.first == source)
                    {
                        for (auto trans = desCity.second.begin(); trans != desCity.second.end(); trans++)
                        {
                            if (trans->vehicle == transport)
                            {
                                desCity.second.erase(trans);
                                break;
                            }

                        }
                    }
                }
            }
        }
        else
        {
            cout << "There is no city with this name " << endl;
            break;
        }
    }
}
////////////////////////////////////////////////
bool RoadMap::isComplete()
{
    stack<string> explore;
    unordered_set<string> visited;

    explore.push(map.begin()->first);

    while (!explore.empty())
    {

        string curr_city = explore.top();
        explore.pop();

        if (visited.find(curr_city) == visited.end()) {

            visited.insert(curr_city);

            //cout << curr_city << endl;

            for (vector <pair<string, vector<Transportation>>>::iterator start = map[curr_city].begin(); start != map[curr_city].end(); start++)
            {
                if ((visited.find(start->first) == visited.end()) && (start->second.size() != 0))
                {
                    explore.push(start->first);
                }

            }
        }
    }

    //cout << visited.size() << endl;


    return (map.size() == visited.size());

}

////////////////////////////////////////////////

void RoadMap::ClearElqueue(queue<pair<string, string>>& path)
{
    while (!path.empty())  path.pop();
}

void RoadMap::ALLAVALIABLEPATHS(string node, double cost)
{
    vis[node] = 1;
    for (auto child : map[node])
    {
        if (!vis[child.first])
        {
            if (child.first != destination) /// node ---child
            {
                for (auto V : child.second)
                {
                    if (cost + V.price < targetmoney)
                    {
                        path.push({ child.first,V.vehicle });
                        ALLAVALIABLEPATHS(child.first, cost + V.price);
                    }
                }
            }
            else
            {
                for (auto V : child.second)
                {
                    if (cost + V.price <= targetmoney)
                    {
                        path.push({ child.first,V.vehicle });
                        routs.push_back({ cost + V.price ,path });
                    }
                }
            }
        }
    }
    ClearElqueue(path);
}

void RoadMap::outputofpaths()
{
    cout << "enter your source:  "; cin >> source;
    cout << "enter your desination:  "; cin >> destination;
    cout << "enter your targetmoney: "; cin >> targetmoney;

    ALLAVALIABLEPATHS(source, 0);
    sort(routs.begin(), routs.end());

    for (auto r : routs)
    {
        cout << source << " ";
        while (!r.second.empty()) // what was the wrong
        {
            cout << "(" << " " << r.second.front().second << " " << ")" << " ";
            cout << r.second.front().first << " ";
            r.second.pop();
        }
        cout << r.first << endl;
    }

}

//dfs algo
void RoadMap::dfs(string v) {
    vis.clear();
    s.push(v);
    while (!s.empty()) {
        string current = s.top();
        s.pop();
        if (!vis[current]) {

            vis[current] = true;
            dfsoutr.push(current);
            //loops on the neigbors of the node 
            for (auto it = map[current].begin(); it != map[current].end(); it++) {

                if (!vis[it->first]) {
                    s.push(it->first);

                }
            }
        }
    }
    while (!dfsoutr.empty()) {
        cout << dfsoutr.front() << endl;
        dfsoutr.pop();
    }
}

//bfs algo
void RoadMap::bfs(string v) {
    //uses queue to pop from first as it wants to pop the neighbor of the first node
    vis.clear();
    bfs_queue.push(v);
    while (!bfs_queue.empty()) {
        string current = bfs_queue.front();
        bfs_queue.pop();
        if (!vis[current]) {
            vis[current] = true;
            bfsout.push(current);
            for (auto it = map[current].begin(); it != map[current].end(); it++) {
                if (!vis[it->first]) {
                    bfs_queue.push(it->first);
                }

            }
        }
    }
    while (!bfsout.empty()) {
        cout << bfsout.front() << endl;
        bfsout.pop();
    }

}


//void RoadMap::adjlist() {
//    for (auto& lis : _map) {
//        string source = lis.first;
//        for (auto& dist : lis.second) {
//            string distination = dist.first;
//
//            adjList[source].push_back(distination);
//            adjList[distination].push_back(source);
//
//
//        }
//
//    }
//}
