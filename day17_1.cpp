#include <iostream>
#include <string>
#include <vector>

// https://adventofcode.com/2020/day/17

using namespace std;

constexpr int cycles = 6;

void simulate(int ***grida, int ***gridb, int sx, int sy, int sz) {

    auto bounds = [sx, sy, sz](int x, int y, int z) {
        return 0 <= x && x < sx && 0 <= y && y < sy && 0 <= z && z < sz;
    };

    auto next = [](int cur, int n) {
        if (cur)    return n == 2 || n == 3;
        else        return n == 3;
    };

    auto neighbours = [bounds, grida, sx, sy, sz](int x, int y, int z) {
        int tot = 0;
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                for (int k = -1; k < 2; k++) {
                    if ((i != 0 || j != 0 || k != 0) 
                    && bounds(x + i, y + j, z + k))
                        tot += grida[x + i][y + j][z + k];
                }
            }
        }
        return tot;
    };

    for (int x = 0; x < sx; x++) {
        for (int y = 0; y < sy; y++) {
            for (int z = 0; z < sz; z++) {
                gridb[x][y][z] = next(grida[x][y][z], neighbours(x, y, z));
            }
        }
    }
}

int count(int ***grid, int sx, int sy, int sz) {
    int c = 0;

    for (int x = 0; x < sx; x++) {
        for (int y = 0; y < sy; y++) {
            for (int z = 0; z < sz; z++) {
                c += grid[x][y][z];
            }
        }
    }

    return c;
}

int main() {

    vector<string> init_grid;

    string line;
    while (getline(cin, line)) {
        init_grid.push_back(line);
    }

    int sx = line.length() + cycles * 2;
    int sy = init_grid.size() + cycles * 2;
    int sz = 1 + cycles * 2;

    int ***grida = new int **[sx];
    int ***gridb = new int **[sx];
    for (int j = 0; j < sx; j++) {
        grida[j] = new int *[sy];
        gridb[j] = new int *[sy];
        for (int k = 0; k < sy; k++) {
            grida[j][k] = new int[sz];
            gridb[j][k] = new int[sz];
        }
    }

    for (int x = 0; x < line.length(); x++) {
        for (int y = 0; y < init_grid.size(); y++) {
            grida[x + cycles][y + cycles][cycles] = init_grid[x][y] == '#';
        }
    }

    for (int i = 0; i < cycles; i++) {
        simulate(grida, gridb, sx, sy, sz);
        swap(grida, gridb);
    }

    cout << count(grida, sx, sy, sz) << endl;

    return 0;
}