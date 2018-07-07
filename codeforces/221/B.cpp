#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
char s[5010];
std::vector<int> E[5010];
int cnt[5010], sum[5010];
int main() 
{
  int n,m;
  scanf("%d%d",&n,&m);
  for(int i = 0; i < n; i++)  
  {
    scanf("%s",s);
    for(int j = 0; j < m; j++) if(s[j] == '1') 
    {
      int k;
      for(k = j + 1; s[k] == '1'; k++);
      for(int x = j; x < k; x++) E[x].push_back(k - x);
      j = k;
    }
  }
  int ans = 0;
  for(int i = 0; i < m; i++)  if((int)E[i].size() > 0)
  {
    memset(cnt,0,sizeof(cnt));
    int sz = E[i].size();
    for(int j = 0; j < sz; j++) cnt[E[i][j]]++;
    sz = 0;
    for(int j = 1; j <= 5000; j++) 
      for(int k = 0; k < cnt[j]; k++)
        E[i][sz++] = j;
    for(int j = 0; j < sz; j++) 
      ans = std::max(ans,E[i][j]*(sz-j));
  }
  printf("%d\n",ans);
  return 0;
}