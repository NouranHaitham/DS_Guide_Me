#include "RoadMap.h"
#include<QMessageBox>


////////////////////////////////////////////////////////
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

    string line;

    while (getline(file, line))
    {
        string source, destination, strPrice;
        istringstream iss(line);

        //cout << line << " " << num << endl;

        getline(iss, source, ' ');  // Read source

        getline(iss, line, ' ');  // to pass '-'


        getline(iss, destination, ' '); // Read destination


        // now we read the list of transportations && push 

        vector<Transportation> trans;
        Transportation t;

        while (getline(iss, t.vehicle, ' ')) {

            getline(iss, strPrice, ' ');
            t.price = stod(strPrice);

            trans.push_back(t);

        }

        // finally we add it [undirected graph]
        map[source].insert({ destination,trans });
        map[destination].insert({ source,trans });

    }


    //For printing the map if needed

    cout << map.size() << endl;

    for (unordered_map<string, unordered_map<string, vector<Transportation>>>::iterator source = map.begin(); source != map.end(); source++)
    {
        cout << source->first << endl;
        for (unordered_map<string, vector<Transportation>>::iterator dest = source->second.begin(); dest != source->second.end(); dest++)
        {
            cout << dest->first << " ";

            for (int j = 0; j < dest->second.size(); j++) {

                cout << dest->second[j].vehicle << " " << dest->second[j].price << "  ";
            }

            cout << endl;
        }
        cout << endl;
    }


    file.close();
}

RoadMap::~RoadMap()
{

    fstream file;
    file.open("Input.txt", ios::out);


    file << map.size() << endl;

    set<pair<string, string>> isPrinted;


    for (auto source = map.begin(); source != map.end(); source++)
    {

        for (auto dest = map.begin(); dest != map.end(); dest++)
        {

            for (auto sourceDestin : source->second)
            {

                if (isPrinted.find({ dest->first,source->first }) != isPrinted.end())
                {
                    break;
                }

                if (sourceDestin.first == dest->first)
                {

                    file << source->first << " - " << dest->first;

                    isPrinted.insert({ source->first ,dest->first });

                    for (int j = 0; j < sourceDestin.second.size(); j++)
                    {

                        file << " " << sourceDestin.second[j].vehicle << " " << sourceDestin.second[j].price;

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

// unordered_map<string, unordered_map<string, vector<Transportation>>> map;

void RoadMap::addEdge(string src, string dest, string method, double price) {

    // undirected graph
    auto& destinations = map[src];
    auto destExit = destinations.find(dest);
    if (destExit == destinations.end()) {
        vector<Transportation> transVector;
        transVector.push_back(Transportation(method, price));
        map[src].insert(make_pair(dest, transVector));
    }
    else {
        map[src][dest].push_back(Transportation(method, price));
    }

}

void RoadMap::addTransportation(string src, string dest, string method, double price) {
    auto sourceCity = map.find(src);
    auto destinationCity = map.find(dest);

    // Check if source and destination cities exist
    if (sourceCity == map.end()) {
        QMessageBox::information(nullptr, "Warning", "Source city is not found in the map!");
        return;
    }

    // Check if transportation already exists in both directions
    bool existsForward = transportationExists(src, dest,method);
    bool existsBackward = transportationExists(dest, src, method);

    // If the transportation already exists in both directions
    if (existsForward && existsBackward) {
        QMessageBox::information(nullptr, "Warning", "Transportation already exists!");
        return;
    }

    // Add transportation for both directions if it doesn't exist
    if (!existsForward) {
        addEdge(src, dest, method, price);
    }
    if (!existsBackward) {
        addEdge(dest, src, method, price);
    }

    QMessageBox::information(nullptr, "Information", "New transportation has been added!");
}

bool RoadMap::transportationExists(string src, string dest, string method) {
    auto it = map.find(src);
    if (it == map.end()) { // checks if src exists in the map 
        return false;
    }

    // checks if destination exits in the destination of the source
    auto& destinations = it->second;
    auto destExit = destinations.find(dest);
    if (destExit == destinations.end()) {
        return false;
    }

    // checks if the method exists in the transportation list
    for (auto& transPair : destExit->second) {
        if (compare(transPair.vehicle, method)) {
            return true;
        }
    }

    return false;
}

bool RoadMap::compare(string str1, string str2) { // compares two strings
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

string RoadMap::toLower(string s) 
{
    string result = s;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}

/*
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
*/

//////////////////////////////////////////////

void RoadMap::updateTransportation(const string& source, const string& destination, const string& vehicle, double newPrice) {
   
    // Check if both the source and destination exist in the map
    auto sourceIter = map.find(source);
    if (sourceIter == map.end()) 
    {
       // cout << "Source or destination city not found in the map." << endl;
        QMessageBox::information(nullptr, "Information", "Source city doesn't exist!");
        return;
    }

    auto destIter = map[source].find(destination);
    if (destIter == map[source].end() && destIter->second.size() != 0)
    {
        // cout << "Source or destination city not found in the map." << endl;
        QMessageBox::information(nullptr, "Information", "There is no transportation between source and destination!");
        return;
    }

    // Find the transportation options for the specified destination from the source
    auto& destMap = sourceIter->second; // second map
    auto& transVector = destIter->second; // vector of transportation

    // Update the price from source to destination
    bool transExist = false;
 
    // Search for the transportation option with the given vehicle
    for (auto& transport : transVector)
    {
        if (transport.vehicle == vehicle) {
            // Update the price of the transportation option
            transport.price = newPrice;
            // cout << "Transportation price updated successfully from " << source << " to " << destination << "." << endl;
            QMessageBox::information(nullptr, "Information", "Transportation price updated successfully !");
            transExist = true;
            break;
        }
    }
    if (!transExist)
    {
      //  cout << "Destination city not found for the given source." << endl;
        QMessageBox::information(nullptr, "Information", "Transportation doesn't exist!");
        return;
    }

    // Update the price from destination to source
    // Search for the transportation option with the given vehicle

    for (auto& transport : map[destination][source])
    {
        if (transport.vehicle == vehicle)
        {
            // Update the price of the transportation option
            transport.price = newPrice;
            cout << "Transportation price updated successfully from " << destination << " to " << source << "." << endl;
            break;
        }
    } 
}

/////////////////////////////////////////////////
void RoadMap::deleteTransportation(string source, string destination, string transport)
{
    auto sourceIter = map.find(source);
    if (sourceIter == map.end())
    {
        // cout << "Source or destination city not found in the map." << endl;
        QMessageBox::information(nullptr, "Information", "Source city doesn't exist!");
        return;
    }

    auto destIter = map[source].find(destination);
    if (destIter == map[source].end() || (destIter != map[source].end() && destIter->second.size() == 0))
    {
        // cout << "Source or destination city not found in the map." << endl;
        QMessageBox::information(nullptr, "Information", "There is no transportation between source and destination!");
        return;
    }

    bool transExist = false;
    auto sourceCity = map.find(source);
  
    // Delete the edge from the source node
    auto desCity = sourceCity->second.find(destination);
    for (auto trans = desCity->second.begin(); trans != desCity->second.end(); trans++) {
        if (trans->vehicle == transport) {
            desCity->second.erase(trans);
            transExist = true;
            break;
        }
    }
   
    // Delete the edge from the destination node

    desCity = map[destination].find(source);
    for (auto trans = desCity->second.begin(); trans != desCity->second.end(); trans++) {
        if (trans->vehicle == transport) {
            desCity->second.erase(trans);
            transExist = true;
            break;
        }
    }
    
     
    if (!transExist) {
        QMessageBox::information(nullptr, "Information", "The Transportation doesn't exist!");
    }
    else {
        QMessageBox::information(nullptr, "Information", "The Transportation has been deleted successfully !");
    }
}

/////////////////////////////////////////////////////////////////
void RoadMap::isComplete()
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

            for (unordered_map <string, vector<Transportation>>::iterator start = map[curr_city].begin(); start != map[curr_city].end(); start++)
            {
                if ((visited.find(start->first) == visited.end()) && (start->second.size() != 0))
                {
                    explore.push(start->first);
                }

            }
        }
    }

    //cout << visited.size() << endl;

    if (map.size() == visited.size())
        QMessageBox::information(nullptr, "Connection", "The map is Connected! 〜(￣▽￣〜)");
    else
        QMessageBox::information(nullptr, "Connection", "The map is NOT Connected! ┑(￣Д ￣)┍");
}

///////////////////////////////////////////////////////////////////////////////////////
//
void RoadMap::ALLAVALIABLEPATHS(string node, double cost) {

    if (node == destination) /// node ---child
    {
        if (cost <= targetmoney)
          routs.emplace(cost, path);
        return;
    }
    for (auto child : map[node]) {

        if (child.first == source)
            continue;
        
        for (auto V : child.second) 
        {
            if (!vis[child.first])
            {

                path.emplace_back(child.first, V.vehicle);
                vis[child.first] = 1;
                
                ALLAVALIABLEPATHS(child.first, cost + V.price);
                
                path.pop_back();
                vis[child.first] = 0;


            }
        }
    }
}

QString RoadMap::outputofpaths(string src, string des, double t)
{
    vis.clear();
    routs.clear();
    path.clear();

    source = src;
    destination = des;
    targetmoney = t;

    ALLAVALIABLEPATHS(source, 0);
    //sort(routs.begin(), routs.end());

    if (routs.empty())
        QMessageBox::information(nullptr, "Paths", "There are no suitable paths to the target destination with your current budget! ┑(￣Д ￣)┍");

    QString text;

    for (auto rout : routs) {
        text.append(source).append(" ");
        for (auto r : rout.second)
        {
            text.append("( ").append(r.second).append(" ) ").append(r.first).append(" ");
        }
        text.append(QString::number(rout.first)).append("\n"); // price
    }
    return text;
}

//////////////////////////////////////////////////////////////////////////////
 
//dfs algo
QString RoadMap::dfs(string v) {

    if (map.find(v) == map.end())
    {
        QMessageBox::information(nullptr, "Alert", "The City doesn't exist!");
    }
    else
    {

        vis.clear();
        dfs_stack.push(v);
        while (!dfs_stack.empty()) {
            string current = dfs_stack.top();
            dfs_stack.pop();
            if (!vis[current]) {

                vis[current] = true;
                dfsout.push(current);
                //loops on the neigbors of the node 
                for (auto it = map[current].begin(); it != map[current].end(); it++) {

                    if (!vis[it->first] && it->second.size() != 0) {
                        dfs_stack.push(it->first);

                    }
                }
            }
        }
    }

    QString text="";
    while (!dfsout.empty()) {
        //cout << dfsoutr.front() << endl;
        text.append(dfsout.front()).append("\n");
        dfsout.pop();
    }

    return text;
}

//bfs algo
QString RoadMap::bfs(string v) {

    //uses queue to pop from first as it wants to pop the neighbor of the first node

    if (map.find(v) == map.end())
    {
        QMessageBox::information(nullptr, "Alert", "The City doesn't exist!");
    }
    else
    {
        vis.clear();
        bfs_queue.push(v);
        while (!bfs_queue.empty()) {
            string current = bfs_queue.front();
            bfs_queue.pop();
            if (!vis[current]) {
                vis[current] = true;
                bfsout.push(current);
                for (auto it = map[current].begin(); it != map[current].end(); it++) {
                    if (!vis[it->first] && it->second.size() != 0) {
                        bfs_queue.push(it->first);
                    }

                }
            }
        }

    }

    QString text="";
    while (!bfsout.empty()) {
        //cout << bfsout.front() << endl;
        text.append(bfsout.front()).append("\n");
        bfsout.pop();
    }


    return text;

}

/////////////////////////////////////////////////////////////////////

QString RoadMap::DisplayEdges(string source, string destination)
{ 
    QString text;
    auto sourceCity = map.find(source);
    if (sourceCity != map.end() && map[source].find(destination) != map[source].end())
    {
        for (auto& trans : map[source][destination])
        {
            text.append(trans.vehicle).append(" - ").append(QString::number(trans.price)).append("\n");
        }
    }
    else
    {
        QMessageBox::information(nullptr, "Alert", "The source city doesn't exist!");  
    }

    if(text=="") QMessageBox::information(nullptr, "Alert", "No Transportation between them!");
     
    return text;

}
