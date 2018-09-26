#include <bits/stdc++.h>
using namespace std;

const int N = 500010;
const long long inf = (long long)1e9;

long long f[N][3];// 0不删，1先于爸爸删，2后于爸爸删
vector <int> e[N];
int k;

long long get(vector <long long> &v, int k) {
    int cnt = 0;
    long long s = 0;
    for (auto it = v.rbegin(); it != v.rend(); it++) {
        cnt ++;
        s += *it;
        if (cnt == k) break;
    }
    return s;
}

void check(long long &x) {
	if (x < 0) {
		x = -inf;
	}
}

void dfs(int u, int fa) {
    long long sum = 0;
    long long sum2 = 0;
    vector <long long> vec;
    for (int v : e[u]) if (v != fa){
        dfs(v, u);
        sum += max(f[v][0], f[v][1]);
        
        sum2 += f[v][1];// 把非法的也会加进来,只需要检查最后结果是否是负数就行了
        vec.push_back(max(f[v][0], f[v][2]) - f[v][1]);
    }
    f[u][0] = sum;    
    f[u][1] = sum2 + 1;    
    f[u][2] = sum2 + 1;
    
    sort(vec.begin(), vec.end());
    if ((int)vec.size() < k - 1) {
    	f[u][1] = -inf;
    } else {
    	f[u][1] += get(vec, k - 1);
    }

	if ((int)vec.size() < k) {
		f[u][2] = -inf;
	} else {
		f[u][2] += get(vec, k);
	}
 
	check(f[u][1]); check(f[u][2]); //非法的状态统一置为-inf
}

int main() {
    int n, a, b;
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &a, &b);
        a--; b--;
        e[a].push_back(b);
        e[b].push_back(a);
    }
    dfs(0, -1);
    printf("%lld\n", max(f[0][0], f[0][2]));
    return 0;
}
