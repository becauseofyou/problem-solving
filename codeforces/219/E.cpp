#include <cstdio>
#include <cmath>
#include <map>
#include <algorithm>
using std::map;
const double eps = 1e-8;
const int mod = 1000000007;
struct point {
  double x,y;
  point(double x = 0,double y = 0):x(x),y(y){}
  void in(){
    int a,b,c,d;
    scanf("%d%d%d%d",&a,&b,&c,&d);
    x = double(a) / b, y = double(c) / d;
  }
  double len2(){
    return x * x + y * y;
  }
  double angle() {
    return atan2(y,x);
  }
}p[1010];
point operator + (const point &a,const point &b) {
  return point(a.x + b.x, a.y + b.y);
}
point operator - (const point &a,const point &b) {
  return point(a.x - b.x, a.y - b.y);
}
point operator / (const point &a, double t) {
  return point(a.x / t, a.y / t);
}
int sgn(double x) {
  return x < -eps ? -1 : x > eps ;
}
bool operator == (const point &a,const point &b) {
  return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0;
}
bool operator < (const point &a, const point &b) {
  return sgn(a.x - b.x) < 0 || sgn(a.x - b.x) == 0 && sgn(a.y - b.y) < 0;
}
point inverse(point a) {
  return a / a.len2();
}
struct Seg{
  point midp;
  double angle;
  Seg(){}
  Seg(point midp,double angle):midp(midp),angle(angle){}
};
bool operator < (const Seg &a, const Seg &b) {
  return a.midp < b.midp || a.midp == b.midp && sgn(a.angle - b.angle) < 0;
}
map<Seg,int> mp;
int main() {
  int n;
  while(scanf("%d",&n)!=EOF) {
    for(int i = 0; i < n; i++){
      p[i].in();
      p[i] = inverse(p[i]);
    }
    std::sort(p,p+n);
    mp.clear();
    for(int i = 0; i < n; i++) {
      for(int j = i + 1; j < n; j++) {
        mp[Seg((p[i]+p[j])/2,(p[i]-p[j]).angle())]++;
      }
    }
    long long ans = 0;
    for(map<Seg,int>::iterator it = mp.begin(),it2; it != mp.end(); it=it2) {
      long long s = 1, tot = 0;
      for(it2 = it; it2 != mp.end() && it->first.midp == it2->first.midp; it2++) {
        s = s * (it2->second + 1) % mod;
        tot += it2->second;
      }
      ans += s - tot - 1;
      ans %= mod;
    }
    printf("%I64d\n",ans);
  }
  return 0;
}
