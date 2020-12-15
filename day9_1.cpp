#include <deque>
#include <string>
#include <iostream>


// https://adventofcode.com/2020/day/9

using namespace std;

constexpr int preamble = 25;

bool hasSum(deque<uint64_t> q, int sum) {
    for (deque<uint64_t>::iterator i = q.begin(); i != q.end(); i++) {
        for (deque<uint64_t>::iterator j = i + 1; j != q.end(); j++) {
            if (*i + *j == sum) return true;
        }
    }
    return false;
}

int main() {

    deque<uint64_t> numbers;

    uint64_t num;
    string line;
	while (getline(cin, line)) {
        num = stoull(line);

        if(numbers.size() >= preamble) {
            if(!hasSum(numbers, num)) break;
            numbers.pop_front();
        }

        numbers.push_back(num);
    }

    cout << num << endl;

    return 0;
}