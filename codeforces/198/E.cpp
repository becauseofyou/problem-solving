// I hate constructive algorithm, it's a big challenge for my IQ
#include <cstdio>
#include <vector>
#include <algorithm>
using std::vector;
using std::pair;
using std::make_pair;
int ans;
pair<int,int> a[1000];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i = 0; i < n; i++) scanf("%d",&a[i].first),a[i].second=i;
    std::sort(a,a+n);
    if(a[n-2].first==0) return puts("-1"),0;
    int now = n-3;
    vector<pair<int,int> > b,c,step;
    b.push_back(a[n-1]);
    b.push_back(a[n-2]);
    while(now>=0) 
    {
        int A,B,C;
        c = b;
        b.clear();
        for(int i = 0; i < 3; i++) 
               if(c[i].first != 0) 
                     b.push_back(c[i]);
        b.push_back(a[now]);
        while(true) 
        {
            std::sort(b.begin(),b.end());
            if(b[0].first == 0 || b[0].first == b[1].first)
            {
                if(b[0].first == b[1].first)
                        ans++,step.push_back(make_pair(b[0].second,b[1].second)),b[1].first=0,b[0].first*=2;
                break;
            }
            int A = b[0].first, A_id = b[0].second;
            int &B = b[1].first, B_id = b[1].second;
            int &C = b[2].first, C_id = b[2].second;

            int p = B / A;
            for(int i = 0;(1<<i) <= p; i++) 
                if(p&(1<<i))
                    ans++,step.push_back(make_pair(A_id,B_id)),B-=A*(1<<i),b[0].first*=2;
                else 
                    ans++,step.push_back(make_pair(A_id,C_id)),C-=A*(1<<i),b[0].first*=2;
        }
        now--;
    }
    printf("%d\n",ans);
    for(int i = 0; i < ans; i++)
        printf("%d %d\n",step[i].first+1,step[i].second+1);
}
