#include <iostream>
#include <string>


// https://adventofcode.com/2020/day/6

using namespace std;

int unique(string s) {
    bool let[26] = { false };
    int ct = 0;
    for (char c : s) {
        ct += !let[c - 'a'];
        let[c - 'a'] = true;
    }
    return ct;
}

int main() {	


    auto count = 0;

	string data;
	string line;
	while (getline(cin, line) || !data.empty()) {
		if(line.empty()) {
			count += unique(data);
			data.clear();
		} else {
			data.append(line);
		}
	}

	cout << count << endl;
	return 0;
}
