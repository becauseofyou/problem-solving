#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    vector <int> l(n), r(n);
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
    }
    sort(l.begin(),l.end());
    sort(r.begin(),r.end());
    long long ret = n;
    for (int i = 0; i < n; i++) {
        ret += max(l[i], r[i]);
    }
    cout << ret << endl;
    return 0;
}

