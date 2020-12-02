#include <iostream>
#include <vector>
#include <string>
#include <regex>

// https://adventofcode.com/2020/day/2

// http://www.cplusplus.com/doc/tutorial/basic_io/

using namespace std;
int main() {
	
	// vector<string> strings;
	// vector<pair<int, int>> ranges; 
	int valid = 0;

	regex rgx("(\\d{1,2})-(\\d{1,2}) ([a-z]): ([a-z]+)");
	smatch sm;
	string line;
	while (getline(cin, line)) {
		regex_search(line, sm, rgx);
		auto low = stoi(sm[1]);
		auto hig = stoi(sm[2]);
		auto c = sm[3].str()[0];
		auto st = sm[4].str();

		auto ct = count(st.begin(), st.end(), c);
		if (ct >= low && ct <= hig)
			valid++;
	}

	cout << valid << endl;
	return 0;
}
