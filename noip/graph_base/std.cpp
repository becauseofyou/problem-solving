#include<cstdio>
#include<string.h>
#include<algorithm>
#include<ext/pb_ds/priority_queue.hpp>
#define LL long long 
using namespace std;
typedef pair<long long , int > pii;
using namespace __gnu_pbds;
typedef __gnu_pbds::priority_queue <pii,  greater<pii >, pairing_heap_tag > heap;
 heap::point_iterator b[1000005];
const int MAX=1e8;
const long long LENMAX=2e18;
struct node{
	int u,to;
	LL w;
}edge[10000100];
int head[1000010],len,k,rxa,rxc,rya,ryc,n,m,t,rp;
LL dist[1000010];
void add(int x,int y,int z)
{
	edge[k].u=y;
	edge[k].to=head[x];
	edge[k].w=z;
	head[x]=k++;
}
int read()
{
   int sum=0,f=1;char x=getchar();
    while(x<'0'||x>'9')f=(x=='-')?-1:1,x=getchar();
    while(x>='0'&&x<='9')sum=(sum<<3)+(sum<<1)+x-'0',x=getchar();
    return sum*f;
}
void dij()
{
	for (int i=1;i<=n;i++) dist[i]=LENMAX;
	heap q;
	dist[1]=0;
	b[1]=q.push(make_pair(0,1));
	while (!q.empty())
	{
		 int t=q.top().second; q.pop();
		for (int i=head[t];i!=-1;i=edge[i].to)
		{
			int u=edge[i].u;
			if (dist[u]>dist[t]+edge[i].w)
			{
				dist[u]=dist[t]+edge[i].w; 
				if (b[u]==0) {
					b[u]=q.push(make_pair(dist[u],u));
				}
				else q.modify(b[u],make_pair(dist[u],u));
			}
		}
	}
}
int main()
{
	//freopen("tyy.in","r",stdin);
	//freopen("tyy.out","w",stdout);
	scanf("%d%d",&n,&m);
	scanf("%d%d%d%d%d%d",&t,&rxa,&rxc,&rya,&ryc,&rp);
	memset(head,-1,sizeof(head));
	int x,y,z;
	x=0; y=0; z=0;
	int A,B;
	for (int i=1;i<=t;i++)
	{
		x=((LL)x*rxa+rxc)%rp;
		y=((LL)y*rya+ryc)%rp;
		A = min(x%n+1, y%n+1);
		B = max(y%n+1, y%n+1);
		add(A,B,MAX-100*A);
	}
	for (int i=1;i<=m-t;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
	}
	dij();
	printf("%lld",dist[n]);
//	fclose(stdin);
//	fclose(stdout);
 }
