#include<bits/stdc++.h>
using namespace std;
const int INF=40001;
int n,m,sx,sy,mx,my;
int dir[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
char a[211][211];
queue<int> q;
bool vis[211][211],vis1[211][211];
int bfs(int x,int y)
{
 q.push(x);
 q.push(y);
 q.push(0);
 vis[x][y]=1;
 while(!q.empty())
 {
  int X=q.front();
  q.pop();
  int Y=q.front();
  q.pop();
  int S=q.front();
  q.pop();
  //cout<<X<<" "<<Y<<" "<<S<<endl;
  if(a[X][Y]=='G')
  {
   q.push(X);
   q.push(Y);
   q.push(S+1);
   a[X][Y]='.';
   continue;
  }
  for(int i=0;i<4;i++)
  {
   int xx=X+dir[i][0],yy=Y+dir[i][1];
   if(a[xx][yy]!='#'&&xx<=n&&yy<=m&&xx>=1&&yy>=1&&!vis[xx][yy])
   {
    q.push(xx);
    q.push(yy);
    q.push(S+1);
    if(xx==mx&&yy==my)
    {
     return S+1;
    }
    vis[xx][yy]=1;
   }
  }
 }
 return INF;
}
int main()
{
 cin>>n>>m;
 for(int i=1;i<=n;i++)
 {
  for(int j=1;j<=m;j++)
  {
   cin>>a[i][j];
   if(a[i][j]=='@')
   {
    sx=i;
    sy=j;
   }
   if(a[i][j]=='M')
   {
    mx=i;
    my=j;
   }
  }
 }
 if(bfs(sx,sy)==INF) cout<<"You can't save Mengxin"<<endl;
 else cout<<bfs(sx,sy);
 return 0;
}
/*
3 3
@#.
.#.
#GM

4 4
@GGM
.##.
....
....

1 1 0
2 1 1
1 2 1
3 1 2
1 2 2
4 1 3
3 2 3
1 3 3
4 2 4
3 3 4
1 3 4
4 3 5
3 4 5
1 4 5
1 1 0
4 4 6
2 4 6
*/