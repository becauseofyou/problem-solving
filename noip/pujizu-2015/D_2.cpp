#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
struct home{
    int s,v;
}a[100010];
int q[100010];
int h[100010],qm[100010];
int n;
bool cmp(home a,home b)
{
    return a.v>b.v;
}
int main()
{
    scanf("%d",&n);
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i].s);
    }
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i].v);
    }
    sort(a+1,a+1+n,cmp);
    for (int i=n;i>=1;i--)
    {
        h[i]=max(h[i+1],2*a[i].s+a[i].v);
    }
    for (int i=1;i<=n;i++)
    {
        qm[i]=max(qm[i-1],a[i].s);
    }
    for (int i=1;i<=n;i++)
        q[i]=q[i-1]+a[i].v;
    for (int i=1;i<=n;i++)
    {
        printf("%d\n",max(q[i-1]+h[i],q[i]+2*qm[i]));
    }
} 
