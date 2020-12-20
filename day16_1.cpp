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

int main() {

    vector<pair<int, int>> ranges;

    string line;
    while(getline(cin, line)) {
        if (line.empty()) break;

        auto col = line.find(":");
        auto r = parseRanges(line.substr(col + 2));
        ranges.push_back(r.first);
        ranges.push_back(r.second);
    }

    while (getline(cin, line) && line != "nearby tickets:");

    int sum = 0;

    int pos;
    string token;
    while (getline(cin, line)) {
        while (!line.empty()) {
            pos = line.find(',');
            if (pos == string::npos) pos = line.size();
            
            token = line.substr(0, pos);
            int n = stoi(token);

            bool ok = false;
            for (auto range : ranges) if (ok = inRange(n, range)) break;

            if (!ok) sum += n;;

            line.erase(0, pos + 1);
        }

    }

    cout << sum << endl;    

    return 0;
}