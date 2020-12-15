#include <deque>
#include <string>
#include <iostream>


// https://adventofcode.com/2020/day/9

using namespace std;

constexpr int preamble = 25;

bool hasSum(deque<uint64_t> q, int sum) {
    for (deque<uint64_t>::iterator i = q.end() - preamble; i != q.end(); i++) {
        for (deque<uint64_t>::iterator j = i + 1; j != q.end(); j++) {
            if (*i + *j == sum) return true;
        }
    }
    return false;
}

pair<uint64_t, uint64_t> findRange(deque<uint64_t> q, uint64_t sum) {
    pair<uint64_t, uint64_t> range;
    for (deque<uint64_t>::iterator i = q.begin(); i != q.end(); i++) {
        deque<uint64_t>::iterator j;
        uint64_t mi = 0xffffffffffffffff, ma = 0, s = 0;

        for (j = i; j != q.end() && s < sum; j++) {
            s += *j;
            mi = min(mi, *j);
            ma = max(ma, *j);
        }

        if (s == sum) return {mi, ma};
    }

    return {0, 0};
}

int main() {

    deque<uint64_t> numbers;

    pair<uint64_t, uint64_t> range{0, 0};
    string line;
	while (getline(cin, line) && (range.first == 0 || range.second == 0)) {
        uint64_t num = stoull(line);

        if(numbers.size() >= preamble)
            if(!hasSum(numbers, num)) range = findRange(numbers, num);

        numbers.push_back(num);
    }

    cout << range.first + range.second << endl;

    return 0;
}