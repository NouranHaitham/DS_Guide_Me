#include "RoadMap.h"
#include <QMessageBox>
#include <QString>

#include<iostream>
#include <sstream>
#include<string>
#include<list>
#include<stack>
#include<unordered_set>
#include<unordered_map>
#include<queue>
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

    string line;

    while (getline(file, line))
    {
        string source, destination, strPrice;
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

    file << map.size() << endl;

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
    auto sourceCity = map.find(src);
    auto destinationCity = map.find(dest);

    // Check if source and destination cities exist
    if (sourceCity == map.end() || destinationCity == map.end()) {
        QMessageBox::information(nullptr, "Warning", "Source or destination city not found in the map!");
        return;
    }

    // for undirected graph
    bool existsForward = false;
    bool existsBackward = false;

    // Check forward direction: source to destination
    auto& sourceDestinations = sourceCity->second;
    for (auto& destinationPair : sourceDestinations) {
        if (ignoreCaseInsensitive(destinationPair.first, dest)) { // Check if the destination exists
            for (auto& transPair : destinationPair.second) {
                if (ignoreCaseInsensitive(transPair.vehicle, method)) { // Check if the method exists
                    existsForward = true;
                    break;
                }
            }
            break;
        }
    }

    // Check backward direction: destination to source
    auto& destDestinations = destinationCity->second;
    for (auto& destinationPair : destDestinations) {
        if (ignoreCaseInsensitive(destinationPair.first, src)) { // Check if the source exists
            for (auto& transPair : destinationPair.second) {
                if (ignoreCaseInsensitive(transPair.vehicle, method)) { // Check if the method exists
                    existsBackward = true;
                    break;
                }
            }
            break;
        }
    }

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


//void RoadMap::updateTransportation(const string& source, const string& destination, const string& vehicle, double newPrice) {
//    // Check if the source exists in the map
//    auto sourceIter = map.find(source);
//    if (sourceIter == map.end()) {
//        //cout << "Source city not found in the map." << endl;
//        QMessageBox::information(nullptr, "Information", "Source city not found in the map!");
//        return;
//    }
//
//    // Find the transportation options for the specified destination from the source
//    auto& destinations = sourceIter->second;
//    for (auto& destinationPair : destinations) {
//        if (destinationPair.first == destination) {
//            // Search for the transportation option with the given vehicle
//            for (auto& transport : destinationPair.second) {
//                if (transport.vehicle == vehicle) {
//                    // Update the price of the transportation option
//                    transport.price = newPrice;
//                    //cout << "Transportation price updated successfully." << endl;
//                    QMessageBox::information(nullptr, "Information", "Transportation price updated successfully!");
//                    break;
//                }
//            }
//            
//            //cout << "Transportation vehicle not found for the given source and destination." << endl;
//            QMessageBox::information(nullptr, "Information", "Transportation vehicle not found for the given source and destination!");
//            return;
//        }
//    }
//
//    //sourceIter = map.find(destination);
//    //destinations = sourceIter->second;
//    //for (auto& destinationPair : destinations) {
//    //    if (destinationPair.first == source) {
//    //        // Search for the transportation option with the given vehicle
//    //        for (auto& transport : destinationPair.second) {
//    //            if (transport.vehicle == vehicle) {
//    //                // Update the price of the transportation option
//    //                transport.price = newPrice;
//    //                //cout << "Transportation price updated successfully." << endl;
//    //                QMessageBox::information(nullptr, "Information", "Transportation price updated successfully!");
//    //                break;
//    //            }
//    //        }
//
//    //        //cout << "Transportation vehicle not found for the given source and destination." << endl;
//    //        QMessageBox::information(nullptr, "Information", "Transportation vehicle not found for the given source and destination!");
//    //        return;
//    //    }
//    //}
//
//    //cout << "Destination city not found for the given source." << endl;
//    QMessageBox::information(nullptr, "Information", "Destination city not found for the given source!");
//
//}

void RoadMap::updateTransportation(const string& source, const string& destination, const string& vehicle, double newPrice) {
    // Check if both the source and destination exist in the map
    auto sourceIter = map.find(source);
    auto destIter = map.find(destination);
    if (sourceIter == map.end() || destIter == map.end()) {
        cout << "Source or destination city not found in the map." << endl;
        QMessageBox::information(nullptr, "Information", "Destination city not found for the given source!");
        return;
    }

    // Find the transportation options for the specified destination from the source
    auto& sourceDestinations = sourceIter->second;
    auto& destDestinations = destIter->second;

    // Update the price from source to destination
    bool foundSourceDest = false;
    for (auto& destinationPair : sourceDestinations) {
        if (destinationPair.first == destination) {
            foundSourceDest = true;
            // Search for the transportation option with the given vehicle
            for (auto& transport : destinationPair.second) {
                if (transport.vehicle == vehicle) {
                    // Update the price of the transportation option
                    transport.price = newPrice;
                    cout << "Transportation price updated successfully from " << source << " to " << destination << "." << endl;
                    QMessageBox::information(nullptr, "Information", "Transportation price updated successfully !");
                    break;
                }
            }
            break;
        }
    }
    if (!foundSourceDest) {
        cout << "Destination city not found for the given source." << endl;
        QMessageBox::information(nullptr, "Information", "Destination city not found for the given source !");
        return;
    }

    // Update the price from destination to source
    bool foundDestSource = false;
    for (auto& destinationPair : destDestinations) {
        if (destinationPair.first == source) {
            foundDestSource = true;
            // Search for the transportation option with the given vehicle
            for (auto& transport : destinationPair.second) {
                if (transport.vehicle == vehicle) {
                    // Update the price of the transportation option
                    transport.price = newPrice;
                    cout << "Transportation price updated successfully from " << destination << " to " << source << "." << endl;
                    break;
                }
            }
            break;
        }
    }
    if (foundDestSource == false)
    {
        QMessageBox::information(nullptr, "Information", "Destination city not found for the given source !");
        cout << "Destination city not found for the given source." << endl;
    }
}

/////////////////////////////////////////////////
void RoadMap::deleteTransportation(string source, string destination, string transport)
{
        // Display all edges
        auto sourceCity = map.find(source);
        if (sourceCity != map.end())
        {
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
            else
                QMessageBox::information(nullptr, "Alert", "The Destination city doesn't exist!");

        }
        else
            QMessageBox::information(nullptr, "Alert", "The source city doesn't exist!");

}
////////////////////////////////////////////////
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

    if (map.size() == visited.size())
        QMessageBox::information(nullptr, "Connection", "The Map is Connected! 〜(￣▽￣〜)");
    else
        QMessageBox::information(nullptr, "Connection", "The Map is NOT Connected! ┑(￣Д ￣)┍");
}

void RoadMap::ALLAVALIABLEPATHS(string node, double cost) {

    if (node == destination) /// node ---child
    {
        if (cost <= targetmoney)
            routs.emplace_back(cost, path);
        return;
    }
    for (auto child : map[node]) {

        if (child.first == source)
            continue;
        for (auto V : child.second) {
            if (!vis[child.first]) {
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
    sort(routs.begin(), routs.end());

    if (routs.empty())
        QMessageBox::information(nullptr, "Paths", "There are no transportation to the target destination! ┑(￣Д ￣)┍");

    QString text;
    for (auto r : routs)
    {
        
        text.append(source).append(" ");
        while (!r.second.empty()) // what was the wrong
        {
            text.append("( ").append(r.second.front().second).append(" ) ").append(r.second.front().first).append(" ");
            r.second.pop();
        }
        text.append(QString::number(r.first)).append("\n");
    }
    return text;

}

//dfs algo
QString RoadMap::dfs(string v) {
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

                if (!vis[it->first] && it->second.size() != 0) {
                    s.push(it->first);

                }
            }
        }
    }

    QString text;
    while (!dfsoutr.empty()) {
        //cout << dfsoutr.front() << endl;
        text.append(dfsoutr.front()).append("\n");
        dfsoutr.pop();
    }
    return text;
}

//bfs algo
QString RoadMap::bfs(string v) {
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
                if (!vis[it->first] && it->second.size() != 0) {
                    bfs_queue.push(it->first);
                }

            }
        }
    }
   
    QString text;
    while (!bfsout.empty()) {
        //cout << bfsout.front() << endl;
        text.append(bfsout.front()).append("\n");
        bfsout.pop();
    }
    return text;

}
//////////////////////////////////////////////////////////

QString RoadMap::DisplayEdges(string source, string destination)
{ 
    QString text;
    auto sourceCity = map.find(source);
    if (sourceCity != map.end())
    {
       
        for (auto& desCity : sourceCity->second)
        {
            if (desCity.first == destination && !desCity.second.empty())
            {
                for (auto trans = desCity.second.begin(); trans != desCity.second.end(); trans++)
                {
                    text.append(trans->vehicle).append(" - ").append(QString::number(trans->price)).append("\n");

                }
                break;
            }
            
        }

    }
    else
    {
        QMessageBox::information(nullptr, "Alert", "The source city doesn't exist!");  
    }

    if(text=="") QMessageBox::information(nullptr, "Alert", "No Transporatation between them!");
     
    return text;

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
