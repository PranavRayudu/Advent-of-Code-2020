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
    
    int *diffs = new int[adapters.size()];
    long *count = new long[adapters.size()];

    int prev = 0;
    for (int i = 0; i < adapters.size(); i++) {
        int a = adapters[i];
        diffs[i] = a - prev;
        prev = a;
    }

    count[0] = 1;
    for (int i = 1; i < adapters.size(); i++) {
        
        long s = 0, j = 0, k = i - 1;
        while (j + diffs[k] <= 3 && k >= 0 && k >= i - 3) {
            s += count[k];
            j += diffs[k];
            k--;
        }
        count[i] = s;
    }

    cout << count[adapters.size() - 1] << endl;
    delete[] diffs;
    delete[] count;

    return 0;
}