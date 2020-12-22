#include <iostream>
#include <string>
#include <deque>
#include <set>

// https://adventofcode.com/2020/day/22

using namespace std;

int pop(deque<int> &q) {
    int n = q.front();
    q.pop_front();
    return n;
}

long hashq(deque<int> q) {
    constexpr int init = 0;
    constexpr int M = 31;
    long hash = init;
    for(auto i : q)
        hash += M * hash + i;
    return hash;
}

int score(deque<int> p) {
    int score = 0;
    while (!p.empty()) {
        score += p.front() * p.size();
        p.pop_front();
    }
    return score;
}

deque<int> copy(deque<int> q, int n) {
    deque<int> p;
    for (int i = 0; i < n; i++) {
        p.push_back(pop(q));
    }
    return p;
}

pair<int, int> play(deque<int> p1, deque<int> p2) {

    set<pair<int, int>> seen;

    while (!p1.empty() && !p2.empty()) {
        int ahash = hashq(p1);
        int bhash = hashq(p2);
        if (!seen.insert({ahash, bhash}).second) {
            return {1, score(p1)};
        }

        int a = pop(p1);
        int b = pop(p2);

        bool awin = 0;
        if (a <= p1.size() && b <= p2.size()) {
            auto res = play(copy(p1, a), copy(p2, b));
            awin = res.first;
        } else {
            awin = a > b;
        }

        if (awin) {
            p1.push_back(a);
            p1.push_back(b);
        } else {
            p2.push_back(b);
            p2.push_back(a);
        }
    }

    return {!p1.empty(), score(!p1.empty() ? p1 : p2)};
}


int main() {

    deque<int> p1, p2;

    deque<int> *p;

    string line;
    while(getline(cin, line)) {
        
        if (line.empty()) continue;

        if (line == "Player 1:") {
            p = &p1;
        } else if (line == "Player 2:") {
            p = &p2;
        } else {
            int n = stoi(line);
            p->push_back(n);
        }
    }

    cout << play(p1, p2).second << endl;

    return 0;
}
