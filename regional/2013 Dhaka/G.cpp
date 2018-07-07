#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

const int N = 101000;

#define mp make_pair
#define pb push_back
typedef pair<int,int> PII;

PII dot[N],B[N],D[N];
int n,m,ans[N],A[N],C[N];

void work(int *A,PII *B) {
	int pa = 0,pb = 0;
	multiset<int> Set;
	for (int i = 0; i < m; i ++) {
		int v = dot[i].first;
		int id = dot[i].second;
		while (pa<n && A[pa]<=v) {
			Set.insert(A[pa]);
			pa ++;
		}
		while (pb<n && B[pb].first<v) {
			multiset<int>::iterator it = Set.find(B[pb].second);
			Set.erase(it);
			pb ++;
		}
		if (!Set.empty()) {
			int val = v - *Set.begin();
			ans[id] = max(ans[id],val);
		}
	}
}

int main() {
	int cas,ca = 0;
	scanf("%d",&cas);
	while (cas--) {
		scanf("%d%d",&n,&m);
		for (int i = 0; i < n; i ++) {
			int l,r;
			scanf("%d%d",&l,&r);
			int mid = l+r>>1;
			A[i] = l;
			B[i] = mp(mid,l);
			C[i] = -r;
			D[i] = mp(-mid-1,-r);
		}
		sort(A,A+n);
		sort(B,B+n);
		sort(C,C+n);
		sort(D,D+n);
		for (int i = 0; i < m; i ++) {
			scanf("%d",&dot[i].first);
			dot[i].second = i;
			ans[i] = 0;
		}
		sort(dot,dot+m);
		work(A,B);
		reverse(dot,dot+m);
		for (int i = 0; i < m; i ++) {
			dot[i].first *= -1;
		}
		work(C,D);
		printf("Case %d:\n",++ca);
		for (int i = 0; i < m; i ++) {
			printf("%d\n",ans[i]);
		}
	}
	return 0;
}