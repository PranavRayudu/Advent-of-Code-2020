#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

// https://adventofcode.com/2020/day/10

using namespace std;

int main() {

    vector<int> adapters;

    string line;
    while(getline(cin, line)) {
        auto n = stoi(line);

        adapters.push_back(n);
    }

    sort(adapters.begin(), adapters.end());
    adapters.push_back(adapters[adapters.size() - 1] + 3);
    
    int j1 = 0, j3 = 0;

    int prev = 0;
    for (int a : adapters) {
        if (a - prev == 1) j1++;
        if (a - prev == 3) j3++;
        prev = a;
    }

    cout << j1 * j3 << endl;

    return 0;
}