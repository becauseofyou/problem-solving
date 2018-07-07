#include <bits/stdc++.h>
using namespace std;

const int MAX_QUERY = 100010;
const int MOD = 1234577;

struct hash_table
{
	int head[MOD];
	int nxt[MAX_QUERY];
	int pnt[MAX_QUERY];
	int E;
	void init () {
		E = 0;
		memset(head, -1, sizeof(head));
	}

	void insert(int number) {
		int h = number % MOD; // 常见的取模哈希函数
		for (int i = head[h]; i != -1; i = nxt[i]) {
			if (pnt[i] == number) {
				return ;
			}
		}
		pnt[E] = number;
        nxt[E] = head[h];
		head[h] = E++;
	}
	bool find(int number) {
		int h = number % MOD;
		for (int i = head[h]; i != -1; i = nxt[i]) {
			if (pnt[i] == number) {
				return true;
			}
		}
        return false;
	}
};

