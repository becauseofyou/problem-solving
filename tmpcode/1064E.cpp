#include <bits/stdc++.h>
using namespace std;


int main() {
    int n;
    cin >> n;
    int left = 0, right = (int) 1e9;
    printf("%d 0\n", right);
    fflush(stdout);
    string s;
    cin >> s;
    int flag = 1;
    if (s == "white") {
        flag = 0;
    }
    for (int i = 0; i < n; i++) {
        int mid =  (left+right) / 2;
        printf("%d 0\n", mid);
        fflush(stdout);
        cin >> s;
        if (s == "black") {
            if (flag) {
                right = mid;
            } else {
                left = mid;
            }
        } else {
            if (flag) {
                left = mid;
            } else {
                right = mid;
            }
        }
    }
    printf("%d 0 %d 1\n", right - 1, right - 1);
    fflush(stdout);
    return 0;
}
