#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// https://adventofcode.com/2020/day/18

using namespace std;

vector<string> parse(string line) {
    long p = 0;
    while((p = line.find("(", p)) != string::npos) {
        if (line[p+1] != ' ') line.insert(p+1, " ", 1);
        if (line[p-1] != ' ') {line.insert(p, " ", 1); p++;}
        p++;
    }

    p = 0;
    while((p = line.find(")", p)) != string::npos) {
        if (line[p+1] != ' ') line.insert(p+1, " ", 1);
        if (line[p-1] != ' ') {line.insert(p, " ", 1); p++;}
        p++;
    }

    stringstream ls(line);

    vector<string> tokens;
    string temp;
    while (getline(ls, temp, ' ')) if (!temp.empty()) tokens.push_back(temp);
    return tokens;
}

enum op {N, P, M, OB, CB};
struct tok {
    long num;
    op o;

    bool isnum() { return o == N; }
    bool isop() { return o == P || o == M; }
    tok(string s) {
        if (s[0] >= '0' && s[0] <= '9') {
            o = N;
            num = stoi(s);
        } else {
            switch (s[0]) {
                case '+': o = P;
                break;
                case '*': o = M;
                break;
                case '(': o = OB;
                break;
                case ')': o = CB;
            }
            num = 0;
        }
    }

    tok(long n): num(n), o(N) { }
};

long evaulate(vector<string> in) {

    vector<tok> operators;
    vector<tok> nums;
    for (long i = 0; i < in.size(); i++) {
        string token = in[i];

        tok t(token);
        if (t.isnum()) nums.push_back(token);
        else {
            if (t.o == CB) {
                while (operators.back().o != OB) {
                    nums.push_back(operators.back());
                    operators.pop_back();
                }

                if (operators.back().o == OB)
                    operators.pop_back();
            } else {
                while (!operators.empty() && t.isop() && operators.back().isop()) {
                    nums.push_back(operators.back());
                    operators.pop_back();
                }

                operators.push_back(t);
            }
        }
    }

    while (!operators.empty()) {
        nums.push_back(operators.back());
        operators.pop_back();
    }

    for (long i = 0; i < nums.size(); i++) {
        if (nums[i].o == N) {
            operators.push_back(nums[i]);
        } else {
            auto a = operators.back().num;
            operators.pop_back();
            auto b = operators.back().num;
            operators.pop_back();
            switch (nums[i].o) {
                case P:
                    a = a + b;
                break;
                case M:
                    a = a * b;
            }
            operators.push_back({a});
        }
    }

    return operators[0].num;
}

int main() {

    long sum = 0;

    string line;
    vector<string> parsed;
    while (getline(cin, line)) {
        parsed = parse(line);
        sum += evaulate(parsed);   
    }

    cout << sum << endl;

    return 0;
}