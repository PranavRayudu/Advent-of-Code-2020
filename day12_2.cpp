#include <string>
#include <iostream>
#include <stdlib.h>

// https://adventofcode.com/2020/day/12

using namespace std;

// https://stackoverflow.com/questions/38251229/modulo-with-a-negative-integer-in-c
int mod(int a, int b) { return (a % b + b) % b; }


void rot(int &x, int &y, int d) {
    int t;
    switch (mod(d, 360)) {
        case 90:
            t = -x;
            x = y;
            y = t;
        break;  
        case 180: 
            x *= -1;
            y *= -1;
        break;
        case 270:
            t = x;
            x = -y;
            y = t;
    }
}

int main() {

    pair<int, int> xy;
    int x = 0, y = 0;
    int wx = 10, wy = 1;

    string line;
    while(getline(cin, line)) {
        int n = stoi(line.substr(1));
        switch (line[0]) {
            case 'N': wy += n;
            break;
            case 'E': wx += n;
            break;
            case 'W': wx -= n;
            break;
            case 'S': wy -= n;
            break;
            case 'F':
                x += wx * n;
                y += wy * n;
            break;
            case 'R': rot(wx, wy, n);
            break;
            case 'L': rot(wx, wy, -n);
        }
    }

    cout << abs(x) + abs(y) << endl;

    return 0;
}
