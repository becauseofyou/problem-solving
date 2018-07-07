#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
	while(a && b) {
		if (a < b)  {
			swap(a, b);
		}
		a -= b;
	}
	return b;
}

int s[100010];
int main () {
	int n, a[26];
	scanf("%d", &n);
	int odd = 0; 
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		if (a[i] & 1) {
			odd++;
		}
	}
	if (odd > 1) {
		puts("0");
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < a[i]; j++) {
                printf("%c", 'a' + i);
			}
		}
        puts("");
        return 0;
	}
	int _gcd = a[0];
	for (int i = 1; i < n; i++) {
		_gcd = gcd(_gcd, a[i]);
	}

    int cnt = 0;
    int id = -1;
	for (int i = 0; i < n; i++) {
		a[i] /= _gcd;
        if (a[i] & 1) {
        	id = i;
            cnt++;
        }
	}
	int parts = _gcd;
    if (cnt > 1) {
        for (int i = 0; i < n; i++) {
            a[i] *= 2;
        }
        parts /= 2;
    }
    memset(s, 0, sizeof(s));
    int l = 0, r = accumulate(a, a + n, 0) - 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < a[i] / 2; j++) {
        	s[l++] = s[r--] = 'a' + i;
	    }
    }
    if (cnt == 1) {
    	s[l] = 'a' + id;
    }
    printf ("%d\n", _gcd);
    for (int i = 0; i < parts; i++) {
    	for (int j = 0; s[j]; j++) {
    		printf("%c", s[j]);
    	}
    }
	return 0;
}
