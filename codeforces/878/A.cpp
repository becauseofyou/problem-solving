#include <bits/stdc++.h>

using namespace std;


int main() {
    int n;
    cin >> n;
    char c;
    int x;
    int a = 0, b = 1023;
    for (int i = 0; i < n; i++) {
        cin >> c >> x;
        if(c=='&') {
            a &= x, b &= x;
        } else if (c == '|') {
            a |= x, b |= x;
        } else {
            a ^= x, b ^= x;
        }
    }
    int _xor = 0;
    int _or = 0;
    int _and = 0;
    for (int i = 0; i < 10; i++) {
        int bit1 = a >> i & 1;
        int bit2 = b >> i & 1;
        if (bit1 == 1 && bit2  == 0) {
            _or += 0;
            _xor += 1 << i;
        }
        if (bit1 == 1 && bit2 == 1) {
            _or += 1 << i;
            _xor += 0;
        }
        if (bit1 == 0 && bit2 == 0) {
            _or += 1 << i;
            _xor += 1 << i;
        }
        if (bit1 == 0 && bit2 == 1) {
        }
    }
    cout << 2 << endl;
    cout << "| " << _or << endl;
    cout << "^ " << _xor << endl;
    return 0;
}
