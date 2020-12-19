#include <iostream>
#include <unordered_map>

// https://adventofcode.com/2020/day/15

using namespace std; 

int data[] = {6, 4, 12, 1, 20, 0, 16};
// int data[] = {0, 3, 6};

int y = 2020;

int doTurn() {
    return 0;
}

int main() {
    
    // <number, <turn last spoken, turn before last spoken>>
    unordered_map<int, pair<int, int>> nums;
    size_t size = sizeof(data) / sizeof(int);
    for (int i = 0; i < size; i++) {
        nums[data[i]] = {i, i};
    }

    int last_spoken = data[size - 1];
    for (int turn = size; turn < y; turn++) {

        auto n = nums.find(last_spoken);

        int x = n->second.first - n->second.second;
        
        if (nums.find(x) == nums.end()) {
            nums[x].second = turn;
            nums[x].first = turn;
        } else {
            nums[x].second = nums[x].first;
            nums[x].first = turn;
        }
        
        last_spoken = x;
    }
    
    cout << last_spoken << endl;

    return 0;
}