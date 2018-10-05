#include <bits/stdc++.h>
using namespace std;

struct interval {
    int l, r;

    //成员函数
    void input() {
        scanf("%d%d", &l, &r);
    }

    void solve() {
    }


    bool operator < (const interval& tmp) const {
        return l < tmp.l;
    }

};


bool operator == (interval a, interval b) {
    return a.l == b.l && a.r == b.r;
}



int cmp(interval a, interval b) {
    if (a.l != b.l) {
        return a.l < b.l;
    }
    return a.r < b.r;
}

//函数的重载
int fun(int a, int b) {
    return a + b;
}

double fun(double a, double b) {
    return a + b;
}

interval data[110];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        data[i].input();
    }
    if (data[0] == data[1]) {
        puts("yes");
    } else {
        puts("no");
    }

    //nlogn
    sort (data, data + n);

    for (int i = 0; i < n; i++) {
        printf("%d %d\n", data[i].l, data[i].r);
    }
    return 0;
}
