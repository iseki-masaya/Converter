//
//  main.cpp
//  Converter
//
//  Created by iseki on 2015/05/25.
//  Copyright (c) 2015年 iseki. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>

using namespace std;

typedef pair<string, double> PersonPageRank;

vector<string> split(const string &s, set<char> delims) {
    vector<string> elems;
    string item;
    for (char ch: s) {
        if (delims.count(ch)) {
            if (!item.empty())
                elems.push_back(item);
            item.clear();
        }
        else {
            item += ch;
        }
    }
    if (!item.empty())
        elems.push_back(item);
    return elems;
}

double convert(const string &s) {
    stringstream ss(s);
    double res;
    ss >> res;
    return res;
}

int main(int argc, const char * argv[]) {
    /** The result of calculation.
     *  ex) 0.145 A
     *      0.234 B
     *      0.456 C
    */
    ifstream pagerank_file("/tmp/part-r-00000");
    /** The result of SQL.
     *  ex) A
     *      B
     *      C
     */
    ifstream person_file("/tmp/lived");

    string str;
    set<char> delims;
    delims.insert('\t');
    delims.insert(' ');
    
    map<string, double> pagerank;
    while (getline(pagerank_file, str)) {
        vector<string> vstr(split(str, delims));
        pagerank.insert({vstr[1], convert(vstr[0])});
    }
    
    vector<PersonPageRank> people;
    while (getline(person_file, str)) {
        people.push_back(PersonPageRank(str, pagerank[str]));
    }
    
    sort(people.begin(), people.end(), [](const PersonPageRank &lhs, const PersonPageRank &rhs) {
        return lhs.second > rhs.second;
    });
    
    for (int i=0; i<10; ++i) {
        cout << people[i].first << endl;
    }
}
