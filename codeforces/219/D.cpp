#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>
#define local debug
using std::set;
const int MAX_LOG = 18;
const int MAX_N = 100010;
int at[MAX_N], head[MAX_N], nxt[MAX_N*2], pnt[MAX_N*2],E;
int plca[MAX_LOG][MAX_N], dep[MAX_N], dfn, order[MAX_N];
void dfs(int u,int f) {
  dep[u] = dep[f] + 1;
  order[dfn] = u;
  at[u] = dfn++;
  plca[0][u] = f;
  for(int i = head[u]; ~i; i = nxt[i]) if(pnt[i]-f){
    dfs(pnt[i],u);
  }
}
int getlca(int a,int b) {
  if(dep[a] > dep[b]) std::swap(a,b);
  int d = dep[b] - dep[a];
  for(int i = MAX_LOG-1; i >= 0; i--) 
    if(d>>i&1)
      b = plca[i][b];
  if(a == b) return a;
  for(int i = MAX_LOG-1; i >= 0; i--)
    if(plca[i][a] != plca[i][b])
      a = plca[i][a], b = plca[i][b];
  return plca[0][a];
}
void add(int a,int b){
  pnt[E] = b;
  nxt[E] = head[a];
  head[a] = E++;
}
std::set<int> SET;
int allnodes;
int get(int a,int b,int c) {
  return dep[a] + dep[b] - 2*dep[c];
}
void addnew(int u,int flag) {
  if(flag>0&&SET.empty()) {
    SET.insert(at[u]);
    return ;
  }
  set<int>::iterator fr = SET.begin(), ed = --SET.end();
  int lca = getlca(order[*fr],order[*ed]);
  allnodes -= get(order[*fr],order[*ed],lca) ;
  if(flag > 0) SET.insert(at[u]);
  set<int>::iterator it = SET.lower_bound(at[u]),it2,it1;
  bool succ = false, pre = false;
  if(it != (--SET.end())) {
    succ = true;
    it2 = it;
    it2++;
    int lca = getlca(order[*it],order[*it2]);
    allnodes += flag * get(order[*it],order[*it2],lca) ;
  } 
  if(it != SET.begin()) {
    pre = true;
    it1 = it;
    it1--;
    int lca = getlca(order[*it1],order[*it]);
    allnodes += flag * get(order[*it],order[*it1],lca) ;
  } 
  if(pre && succ) {
    int lca = getlca(order[*it1],order[*it2]);
    allnodes += (-flag)*get(order[*it1],order[*it2],lca);
  }
  if(flag < 0) SET.erase(it);
  if(SET.empty()) return ;
  lca = getlca(order[*SET.begin()],order[*(--SET.end())]);
  allnodes += get(order[*SET.begin()],order[*(--SET.end())],lca) ;
}
int main() {
  int n, k, a, b;
  while(scanf("%d%d",&n,&k)!=EOF) {
    std::fill(head,head+n+1,-1);
    E = 0; SET.clear();
    for(int i = 1; i < n; i++) {
      scanf("%d%d",&a,&b);
      add(a,b); add(b,a);
    }
    dfn = 0;
    for(int i = 1; i < MAX_LOG; i++) 
      for(int j = 1; j <= n; j++)
        plca[i][j] = 0;
    dfs(1,0);
    for(int i = 1; i < MAX_LOG; i++) {
      for(int j = 1; j <= n; j++) {
        plca[i][j] = plca[i-1][plca[i-1][j]];
      }
    }
#ifndef local
    for(int i = 1; i < 4; i++) {
      for(int j = 1; j <= n; j++) {
        printf("plca[%d][%d]=%d\n",i,j,plca[i][j]);
      }
    }
#endif
    allnodes = 0;
    int ans = 0;
    for(int L = 1, R = 1; L <= n; L++) {
      while(R <= n && allnodes/2+1<= k) {        
        ans = std::max(ans,R-L);
        addnew(R++,1);
      }
      if(R > n) {
        if(allnodes/2+1 <= k) ans = std::max(ans,R-L);
        break;
      }
      addnew(L,-1);
    }
    printf("%d\n",ans);
  }
  return 0;
}
