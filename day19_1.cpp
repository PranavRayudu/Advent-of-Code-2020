#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

// https://adventofcode.com/2020/day/19

using namespace std;

vector<int> tokenize(string l) {
    std::stringstream ls(l);
    vector<int> tokens;

    string t;
    while (getline(ls, t, ' ')) {
        if (!t.empty()) tokens.push_back(stoi(t));
    }
    return tokens;
}

struct rule {

    static unordered_map<int, rule> rules;

    string r;
    vector<int> left_rule;
    vector<int> right_rule;

    rule() {}

    rule(string ru) {
        int q1, q2;
        if ((q1 = ru.find("\"")) != string::npos
         && (q2 = ru.find("\"")) != string::npos) {
             r = ru.substr(q1+1, q2);
         } else {
            string left;
            string right;
            int div;
            if ((div = ru.find("|")) != string::npos) {
                left = ru.substr(0, div);
                right = ru.substr(div+1);
            } else {
                left = ru;
            }

            if (!left.empty()) left_rule = tokenize(left);
            if (!right.empty()) right_rule = tokenize(right);
         }
    }

    bool evaluate(string a) {
        return this->eval(a) == a.length();
    }

    int eval(string a) {
        if (!r.empty()) return a.length() >= r.length() && a.substr(0, r.size()) == r ? r.length() : -1;
        
        bool good = true;
        int i = 0;
        for (auto r : left_rule) {
            int ans = rules[r].eval(a.substr(i));
            if (ans == -1) {
                good = false;
                break;
            }
            else i += ans;
        }

        if (good) return i;
        if (!good && right_rule.empty()) return -1;

        good = true;
        i = 0;
        for (auto r : right_rule) {
            int ans = rules[r].eval(a.substr(i));
            if (ans == -1) {
                good = false;
                break;
            }
            else i += ans;
        }

        if (good) return i;
        else return -1;
    }
};

unordered_map<int, rule> rule::rules;

int main() {

    string line;
    while(getline(cin, line) && !line.empty()) {
        int d = line.find(":");
        int key = stoi(line.substr(0, d));
        rule::rules[key] = rule(line.substr(d+1));
    }

    int ct = 0;
    while(getline(cin, line)) {
        bool ok = rule::rules[0].evaluate(line);
        ct += ok;
    }

    cout << ct << endl;

    return 0;
}