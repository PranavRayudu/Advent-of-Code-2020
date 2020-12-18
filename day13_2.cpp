#include <string>
#include <iostream>
#include <vector>
#include<bits/stdc++.h> 


// https://adventofcode.com/2020/day/13

using namespace std; 
 
// Returns modulo inverse of a with respect to m using extended 
// Euclid Algorithm. Refer below post for details: 
// https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/ 
long inv(long a, long m) 
{ 
    long m0 = m, t, q; 
    long x0 = 0, x1 = 1; 
 
    if (m == 1) 
    return 0; 
 
    // Apply extended Euclid Algorithm 
    while (a > 1) 
    { 
        // q is quotient 
        q = a / m; 
 
        t = m; 
 
        // m is remainder now, process same as 
        // euclid's algo 
        m = a % m, a = t; 
 
        t = x0; 
 
        x0 = x1 - q * x0; 
 
        x1 = t; 
    } 
 
    // Make x1 positive 
    if (x1 < 0) 
    x1 += m0; 
 
    return x1; 
} 
 
// k is size of num[] and rem[]. Returns the smallest 
// number x such that: 
// x % num[0] = rem[0], 
// x % num[1] = rem[1], 
// .................. 
// x % num[k-2] = rem[k-1] 
// Assumption: Numbers in num[] are pairwise coprime 
// (gcd for every pair is 1) 
long chineseRemainder(vector<int> n, vector<int> a) {
    // Compute product of all numbers
    long prod = 1;
    for (int i = 0; i < n.size(); i++) prod *= n[i];
 
    // Initialize result
    long result = 0;
 
    // Apply above formula
    for (int i = 0; i < a.size(); i++) {
        long p = prod / n[i];
        result += a[i] * inv(p, n[i]) * p;
    }

    return result % prod;
} 
 
int main() {

    
    string line;
    cin >> line;

    vector<int> times;

    // https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    cin >> line;
    string token;
    while (!line.empty()) {
        size_t pos = line.find(',');
        if (pos == string::npos) pos = line.size();

        token = line.substr(0, pos);
        if (token[0] != 'x') times.push_back(stoi(token));
        else                 times.push_back(0);

        line.erase(0, pos + 1);
    }

    vector<int> a;
    vector<int> n;

    for (int i = 0; i < times.size(); i++) {
        if (times[i] != 0) {
            n.push_back(times[i]);
            a.push_back(times[i] - i);
        }
    }

    cout << chineseRemainder(n, a) << endl;

    return 0;
}
