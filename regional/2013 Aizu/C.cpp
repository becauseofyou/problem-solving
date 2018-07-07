#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using std::vector;
using std::sort;
using std::min;
using std::unique;
using std::max;
using std::lower_bound;
struct Point {
        double x, y;
        Point(double x = 0, double y = 0) : x(x), y(y) {}
        void print() {
                printf("x=%lf y=%lf\n",x,y);
        }
        void in() {
                scanf("%lf%lf",&x, &y);
        }
};
inline int sgn(double x, double eps = 1e-8) {
        return x < -eps ? -1 : x > eps;
}
bool operator < (const Point &a, const Point &b) {
        return sgn(a.x - b.x) < 0 || sgn(a.x - b.x) == 0 && sgn(a.y - b.y) < 0;
}
bool operator == (const Point &a, const Point &b) {
        return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0;
}
struct Rec {
        Point a, b;
        void in() {
                a.in();
                b.in();
        }
}rec[55];
struct Seg {
        Point s, e;
        Seg() {
        }
        Seg(Point _s, Point _e) {
                s = _s;
                e = _e;
        }
        bool operator < (const Seg& cmp) const  {
                if(s.y == e.y) {
                        if(s.y != cmp.s.y) return s.y < cmp.s.y;
                        return s.x < cmp.s.x;
                }
                if(s.x == e.x) {
                        if(s.x != cmp.s.x) return s.x < cmp.s.x;
                        return s.y < cmp.s.y;
                }
        }
        bool operator == (const Seg& cmp) const {
                return s == cmp.s && e == cmp.e;
        }
};       
vector<Point> pt;
vector<Seg> chuizhi;
vector<Seg> shuiping;
int n;
bool intersect(Seg shuiping, Seg chuizhi) {
        double x1 = min(shuiping.s.x, shuiping.e.x);
        double x2 = max(shuiping.s.x, shuiping.e.x);
        double y1 = min(chuizhi.s.y, chuizhi.e.y);
        double y2 = max(chuizhi.s.y, chuizhi.e.y);
        return chuizhi.s.x >= x1 && chuizhi.s.x <= x2 && shuiping.s.y >= y1 && shuiping.s.y <= y2;
}
void gao(Seg a, Seg b, vector<double> &x) {
        double x1 = min(a.s.x, a.e.x), x2 = max(a.s.x, a.e.x);
        double x3 = min(b.s.x, b.e.x), x4 = max(b.s.x, b.e.x);
        if(x3 >= x1 && x3 <= x2) {
                x.push_back(x3);
        }
        if(x4 >= x1 && x4 <= x2) {
                x.push_back(x4);
        }
}
void gao2(Seg a, Seg b, vector<double> &y) {
        double y1 = min(a.s.y, a.e.y), y2 = max(a.s.y, a.e.y);
        double y3 = min(b.s.y, b.e.y), y4 = max(b.s.y, b.e.y);
        if(y3 >= y1 && y3 <= y2) {
                y.push_back(y3);
        }
        if(y4 >= y1 && y4 <= y2) {
                y.push_back(y4);
        }
}
vector<Seg> ss1, ss2;
int fa[100010];
int find(int x) {
        return fa[x] == x ? x : find(fa[x]);
}
void Unio(Point s, Point e) {
        int id1 = lower_bound(pt.begin(), pt.end(), s) - pt.begin();
        int id2 = lower_bound(pt.begin(), pt.end(), e) - pt.begin();
        int x1 = find(id1);
        int y1 = find(id2);
        if(x1 != y1) {
                fa[x1] = y1;
        }
}
int main() {
        while(scanf("%d",&n) == 1) {
                if(!n) {
                        break;
                }
                pt.clear();
                chuizhi.clear();
                shuiping.clear();
                ss1.clear();
                ss2.clear();
                for(int i = 0; i < 100000; i++) fa[i] = i;
                for(int i = 0; i < n; i++) {
                        rec[i].in();
                        chuizhi.push_back(Seg(rec[i].a, Point(rec[i].a.x, rec[i].b.y)));
                        chuizhi.push_back(Seg(rec[i].b, Point(rec[i].b.x, rec[i].a.y)));
                        shuiping.push_back(Seg(rec[i].a, Point(rec[i].b.x, rec[i].a.y)));
                        shuiping.push_back(Seg(rec[i].b, Point(rec[i].a.x, rec[i].b.y)));
                }
                int E = 0;
                for(int i = 0; i < shuiping.size(); i++) {
                        vector<double> x;
                        x.push_back(shuiping[i].s.x);
                        x.push_back(shuiping[i].e.x);
                        for(int j = 0; j < chuizhi.size(); j++) {
                                if(intersect(shuiping[i], chuizhi[j])) {
                                        x.push_back(chuizhi[j].s.x);
                                }
                        }
                        for(int j = 0; j < shuiping.size(); j++) if(j != i && shuiping[j].s.y == shuiping[i].s.y){
                                gao(shuiping[i], shuiping[j], x);
                        }
                        sort(x.begin(), x.end());
                        x.erase(unique(x.begin(), x.end()), x.end());
                        double y = shuiping[i].s.y;
                        for(int j = 0; j < x.size(); j++) {
                                pt.push_back(Point(x[j], y));
                                if(j) {
                                        ss1.push_back(Seg (Point(x[j-1], y), Point(x[j], y)) );
                                }
                        }
                }
                for(int i = 0; i < chuizhi.size(); i++) {
                        vector<double> y;
                        y.push_back(chuizhi[i].s.y);
                        y.push_back(chuizhi[i].e.y);
                        for(int j = 0; j < shuiping.size(); j++) {
                                if(intersect(shuiping[j], chuizhi[i])) {
                                        y.push_back(shuiping[j].s.y);
                                }
                        }
                        for(int j = 0; j < chuizhi.size(); j++) if(j != i && chuizhi[j].s.x == chuizhi[i].s.x){
                                gao2(chuizhi[i], chuizhi[j], y);
                        }
                        sort(y.begin(), y.end());
                        y.erase(unique(y.begin(), y.end()), y.end());
                        double x = chuizhi[i].s.x;
                        for(int j = 0; j < y.size(); j++) {
                                pt.push_back(Point(x, y[j]));
                                if(j) {
                                        ss2.push_back(Seg (Point(x, y[j-1]), Point(x, y[j])));
                                }
                        }
                }
                sort(ss1.begin(), ss1.end());
                ss1.erase(unique(ss1.begin(), ss1.end()), ss1.end());
             /*   for(int i = 0; i < ss1.size(); i++) {
                        ss2[i].s.print();
                        ss2[i].e.print();
                        puts("");
                }*/
                sort(ss2.begin(), ss2.end());
                ss2.erase(unique(ss2.begin(), ss2.end()), ss2.end());
                E += ss1.size() + ss2.size();
                sort(pt.begin(), pt.end());
                pt.erase(unique(pt.begin(), pt.end()), pt.end());
                for(int i = 0; i < ss1.size(); i++) {
                        Point s = ss1[i].s;
                        Point e = ss1[i].e;
                        Unio(s, e);
                }
                for(int i = 0; i < ss2.size(); i++) {
                        Point s = ss2[i].s;
                        Point e = ss2[i].e;
                        Unio(s, e);
                }
                int V = pt.size();
                int comp = 0;
                for(int i = 0; i < pt.size(); i++) {
                        if(find(i) == i) comp++;
                }
            //    printf("%d %d %d\n",ss2.size(), V,E);
                printf("%d\n", comp + 1 - V + E);
        }
        return 0;
}

