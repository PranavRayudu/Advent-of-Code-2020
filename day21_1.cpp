#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm> 

// https://adventofcode.com/2020/day/21

using namespace std;

// trim from start (in place)
static inline void ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), s.end());
}

// trim from both ends (copying)
static inline string trim(string s) {
    ltrim(s);
    rtrim(s);
    return s;
}

vector<string> tokenize(string l, char delim) {
    stringstream ls(l);
    vector<string> tokens;

    string t;
    while (getline(ls, t, delim)) 
        if (!t.empty()) 
            tokens.push_back(trim(t));
    return tokens;
}

template <typename T>
set<T> vecToSet(vector<T> v) { 
    return {v.begin(), v.end()}; 
}

template <typename T>
set<T> diff(set<T> a, set<T> b) {
    set<T> difference;
    set_difference(
        a.begin(), a.end(), b.begin(), b.end(), 
        inserter(difference, difference.begin()));
    return difference;
}

// https://stackoverflow.com/questions/13448064/how-to-find-the-intersection-of-two-stdset-in-c
template <typename T>
set<T> intersection(set<T> a, set<T> b) {
    set<T> intersect;
    set_intersection(
        a.begin(), a.end(), b.begin(), b.end(), 
        inserter(intersect, intersect.begin()));
    return intersect;
}

void rm(pair<set<string>, set<string>> food, 
        vector<pair<set<string>, set<string>>> &foods) {
    for (auto &f : foods) {
        f.first = diff(f.first, food.first);
        f.second = diff(f.second, food.second);
    }
}

pair<set<string>, set<string>> common(
    pair<set<string>, set<string>> a, pair<set<string>, set<string>> b) {
    return {intersection(a.first, b.first), intersection(a.second, b.second)};
}

template <typename T>
bool in(T t, set<T> con) {
    auto it = con.find(t);
    return it != con.end();
}

int main() {

    vector<pair<set<string>, set<string>>> foods;
    set<string> allergens;
    
    string line;
    while(getline(cin, line)) {
        int st = line.find("(contains ");
        int end = line.find(")");
        auto f = vecToSet(tokenize(line.substr(0, st), ' '));
        auto a = vecToSet(tokenize(line.substr(st+10, end-st-10), ','));
        foods.push_back({f, a});
        allergens.insert(a.begin(), a.end());
    }

    // alt-intersection test
    for (int i = 0; i < foods.size(); i++) {
        
        auto allergens = foods[i].second;
        for (auto allergen : allergens) {
            auto food = foods[i].first;
            for (int j = 0; j < foods.size(); j++) {
                if (i != j && in(allergen, foods[j].second)) {
                    food = intersection(food, foods[j].first);
                }
            }
            if (food.size() == 1)
                rm({food, {allergen}}, foods);
        }
    }

    int tot = 0;
    for (int i = 0; i < foods.size(); i++) {
        tot += foods[i].first.size();
    }

    cout << tot << endl;

    return 0;
}