#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 100010;
int num[maxn];
int lis[maxn];
int n;
int solve()
{
	int len = 0,idx;
	lis[len++] = -1;
	for(int i=0;i<n;i++){
		idx = lower_bound(lis,lis+len,num[i])-lis;//求最长上升
		if(idx == len)  lis[len++] = num[i];
		else 	  lis[idx] = num[i];
	}
	return len - 1;
}
int main() {
    scanf("%d",&n);
    for(int i = 0; i < n; i++) scanf("%d",&num[i]);
    printf("%d\n",solve());
    return 0;
}
