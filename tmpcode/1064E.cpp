#include <bits/stdc++.h>
using namespace std;


int main() {
    int n;
    cin >> n;
    int x = (int)1e9;
    int left = 0, right = (int) 1e9;
    for (int i = 0; i < n; i++) {
        int mid =  (left+right)/2;
        printf("%d 0\n", mid);
        fflush(stdout);
        string s;
        cin >> s;
        if (s == "black") {
            right = mid;
        } else {
            left = mid;
        }
    }
    printf("%d 0 %d 1\n", right - 1, right - 1);
    fflush(stdout);
    return 0;
}
