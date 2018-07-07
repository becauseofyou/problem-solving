#include <bits/stdc++.h>
using namespace std;

char s[222222];
int main () {
    int n;
    scanf("%d", &n);
    scanf("%s", s);
    stack<int> stk;
    for (int i = 0; s[i]; i++) {
        if (!stk.empty() && stk.top() != s[i]) {
            stk.pop();
        } else {
            stk.push(s[i]);
        }
    }
    printf ("%d\n", (int)stk.size());
    return 0;
}
