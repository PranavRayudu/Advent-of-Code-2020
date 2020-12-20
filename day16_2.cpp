#include <string>
#include <iostream>
#include <vector>


// https://adventofcode.com/2020/day/16

using namespace std;

pair<int, int> parseRange(string range) {
    auto dash = range.find("-");
    return {stoi(range.substr(0, dash)), stoi(range.substr(dash + 1))};
}

pair<pair<int, int>, pair<int, int>> parseRanges(string ranges) {
    auto delim = ranges.find("or");
    return {parseRange(ranges.substr(0, delim - 1)), parseRange(ranges.substr(delim + 3))};
}

bool inRange(int n, pair<int, int> range) {
    return range.first <= n && n <= range.second;
}

vector<int> parseTicket(string line) {
    
    vector<int> ticket;

    int pos;
    string token;
    
    while (!line.empty()) {
        pos = line.find(',');
        if (pos == string::npos) pos = line.size();
        
        token = line.substr(0, pos);
        // cout << token << endl;
        int n = stoi(token);
        ticket.push_back(n);
        line.erase(0, pos + 1);
    }

    return ticket;
}

pair<bool, int> getPos(int n, vector<pair<int, int>> &ranges) {
    int c = 0;
    int pos = 0;
    for (int i = 0; i < ranges.size(); i++) {
        if (inRange(n, ranges[i])) {
            c++;
            pos = i;
        }
    }
    cout << n << " " << c << " " << pos / 2 << endl;
    return {c == 1, pos / 2};
}

bool remove(int val, int j, vector<vector<int>> &vec) {
    for (int i = 0; i < vec[j].size(); i++) {
        if (vec[j][i] == val) {
            vec[j].erase(vec[j].begin() + i);
            if (vec[j].size() == 1) {
                for (int k = 0; k < vec.size(); k++)
                    if (k != j) remove(vec[j][0], k, vec);
            }
            return true;
        }
    }
    return false;
}


int find(int n, vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == n) return i;
    }

    return -1;
}

int main() {

    vector<pair<int, int>> ranges;

    vector<vector<int>> tickets;

    string line;
    while(getline(cin, line)) {
        if (line.empty()) break;

        auto col = line.find(":");
        auto r = parseRanges(line.substr(col + 2));

        ranges.push_back(r.first);
        ranges.push_back(r.second);
    }
    
    while (getline(cin, line) && line != "your ticket:");
    // cout << line << endl;
    getline(cin, line);
    // cout << line << endl;
    tickets.push_back(parseTicket(line));
        // getline(cin, line);
    // cout << "done" << endl;
    while (getline(cin, line) && line != "nearby tickets:");


    int pos;
    string token;
    while (getline(cin, line)) {
        
        auto ticket = parseTicket(line);
        
        bool ok;
        for (auto t : ticket) {
            ok = false;
            for (auto r : ranges) {
                if (ok = inRange(t, r)) break;
            }
            if (!ok) break;
        }

        if (ok) tickets.push_back(ticket);
    }

    vector<vector<int>> places;
    
    for (int i = 0; i < ranges.size() / 2; i++) {
        vector<int> p;
        for (int j = 0; j < ranges.size() / 2; j++) {
            p.push_back(j);
        }

        places.push_back(p);
    }


    for (int i = 1; i < tickets.size(); i++) {
        
        for (int j = 0; j < tickets[i].size(); j++) {
            int v = tickets[i][j];
            auto &place = places[j];
            for (int k = 0; k < ranges.size(); k+=2) {
                auto range1 = ranges[k];
                auto range2 = ranges[k+1];
                if (!inRange(v, range1) && !inRange(v, range2))
                    remove(k/2, j, places);
            }
        }
    }

    vector<int> place;
    for (int i = 0; i < ranges.size() / 2; i++) {
        place.push_back(places[i][0]);
    }


    long ans = 1;
    for (int i = 0; i < 6; i++) {
        ans *= tickets[0][find(i, place)];
    }

    cout << ans << endl;

    return 0;
}