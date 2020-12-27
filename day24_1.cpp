#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

// https://adventofcode.com/2020/day/24

using namespace std;

// https://www.redblobgames.com/grids/hexagons/
// axial coordinates
unordered_map<string, pair<int, int>> coords = {
    {"e",  {1, 0}},
    {"se", {0, 1}},
    {"sw", {-1, 1}},
    {"w",  {-1, 0}},
    {"nw", {0, -1}},
    {"ne", {1, -1}}
};

vector<pair<int, int>> parsedirs(string dir) {
    vector<pair<int, int>> dirs;

    for (int i = 0; i < dir.length(); i++) {
        if (dir[i] == 'n' || dir[i] == 's') {
            dirs.push_back(coords[dir.substr(i, 2)]);
            i++;
        } else {
            dirs.push_back(coords[dir.substr(i, 1)]);
        }
    }

    return dirs;
}

pair<int, int> getcoord(vector<pair<int, int>> dirs) {
    pair<int, int> coord = {0, 0};
    for (auto d : dirs) {
        coord.first += d.first;
        coord.second += d.second;
    }

    return coord;
}

// A hash function used to hash a pair of any kind 
struct hash_pair { 
    template <class T1, class T2> 
    size_t operator()(const pair<T1, T2>& p) const
    { 
        auto hash1 = hash<T1>{}(p.first); 
        auto hash2 = hash<T2>{}(p.second); 
        return hash1 ^ hash2; 
    }
};

int main() {

    unordered_map<pair<int, int>, bool, hash_pair> tiles;

    string line;
    while(getline(cin, line)) {
        auto dirs = parsedirs(line);
        auto coord = getcoord(dirs);
        
        tiles[coord] = !tiles[coord];
    }

    int ans = 0;
    for (auto tile : tiles)
        ans += tile.second;

    cout << ans << endl;
    return 0;
}