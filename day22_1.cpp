#include <iostream>
#include <string>
#include <deque>


// https://adventofcode.com/2020/day/22

using namespace std;

int score(deque<int> p) {
    int score = 0;
    while (!p.empty()) {
        score += p.front() * p.size();
        p.pop_front();
        
    }
    return score;
}


int play(deque<int> p1, deque<int> p2) {

    while (!p1.empty() && !p2.empty()) {
        int a = p1.front();
        p1.pop_front();
        int b = p2.front();
        p2.pop_front();

        if (a > b) {
            p1.push_back(a);
            p1.push_back(b);
        } else {
            p2.push_back(b);
            p2.push_back(a);
        }
    }

    return score(!p1.empty() ? p1 : p2);
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

    cout << play(p1, p2) << endl;

    return 0;
}
