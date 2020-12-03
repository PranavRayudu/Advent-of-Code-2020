#include <iostream>
#include <vector>
#include <string>

// https://adventofcode.com/2020/day/3

using namespace std;
int main() {
	
	vector<string> map;

	string line;
	while (getline(cin, line)) {
		map.push_back(line);
	}

	const auto c_off = 3, r_off = 1;
	auto r = 0, c = 0;
	auto trees = 0;

	while ((r + r_off < map.size())) {
		r += r_off, c += c_off;
		trees += map[r][c % map[r].length()] == '#';
	}

	cout << trees << endl;

	return 0;
}
