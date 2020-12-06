#include <iostream>
#include <string>


// https://adventofcode.com/2020/day/6

using namespace std;

int unique(string s, int tot) {
    int let[26] = { 0 };
    int ct = 0;
    for (char c : s) {
        let[c - 'a']++;
		ct += let[c - 'a'] == tot;
    }
    return ct;
}

int main() {	

	auto ppl = 0;
    auto count = 0;

	string data;
	string line;
	while (getline(cin, line) || !data.empty()) {
		if(line.empty()) {
			count += unique(data, ppl);
			data.clear();
			ppl = 0;
		} else {
			data.append(line);
			ppl++;
		}
	}

	cout << count << endl;
	return 0;
}
