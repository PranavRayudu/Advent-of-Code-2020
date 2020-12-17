#include <string>
#include <iostream>
#include <stdlib.h>

// https://adventofcode.com/2020/day/12

using namespace std;

// https://stackoverflow.com/questions/38251229/modulo-with-a-negative-integer-in-c
int mod(int a, int b) { return (a % b + b) % b; }


pair<int, int> dxy(int d) {
    switch (mod(d, 360)) {
        case 0: return {0, 1};
        case 90: return {1, 0};
        case 180: return {0, -1};
        case 270: return {-1, 0};
        default: return {0, 0};
    }
}

int main() {

    pair<int, int> xy;
    int d = 90;
    int x = 0, y = 0;

    string line;
    while(getline(cin, line)) {
        int n = stoi(line.substr(1));
        switch (line[0]) {
            case 'N': y += n;
            break;
            case 'E': x += n;
            break;
            case 'W': x -= n;
            break;
            case 'S': y -= n;
            break;
            case 'F': 
                xy = dxy(d);
                x += xy.first * n;
                y += xy.second * n;
            break;
            case 'R': d += n;
            break;
            case 'L': d -= n;
        }
    }

    cout << abs(x) + abs(y) << endl;

    return 0;
}
