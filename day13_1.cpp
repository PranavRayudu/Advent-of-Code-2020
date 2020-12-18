#include <string>
#include <iostream>

// https://adventofcode.com/2020/day/13

using namespace std;

int mod(int a, int t) {
    return a - (t % a);
} 

int main() {

    string line;
    cin >> line;
    int time = stoi(line);
    int min_id;
    int min_time = 0x7fffffff;

    // https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    cin >> line;
    size_t pos = 0;
    string token;
    int id, t;
    while ((pos = line.find(',')) != string::npos) {
        token = line.substr(0, pos);
        if (token[0] != 'x') {
            id = stoi(token);
            t = mod(id, time);
            
            if (t < min_time) {
                min_id = id;
                min_time = t;
            }
        }

        line.erase(0, pos + 1);
    }

    cout << min_id * min_time << endl;

    return 0;
}
