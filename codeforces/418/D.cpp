#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-7;
const double pi = acos(-1.0);
int sgn(double x) {
  return x < -eps ? -1 : x > eps;
}
struct Circle{
  int x, y, r;
  void in () {
    scanf("%d%d%d", &x, &y, &r);
  }
}c[1010];
double dist(int x1, int y1, int x2, int y2) {
  return sqrt(1.0*(x1-x2)*(x1-x2) + 1.0*(y1-y2)*(y1-y2));
}

bool Inside(Circle a, Circle b) {
  return sgn(dist(a.x, a.y, b.x, b.y) - (b.r - a.r) ) <= 0;
}

vector<int> edge[1010];
int in[1010];

double ret;
void dfs(int u, int dep) {
  if(dep <= 1) {
    ret += pi * c[u].r * c[u].r ;
  } else {
    ret += pi * c[u].r * c[u].r * ((dep&1) ? 1 : -1);
  }
  for(int v : edge[u]) {
    dfs(v, dep + 1);
  }
}
int main() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n; i++) { 
    c[i].in();
  }
  for(int i = 0; i < n; i++) {
    int id = -1;
    double r = 0;
    for(int j = 0; j < n; j++) if(i != j) {
      if(Inside(c[i], c[j])) {
        if(id == -1 || sgn(c[j].r - r) < 0) {
          id = j;
          r = c[j].r;
        }
      }
    }
    if(id != -1) {
      edge[id].push_back(i);
      in[i]++;
    }
  }
  ret = 0;
  for(int i = 0; i < n; i++) if(!in[i]){
    dfs(i, 0);
  }
  printf("%.9f\n", ret);
  return 0;
}