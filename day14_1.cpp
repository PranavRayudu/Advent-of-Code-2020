#include <string>
#include <iostream>
#include <unordered_map>

// https://adventofcode.com/2020/day/14

using namespace std; 

long applyMask(long n, string mask) {

    for(int i = 0; i < mask.length(); i++) {
        char c = mask[i];
        if (c == 'X') continue;

        bool bit = c - '0';
        long bitmask = 1l << (mask.length() - i  - 1);

        if (bit) {
            n |= bitmask;
        } else {
            bitmask = -1 ^ bitmask;
            n &= bitmask;
        }
    }

    return n;
}

pair<long, string> parseLine(string line) {
    if (line.find("mask") != string::npos) {
        return {0, line.substr(7, line.length())};
    } else {
        auto st = line.find("["), end = line.find("]");
        auto eq = line.find("=");
        return {stol(line.substr(st + 1, end)), 
                line.substr(eq + 2, line.length())};
    }
}

int main() {

    unordered_map<long, long> mem;
    string mask;

    string line;
    while(getline(cin, line)) {
        auto code = parseLine(line);
        if (code.first) {
            long n = stol(code.second);
            mem[code.first] = applyMask(n, mask);
        } else {
            mask = code.second;
        }
    }

    long sum = 0;
    for (auto m : mem) sum += m.second;

    cout << sum << endl;

    return 0;
}