#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int price[8] = {
        319,419,450,519,599,600,630,719
};
int a[8] = {
        1024,1024,960,2048,1136,1280,1080,1136
};
int b[8] = {
        768,600,640,1536,640,800,1920,640
};

int calc(int xx,int yy,double x,double y,double a,double b) {
        if (x>a || y>b) return 0;
        return xx*yy;
}

int get(int a,int b,double x,double y) {
        return max(calc(a,int(a*y/x),a,a*y/x,a,b),calc(int(b*x/y),b,b*x/y,b,a,b));
}

int work(int x,int y) {
        int ret = 0;
        double mx = 0;
        for (int i = 0; i < 8; i ++) {
                double val = (double)max(get(a[i],b[i],x,y),get(a[i],b[i],y,x))/a[i]/b[i];
                if (val>mx) {
                        mx = val;
                        ret = price[i];
                }
        }
        return ret;
}

int main() {
        int h,w;
        while (scanf("%d%d",&h,&w)==2 && h) {
                printf("%d\n",work(h,w));
        }
        return 0;
}

