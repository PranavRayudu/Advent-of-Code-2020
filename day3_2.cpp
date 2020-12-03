#include <iostream>
#include <vector>
#include <string>

// https://adventofcode.com/2020/day/3

using namespace std;

int trees_encountered(vector<string> map, int c_off, int r_off) {
	auto r = 0, c = 0;
	auto trees = 0;

	while ((r + r_off < map.size())) {
		r += r_off, c += c_off;
		trees += map[r][c % map[r].length()] == '#';
	}

	return trees;
}

int main() {
	
	vector<string> map;

	string line;
	while (getline(cin, line)) {
		map.push_back(line);
	}

	vector<pair<int, int>> off = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};

	auto tree_mult = 1l;
	for (pair<int, int> o : off) 
		tree_mult *= trees_encountered(map, o.first, o.second);
	
	cout << tree_mult << endl;

	return 0;
}
