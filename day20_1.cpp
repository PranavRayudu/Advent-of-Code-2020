#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm> 

// https://adventofcode.com/2020/day/20

using namespace std;

constexpr int side = 10;

vector<string> getEdges(array<string, side> grid) {
    vector<string> edges;
    edges.push_back(grid[0]);
    edges.push_back(grid[side-1]);
    
    string left, right;
    for (int i = 0; i < side; i++) {
        left += grid[i][0];
        right += grid[i][side-1];
    }
    edges.push_back(left);
    edges.push_back(right);
    return edges;
}

string flip(string a) {
    string b = a;
    reverse(b.begin(), b.end());
    return b;
}

int findMatches(pair<int, vector<string>> s1, 
    unordered_map<int, vector<string>> edges) {
    
    int matches = 0;
    for (auto edge1 : s1.second) {
        for (auto s2 : edges) {
            if (s1.first != s2.first) {
                for (auto edge2 : s2.second) {
                    if (edge1 == edge2 || edge1 == flip(edge2)) {
                        matches++;
                        break;
                    }
                }
            }
        }
    }

    return matches;
}

int main() {

    unordered_map<int, vector<string>> edges;

    string line;
    while(getline(cin, line)) {
        int n = stoi(line.substr(5, 9));

        array<string, side> grid;
        for (int i = 0; i < side; i++) {
            getline(cin, line);
            grid[i] = line;
        }

        edges[n] = getEdges(grid);
        getline(cin, line);
    }

    long ans = 1;
    for (auto edge : edges) {
        int res = findMatches(edge, edges);
        if (res == 2) {
            ans *= edge.first;
        }
    }

    cout << ans << endl;

    return 0;
}
