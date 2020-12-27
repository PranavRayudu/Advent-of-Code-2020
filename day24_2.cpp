#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <set>

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

constexpr int days = 100;

typedef unordered_map<pair<int, int>, bool, hash_pair> tilemap;
typedef unordered_map<pair<int, int>, int, hash_pair> neighbourmap;
typedef set<pair<int, int>> tileset;

vector<pair<int, int>> parsedirs(string &dir) {
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

pair<int, int> getcoord(vector<pair<int, int>> &dirs) {
    pair<int, int> coord = {0, 0};
    for (auto d : dirs) {
        coord.first += d.first;
        coord.second += d.second;
    }

    return coord;
}

neighbourmap countNeighbours(tileset &blackTiles) {
    neighbourmap neighbours;
    for (auto &blackTile : blackTiles) {
        auto q = blackTile.first, r = blackTile.second;
        for (auto &coord : coords) {
            int dq = coord.second.first, dr = coord.second.second;
            ++neighbours[{q + dq, r + dr}];
        }
    }

    return neighbours;
}

tileset newTiles(tileset &blackTiles, neighbourmap &neighbours) {
    tileset newBlackTiles;
    for (auto &neighbour : neighbours) {
        auto coord = neighbour.first;
        auto count = neighbour.second;
        if (blackTiles.find(coord) != blackTiles.end()) {
            if (count <= 2) newBlackTiles.insert(coord);
        } else {
            if (count == 2) newBlackTiles.insert(coord);
        }
    }

    return newBlackTiles;
}

int main() {

    tilemap tiles;

    string line;
    while(getline(cin, line)) {
        auto dirs = parsedirs(line);
        auto coord = getcoord(dirs);
        tiles[coord] = !tiles[coord];
    }

    tileset blackTiles;

    for (auto tileb : tiles) {
        if (tileb.second) blackTiles.insert(tileb.first);
    }

    for (int i = 0; i < days; i++) {
        neighbourmap neighbours = countNeighbours(blackTiles);
        blackTiles = newTiles(blackTiles, neighbours);
    }

    cout << blackTiles.size() << endl;
    
    return 0;
}