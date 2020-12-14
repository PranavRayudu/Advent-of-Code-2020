#include <iostream>
#include <vector>
#include <string>


// https://adventofcode.com/2020/day/8

using namespace std;

enum op { JMP, NOP, ACC, DONE };

vector<pair<op, int>> code;

vector<pair<op, int>> parseProgram() {
	
	vector<pair<op, int>> prog;
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
		prog.push_back({o, i});
	}
	return prog;
}

pair<bool, int> execute(int i, int ct) {
	
	auto temp = code;

    int counter = 0;
	bool ok = true;
	pair<op, int> ins;
	while (i < temp.size() && ok) {
		int inc = 1;
        ins = temp[i];
        temp[i].first = DONE;

        if (ins.first == DONE) {
            ok = false;
        } else if (ins.first == ACC) {
            counter += ins.second;
        } else if (ins.first == JMP) {
            inc = ins.second;
        } else if (ins.first == NOP) {}

		i += inc;

	}

	return {ok, counter};
}

int main() {	
	
	code = parseProgram();

	pair<bool, int> res;
	for (int i = 0; i < code.size(); i++) {
		
		if (code[i].first == JMP || code[i].first == NOP) {
			for (int j = 0; j < 2; j++) {
				if ((res = execute(0, 0)).first) break;
				code[i].first = (op) !code[i].first;
			}
		}
	}

    cout << res.second << endl;
	return 0;
}
