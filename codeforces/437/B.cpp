#include <bits/stdc++.h>
using namespace std;
int main() {
    int sum, limit;
    cin >> sum >> limit;
    vector <int> ret;
    for (int i = 0; i < 17; i++) {
        if (sum & (1 << i)) {
            ret.push_back(1 << i);
        }
    }
    cout << ret.size() << endl;
    for (int  v: ret) {
        cout << v << " " ;
    }
    return 0;
}
