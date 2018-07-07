#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
char s[N];
int mp[256];
struct Bit {
	int c[N];
	void Insert (int x, int value) {
		for (; x < N; x += x&-x) {
			c[x] += value;
		}
	}
	int Sum (int x) {
		int ret = 0;
		for (; x; x -= x&-x) {
			ret += c[x];
		}
		return ret;
	}
}tree[4][11][12]; // which character, %MOD, MOD  

int main (){
	mp['A'] = 0;
	mp['T'] = 1;
	mp['G'] = 2;
	mp['C'] = 3;
	scanf("%s", s + 1);
	int n = strlen (s + 1);
	for (int i = 1; i <= n; i++) {
		for (int len = 1; len <= 11; len ++) {
			int m = i % len;
			tree[mp[s[i]]][m][len].Insert(i, 1);
		}
	}
	int q, pos, op, l, r;
	char to[2], query_str[11];
	scanf("%d", &q);
	while(q --) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d%s", &pos, to);
			if (s[pos] == to[0]) {
				continue;
			}
			int which = mp[s[pos]];
			for (int len = 1; len <= 11; len++) {
				int m = pos % len;
				tree[which][m][len].Insert(pos, -1);
			}
			s[pos] = to[0];
			which = mp[s[pos]];
			for (int len = 1; len <= 11; len++) {
				int m = pos % len;
				tree[which][m][len].Insert(pos, 1);
			}
		} else {
			scanf("%d%d%s", &l, &r, query_str);
			int len = strlen(query_str);
			int ret = 0;
			for (int i = 0; query_str[i]; i++) {
				ret += tree[mp[query_str[i]]][(l + i) % len][len].Sum(r);
				ret -= tree[mp[query_str[i]]][(l + i) % len][len].Sum(l - 1);
			}
			printf("%d\n", ret);
		}	
	}
	return 0;
}