#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// https://adventofcode.com/2020/day/23

using namespace std;

// string in = "389125467";
string in = "716892543";

// auto turns = 100;
auto turns = 10'000'000;
// auto listsz = 9;
auto listsz = 1'000'000;

inline bool is(int i, int a, int b, int c) {
    return i == a || i == b || i == c;
}

int domove(int* list, int curi) {
    auto rm1 = list[curi];
    auto rm2 = list[rm1];
    auto rm3 = list[rm2];
    auto dest = curi - 1;

    while (dest <= 0 || is(dest, rm1, rm2, rm3))
        if (--dest <= 0) dest = listsz;

    list[curi] = list[rm3];
    list[rm3] = list[dest];
    list[dest] = rm1;
    return list[curi];
}

void print(int *arr, int m = 10) {
    for (int i = 1; i <= m; i++)
        // cout arr[i] << " ";
        cout << i << ": " << arr[i] << endl;
    cout << endl;
}

void populate(int *list, string input) {
    
    for (auto it = input.begin(); it < input.end() - 1; it++) {
        int i = *it - '0';
        int j = *(it + 1) - '0';
        list[i] = j;
    }

    int i = input.back() - '0';
    list[i] = input.front() - '0';
    if (input.length() >= listsz) return;
    
    list[i] = input.length() + 1;

    for (i = input.length() + 1; i < listsz; i++) {
        list[i] = i + 1;
    }

    list[listsz] = input.front() - '0';
}

int main() {

    auto list = new int[listsz + 1];
    populate(list, in);

    // print(list);

    int st = in.front() - '0';
    for (int i = 0; i < turns; i++) {
        st = domove(list, st);
    }

    long a = list[1];
    long b = list[a];
    cout << a * b << endl;
    return 0;
}