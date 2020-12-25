#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// https://adventofcode.com/2020/day/23

using namespace std;

// auto in = "389125467";
auto in = "716892543";

vector<int> stovec(string input) {
    vector<int> ans;
    for (auto i : input) {
        ans.push_back(i - '0');
    }
    return ans;
}

int min(vector<int> vec) {
    return *min_element(vec.begin(), vec.end());
}

int max(vector<int> vec) {
    return *max_element(vec.begin(), vec.end());
}

int x(int i, vector<int> vec) {
    if (i < 0) i = vec.size() + (i % vec.size());
    return vec[i % vec.size()];
}

int ind(int i, vector<int> vec) {
    if (i < 0) i = vec.size() + (i % vec.size());
    return i % vec.size();
}

vector<int>::iterator find(int i, vector<int> &vec) {
    return find(vec.begin(), vec.end(), i);
}

vector<int> rm(vector<int> &vec, int from, int to) {
    vector<int> removed;
    for (int i = from; i < to; i++) {
        auto vi = ind(i, vec);
        removed.push_back(vec[vi]);
        vec[vi] = -1; // mark for death
    }

    vec.erase(std::remove(vec.begin(), vec.end(), -1), vec.end());

    return removed;
}

int domove(vector<int> &vec, int curi) {
    // auto curit = vec.begin() + ind(curi, vec);
    // int cur = *curit;
    int cur = x(curi, vec);
    vector<int> removed = rm(vec, curi+1, curi+4);
    int dest = cur;

    auto dest_it = vec.end();
    while (dest_it == vec.end()) {
        if (--dest < min(vec)) dest = max(vec); 
        dest_it = find(dest, vec);
    }

    vec.insert(dest_it+1, removed.begin(), removed.end());
    return ind(find(cur, vec) + 1 - vec.begin(), vec);
}

void print(vector<int> vec) {
    for (int v : vec)
        cout << v << " ";
    cout << endl;
}

string vectostr(vector<int> vec) {
    string s;
    for (auto v : vec) {
        s += v + '0';
    }
    return s;
}

int main() {

    auto list = stovec(in);
    int st = 0;
    for (int i = 0; i < 100; i++) {
        st = domove(list, st);
    }

    string ans = vectostr(list);

    while (ans[0] != '1') ans = ans.substr(1) + ans[0];

    ans = ans.substr(1);
    cout << ans << endl;
    return 0;
}