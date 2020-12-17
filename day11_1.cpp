#include <string>
#include <vector>
#include <iostream>
#include <cstring>


// https://adventofcode.com/2020/day/11

using namespace std;


int neighbours(char **grida, int i, int j, char c, int l1, int l2) {
    int n = -(grida[i][j] == c);
    for (int di = -1; di < 2; di++) 
        for (int dj = -1; dj < 2; dj++)
            if (i + di >= 0 && i + di < l1
             && j + dj >= 0 && j + dj < l2)
                n += grida[i + di][j + dj] == c;
    return n;
}


bool gen(char **grida, char **gridb, int l1, int l2) {
    
    bool d = false;
    for (int i = 0; i < l1; i++) {
        for (int j = 0; j < l2; j++) {
            int n = neighbours(grida, i, j, '#', l1, l2);
            if (grida[i][j] == 'L' && n == 0) {
                d |= gridb[i][j] = '#';
            } else if (grida[i][j] == '#' && n >= 4) {
                d |= gridb[i][j] = 'L';
            } else {
                gridb[i][j] = grida[i][j];
            }
        }
    }

    return d;
}

int count(char **grida, char c, int l1, int l2) {
    int ct = 0;
    for (int i = 0; i < l1; i++) {
        for (int j = 0; j < l2; j++) {
            ct += grida[i][j] == c;
        }
    }
    return ct;
}

int main() {

    vector<string> seats;

    string line;
    while (getline(cin, line)) seats.push_back(line);

    int l1 = seats.size();
    int l2 = seats[0].length();
    char **grida = new char*[l1];
    char **gridb = new char*[l1];

    for (int i = 0; i < l1; i++) {
        grida[i] = new char[l2];
        gridb[i] = new char[l2];

        memcpy(grida[i], seats[i].c_str(), l2);
    }

    while (gen(grida, gridb, l1, l2)) swap(grida, gridb);

    cout << count(grida, '#', l1, l2) << endl;

    return 0;
}