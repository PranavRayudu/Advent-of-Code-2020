#include <string>
#include <iostream>

// https://adventofcode.com/2020/day/25

using namespace std;

long mod = 20201227;

inline void transform(long &sub, long subject_num) {
    sub = (sub * subject_num) % mod;
}

long findloop(long pub_key) {
    constexpr int sub = 7;
    long loop = 0;
    long key = 1;
    while (key != pub_key) {
        transform(key, sub);
        loop++;
    }
    return loop;
}

inline long loop_transform(long pub, long loop) {
    long p = 1;
    for (long i = 0; i < loop; i++) transform(p, pub);
    return p;
}

int main() {

    string card, door;

    long pub_card, pub_door;

    cin >> card;
    cin >> door;

    pub_card = stoi(card);
    pub_door = stoi(door);

    long card_loop = findloop(pub_card);
    long door_loop = findloop(pub_door);

    long hash;
    hash = loop_transform(pub_card, door_loop);
    hash = loop_transform(pub_door, card_loop);

    cout << hash << endl;

    return 0;
}