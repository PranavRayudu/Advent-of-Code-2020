#include <iostream>
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
	
    auto maxid = 0;

	string line;
	while (getline(cin, line)) {
		auto id = getid(line);
        maxid = max(maxid, id);
	}

    cout << maxid << endl;

	return 0;
}
