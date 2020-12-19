#include <string>
#include <iostream>
#include <unordered_map>

// https://adventofcode.com/2020/day/14

using namespace std; 

long setbit(long n, int i, bool b) {
    long bitmask = 1l << i;
    if (b) {
        n |= bitmask;
    } else {
        bitmask = -1 ^ bitmask;
        n &= bitmask;
    }
    return n;
}

void applyMask( int i, 
                long n, 
                string mask, 
                unordered_map<long, long> &mem, long val) {

    for(; i < mask.length(); i++) {
        char c = mask[i];
        if (c == 'X') {
            n = setbit(n, mask.length() - i - 1, 0);
            applyMask(i + 1, n, mask, mem, val);
            
            n = setbit(n, mask.length() - i - 1, 1);
            applyMask(i + 1, n, mask, mem, val);
            return;
        } else if (c == '1') {
            n |= 1l << (mask.length() - i  - 1);
        }
    }

    mem[n] = val;
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
            long m = code.first, n = stol(code.second);
            applyMask(0, m, mask, mem, n);
        } else {
            mask = code.second;
        }
    }

    long sum = 0;
    for (auto m : mem) sum += m.second;

    cout << sum << endl;

    return 0;
}