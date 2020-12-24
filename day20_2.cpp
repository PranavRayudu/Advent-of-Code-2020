#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm> 
#include <math.h>
#include <functional>

// https://adventofcode.com/2020/day/20

using namespace std;

constexpr int side = 10;

string flipstr(string a) {
    string b = a;
    reverse(b.begin(), b.end());
    return b;
}

vector<string> getEdges(array<string, side> grid) {
    vector<string> edges;
    
    string left, right;
    for (int i = 0; i < side; i++) {
        left += grid[i][0];
        right += grid[i][side-1];
    }

    edges.push_back(grid[0]);
    edges.push_back(right);
    edges.push_back(grid[side-1]);
    edges.push_back(left);
    return edges;
}

array<string, side> rotateCW(array<string, side> tile) {
    array<string, side> newTile = tile;

    for (int i = 0; i < side; i++)
        for (int j = 0; j < side; j++)
            newTile[i][j] = tile[side - 1 - j][i];

    return newTile;
}

array<string, side> flipX(array<string, side> tile) {
    array<string, side> newTile = tile;

    for (int y = 0; y < side; y++)
        for (int x = 0; x < side; x++)
            newTile[y][x] = tile[y][side-x-1];

    return newTile;
}

array<string, side> flipY(array<string, side> tile) {
    array<string, side> newTile = tile;

    for (int y = 0; y < side; y++)
        for (int x = 0; x < side; x++)
            newTile[y][x] = tile[side-y-1][x];

    return newTile;
}

auto t1 = [](array<string, side> otile) { return otile; };
auto t2 = [](array<string, side> otile) { return flipY(otile); };
auto t3 = [](array<string, side> otile) { return flipX(otile); };
auto t4 = [](array<string, side> otile) { return flipX(flipY(otile)); };
auto t5 = [](array<string, side> otile) { return rotateCW(otile); };
auto t6 = [](array<string, side> otile) { return rotateCW(flipY(otile)); };
auto t7 = [](array<string, side> otile) { return rotateCW(flipX(otile)); };
auto t8 = [](array<string, side> otile) { return rotateCW(flipX(flipY(otile))); };

// auto t1 = [](array<string, side> otile) { return otile; };
// auto t2 = [](array<string, side> otile) { return rotateCW(otile); };
// auto t3 = [](array<string, side> otile) { return rotateCW(rotateCW(otile)); };
// auto t4 = [](array<string, side> otile) { return rotateCW(rotateCW(rotateCW(otile))); };
// auto t5 = [](array<string, side> otile) { return flipY(otile); };
// auto t6 = [](array<string, side> otile) { return rotateCW(flipY(otile)); };
// auto t7 = [](array<string, side> otile) { return rotateCW(rotateCW(flipY(otile))); };
// auto t8 = [](array<string, side> otile) { return rotateCW(rotateCW(rotateCW(flipY(otile)))); };
vector<function<array<string, side>(array<string, side>)>> transforms
        = { t1, t2, t3, t4, t5, t6, t7, t8 };
array<string, side> match(array<string, side> tile, 
    vector<array<string, side>> &tiles, int s) {

    auto edges = getEdges(tile);
    auto side1 = edges[s];
    for (auto it = tiles.begin(); it != tiles.end(); ++it) {
        for (int i = 0; i < transforms.size(); i++) {
            auto otile = *it;
            otile = transforms[i](*it);
            auto oedge = getEdges(otile)[(s+2)%4];
            if (side1 == oedge) {
                tiles.erase(it);
                return otile;
            }
        }
    }

    return {};
}

array<string, side> nomatch(vector<array<string, side>> &tiles, int s1, int s2) {
    
    for (auto it1 = tiles.begin(); it1 != tiles.end(); ++it1) {

        bool good = true;
        for (int t = 0; t < transforms.size() && good; t++) {
            auto trans = transforms[t];
            auto tile = trans(*it1);

            auto edges = getEdges(tile);
            auto side1 = edges[s1];
            auto side2 = edges[s2];
            
            for (auto it2 = tiles.begin(); it2 != tiles.end() && good; ++it2) {
                if (it1 != it2) {
                    auto oedges = getEdges(*it2);
                    for (auto oedge : oedges) {
                        if (side1 == oedge || side1 == flipstr(oedge) || 
                            side2 == oedge || side2 == flipstr(oedge)) {
                            good = false;
                            break;
                        }
                    }
                }
            }

            if (good) {
                tiles.erase(it1);
                return tile;
            }
        }
    }

    return {};
}

array<string, side-2> removeBorders(array<string, side> tile) {
    array<string, side-2> newTile;
    for (int y = 1; y < side-1; y++)
        for (int x = 1; x < side-1; x++)
            newTile[y-1][x-1] = tile[y][x];

    return newTile;
}

void apply(char **grid, array<string, side-2> tile, int x1, int y1) {
    for (int y = y1; y < y1 + side-2; y++)
        for (int x = x1; x < x1 + side-2; x++)
            grid[y][x] = tile[y-y1][x-x1];
}

void apply(char **grid, array<string, side> tile, int x1, int y1) {
    for (int y = y1; y < y1 + side; y++)
        for (int x = x1; x < x1 + side; x++)
            grid[y][x] = tile[y-y1][x-x1];
}


int gridsz;
void print(char **grid) {
    for (int y = 0; y < gridsz; y++) {
        cout << grid[y] << endl;
    }
    cout << endl;
}

char **newGrid() {
    char **grid = new char*[gridsz];
    for (int i = 0; i < gridsz; i++) {
        grid[i] = new char[gridsz+1];
        fill_n(grid[i], gridsz, '-');
        grid[i][gridsz] = 0;
    }
    return grid;
}

char **gridFlipY(char** grid) {
    auto newg = newGrid();
    for (int y = 0; y < gridsz; y++) {
        for (int x = 0; x < gridsz; x++) {
            auto temp = grid[y][x];
            newg[y][x] = grid[gridsz-y-1][x];
        }
    }
    return newg;
}

// https://www.geeksforgeeks.org/inplace-rotate-square-matrix-by-90-degrees/
char **rotateGrid(char **grid) {
    auto newg = newGrid();
    for (int x = 0; x < gridsz / 2; x++) {
        for (int y = x; y < gridsz - x - 1; y++) {
            auto temp = grid[y][x];
            newg[y][x] = grid[gridsz - 1 - x][y];
            newg[gridsz - 1 - x][y] = grid[gridsz - 1 - y][gridsz - 1 - x];
            newg[gridsz - 1 - y][gridsz - 1 - x] = grid[x][gridsz - 1 - y];
            newg[x][gridsz - 1 - y] = temp;
        }
    }
    return newg;
}

vector<string> monster = {
    "                  # ",
    "#    ##    ##    ###",
    " #  #  #  #  #  #   ",
};

int dragons(char **grid) {
    
    int d = 0;
    for (int y = 0; y < gridsz - monster.size(); y++) {
        for (int x = 0; x < gridsz - monster[0].length(); x++) {
            
            bool m = true;
            for (int dy = 0; dy < monster.size() && m; dy++) {
                for (int dx = 0; dx < monster[0].length() && m; dx++) {
                    m = monster[dy][dx] != '#' || (
                        monster[dy][dx] == '#' && grid[y+dy][x+dx] == '#');
                }
            }

            if (m) {
                for (int dy = 0; dy < monster.size() && m; dy++) {
                    for (int dx = 0; dx < monster[0].length() && m; dx++) {
                        if (monster[dy][dx] == '#') grid[y+dy][x+dx] = 'O';
                    }
                }
            }

            d += m;
        }
    }
    return d;
}

int count(char **grid) {
    int c = 0;
    for (int y = 0; y < gridsz; y++) {
        for (int x = 0; x < gridsz; x++) {
            c += grid[y][x] == '#';
        }
    }

    return c;
}

auto g1 = [](char **grid) { return grid; };
auto g2 = [](char **grid) { return rotateGrid(grid); };
auto g3 = [](char **grid) { return rotateGrid(rotateGrid(grid)); };
auto g4 = [](char **grid) { return rotateGrid(rotateGrid(rotateGrid(grid))); };
auto g5 = [](char **grid) { return gridFlipY(grid); };
auto g6 = [](char **grid) { return rotateGrid(gridFlipY(grid)); };
auto g7 = [](char **grid) { return rotateGrid(rotateGrid(gridFlipY(grid))); };
auto g8 = [](char **grid) { return rotateGrid(rotateGrid(rotateGrid(gridFlipY(grid)))); };

vector<function<char**(char**)>> gridTransforms = { g1, g2, g3, g4, g5, g6, g7, g8 };

int main() {

    vector<array<string, side>> tiles;

    string line;
    while(getline(cin, line)) {
        int n = stoi(line.substr(5, 9));

        array<string, side> grid;
        for (int i = 0; i < side; i++) {
            getline(cin, line);
            grid[i] = line;
        }

        tiles.push_back(grid);
        getline(cin, line);
    }

    int tilect = sqrt(tiles.size());
    int tilesz = side-2;
    gridsz = tilect * side;
    gridsz = tilect * tilesz;
    
    char **grid = newGrid();
    vector<array<string, side>> takenTiles;
    auto tile = nomatch(tiles, 0, 3);
    
    apply(grid, removeBorders(tile), 0, 0);
    takenTiles.push_back(tile);

    for (int y = 0; y < gridsz; y += tilesz) {
        for (int x = 0; x < gridsz; x += tilesz) {
            
            if (y != 0 || x != 0) {
                int previ;
                if (x == 0) {
                    previ = (y/tilesz-1) * tilect;
                    tile = match(takenTiles[previ], tiles, 2);
                } else {
                    // previ = takenTiles.size() - 1;
                    previ = y/tilesz * tilect + (x/tilesz-1);
                    tile = match(takenTiles[previ], tiles, 1);
                }
                apply(grid, removeBorders(tile), x, y);
                takenTiles.push_back(tile);
                
                // print(grid);
            }
        }
    }

    int drags;
    for (auto gt : gridTransforms) {
        auto newg = gt(grid);
        if (drags = dragons(newg)) {
            print(newg);
            break;
        }
    }

    cout << drags << endl;
    cout << count(grid) - drags * 15 << endl;

    return 0;
}