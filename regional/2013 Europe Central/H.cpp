#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int inf = 1 << 30;
struct point {
    int a[3];
    int b[3];
    void in() {
        for(int i = 0; i < 3; i++) {
            scanf("%d", &a[i]);
        }
        for(int i = 0; i < 3; i++) {
            scanf("%d", &b[i]);
            if(a[i] > b[i]) {
                swap(a[i], b[i]);
            }
        }
    }
    void rot() {
        rotate(a, a + 1, a + 3);
        rotate(b, b + 1, b + 3);
    }
};
bool gao(vector<point>&p1, vector<point>&p2, int x, int y, int z) {
    int xmin = inf, xmax = -inf;
    int ymin = -inf, ymax = inf;
    int zmin = -inf, zmax = inf;
    for(int i = 0; i < p1.size(); i++) {
        xmin = min(xmin, p1[i].a[x]);
        xmax = max(xmax, p1[i].a[x]);

        ymin = max(ymin, p1[i].a[y]);
        ymax = min(ymax, p1[i].b[y]);

        zmin = max(zmin, p1[i].a[z]);
        zmax = min(zmax, p1[i].b[z]);
    }
 //   printf("%d %d\n %d %d\n", ymin, ymax, xmin, xmax);
    for(int i = 0; i < p2.size(); i++) {
        int x1 = p2[i].a[x], x2 = p2[i].b[x];
        int y1 = p2[i].a[y], y2 = p2[i].b[y];
        int z1 = p2[i].a[z], z2 = p2[i].b[z];
        if(x1 < xmin && x2 > xmax && z1 > zmin && z1 < zmax && (y1 > ymin && y1 < ymax || y2 > ymin && y2 < ymax))
            continue;
        return false;
    }
    return true;
}
vector<point> plane1, plane2, plane3;
int main() {
    int n, T;
    scanf("%d", &T);
    while(T--) {
        plane1.clear();
        plane2.clear();
        plane3.clear();
        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            point tmp;
            tmp.in();
            if(tmp.a[0] == tmp.b[0]) {
                plane1.push_back(tmp);
            } else if(tmp.a[1] == tmp.b[1]) {
                plane2.push_back(tmp);
            } else {
                plane3.push_back(tmp);
            }
        }
        bool flag = false;
        for(int i = 0; i < 3; i++) {
     //       printf("%d %d %d\n", plane1.empty(), plane2.empty(), plane3.empty());
            if(!plane1.empty() && (!plane2.empty() || !plane3.empty() ) &&  gao(plane1, plane2, 0, 2, 1) && gao(plane1, plane3, 0, 1, 2)) {
                flag = true;
                break;
            }
            for(int j = 0; j < plane1.size(); j++) {
                plane1[j].rot();
            }
            for(int j = 0; j < plane2.size(); j++) {
                plane2[j].rot();
            }
            for(int j = 0; j < plane3.size(); j++) {
                plane3[j].rot();
            }
            plane1.swap(plane2);
            plane2.swap(plane3);
        }
        printf("%s\n",flag ? "YES" : "NO");
    }
    return 0;
}