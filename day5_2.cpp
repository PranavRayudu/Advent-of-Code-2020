#include <iostream>
#include <algorithm>
#include <string>


// https://adventofcode.com/2020/day/5

using namespace std;

int strtobin(string s, char high) {
    int bin = 0;

    for (int i = 0; i < s.size(); i++) {
        bin |= (s[i] == high) << s.size() - i - 1;
    }

    return bin;
}

int getid(string pass) {
    // cout << pass.substr(0, 7) << ", " << pass.substr(7) << endl;
    auto row = strtobin(pass.substr(0, 7), 'B');
    auto col = strtobin(pass.substr(7), 'R');
    // cout << row << ", " << col << endl;
    return row * 8 + col;
}


int main() {
	
    bool exists[1024] = {false};

	string line;
	while (getline(cin, line)) {
		auto id = getid(line);
        exists[id] = true;
	}

    auto beg = find(exists + 1, exists + 1023, true);
    auto i = find(beg + 1, exists + 1023, false);
    cout << i - exists << endl;

	return 0;
}
