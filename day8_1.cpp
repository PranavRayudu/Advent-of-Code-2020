#include <iostream>
#include <vector>
#include <string>


// https://adventofcode.com/2020/day/8

using namespace std;

enum op { ACC, JMP, NOP, DONE };

int main() {	
	
	vector<pair<op, int>> code;

	string line;
	
	while (getline(cin, line)) {
		string ins = line.substr(0, 3);
		string val = line.substr(3);

		op o = DONE;
		if (ins == "acc") {
			o = ACC;
		} else if (ins == "jmp") {
			o = JMP;
		} else if (ins == "nop") {
			o = NOP;
		}

		int i = stoi(val);
		code.push_back({o, i});
	}

	int i = 0;
    int counter = 0;
	while (i < code.size()) {

        auto ins = code[i];
        code[i].first = DONE;
        if (ins.first == DONE) {
            break;
        } else if (ins.first == ACC) {
            counter += ins.second;
            i++;
        } else if (ins.first == JMP) {
            i += ins.second;
        } else if (ins.first == NOP) {
            i++;
        }
	}

    cout << counter << endl;
	return 0;
}
