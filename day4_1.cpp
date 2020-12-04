#include <iostream>
#include <vector>
#include <string>

// https://adventofcode.com/2020/day/4

using namespace std;

vector<string> keys = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };

int countTokens(string data)  {
	auto ct = 0;
	for (string key : keys) {
		ct += data.find(key + ":") != string::npos;
	}
	// cout << ct << endl;
	return ct;
}

int main() {
	
	auto valid = 0;

	string data;
	string line;
	while (getline(cin, line) || !data.empty()) {
		if(line.empty()) {
			valid += countTokens(data) == 7;
			data.clear();
		} else {
			data.append(line);
		}
	}

	cout << valid << endl;


	return 0;
}
