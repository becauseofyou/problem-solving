#include <bits/stdc++.h>
using namespace std;

struct node {
    char s[110];
}a[10010];

bool cmp(node a, node b) {
    return strcmp(a.s, b.s) < 0;
}

int main() {
//    sort (a, a + n, cmp);

    char str1[10]="abcde";
    char str2[10]="bdef";
    strcpy(str1, str2);
    printf("%s\n", str1);
    return 0;
}
