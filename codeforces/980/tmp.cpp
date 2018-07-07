#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int n,m,in[N],out[N],rem,lol,at[N],L[N],mx[N],Z[N],p[N];
vector<pair<int,int>>g[N];
vector<int>comp[N];
bool is[N],vis[N];
void dfs(int u,int p){
	in[u] = out[u] = ++rem;
	for(auto i : g[u]){
		int x = i.first,y = i.second;
		if(!in[x]){
			dfs(x,u);
			out[u] = min(out[x],out[u]);
			if(out[x] > in[u])is[y] = 1;
		}
		else if(i.first != p)out[u] = min(out[u],in[x]);
	}
}
void compress(int u,int to){
	comp[to].push_back(u);
	vis[u] = 1;at[u] = to;
	for(auto i : g[u])
		if(!vis[i.first] && !is[i.second])
			compress(i.first,to);
}
void bfs(){
	queue<int>q;
	vector<int>dis;
	q.push(0);
	p[0] = -1;
	memset(vis,0,sizeof vis);
	vis[0] = 1;
	while(!q.empty()){
		int x = q.front();
		dis.push_back(x);
		q.pop();
		for(auto i : g[x])
			if(!vis[i.first]){
				p[i.first] = x;
				vis[i.first] = 1;
				q.push(i.first);
			}
	}
	for(int i = n - 1;i + 1;i--){
		int x = dis[i];
		for(auto j : g[x])
			if(p[j.first] == x){
				mx[x] = max(mx[x],mx[j.first] + 1);
				if(is[j.second])L[x] = max(L[x],mx[j.first] + 1);
			}
	}
}
void solve(int u,int rev){
	L[u] = max(L[u],rev);
	vector<int>&comp = ::comp[at[u]];
	int sz = comp.size();
	for(int turn = 0;turn < 2;turn++){
		priority_queue<pair<int,int>>q;
		for(int i = 0;i < 2*sz;i++){
			int id = comp[i%sz],val = L[id] - i;
			while(q.size() && q.top().second + i > sz/2)q.pop();
			if(q.size())Z[id] = max(Z[id],q.top().first + i);
			while(q.size() && val >= q.top().first)q.pop();
			q.push({val,-i});
		}
		reverse(comp.begin(),comp.end());
	}
	for(int i : comp){
		int f = 0,s = 0,p = ::p[i];
		for(auto j : g[i])
			if(p != j.first && is[j.second]){
				s = max(s,mx[j.first] + 1);
				if(s > f)swap(s,f);
			}
		for(auto j : g[i])
			if(p != j.first && is[j.second]){
				int val = max(rev,Z[i]);
				if(mx[j.first] + 1 == f)val = max(val,s);
				else val = max(val,f);
				solve(j.first,val + 1);
			}
	}
}
int main(){
// 	freopen("input.txt","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i = 0,a,b;i < m;i++){
		scanf("%d%d",&a,&b);
		g[--a].push_back({--b,i});
		g[b].push_back({a,i});
	}
	dfs(0,-1);
	for(int i = 0;i < n;i++)
		if(!vis[i])compress(i,lol++);
	bfs();
	solve(0,0);
	for(int i = 0;i < n;i++)printf("%d ",max(L[i],Z[i]));
}