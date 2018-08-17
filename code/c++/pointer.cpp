#include <bits/stdc++.h>
using namespace std;

int x;

//形式参数
void add(int a, int b) {
    a = 10;
    b = 20;
}


void change(int *b) { // int b[]
    for (int i = 0; i < 10; i++) {
        *b = 2;
        b++;
    }
}


void ss(char *s) {
    
    puts(s);

    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        printf("%c", s[i]);
    }

    puts("");
    for (;*s;s++) {
        printf("%c", *s);
    }
}

void go (int* p) {
    *p = 3;
}

void change_array(int arr[][10])
{
}



int main() {
    //作用域
    /*{
        int a = 10;
        int* p = &a;
        cout << *p << endl;
    }*/

/*    {
        int a[10];
        memset(a, 0, sizeof(a));
        change(a);

        for (int i = 0; i < 10; i++) {
            printf("%d ", a[i]);
        }
    }*/

    /*{
        char s[10] = "abcde";
        ss(s);
    }*/

    /*{
        int a[10][10];
        memset(a, -1, sizeof(a));
        change_array(a);
    }*/

    {
        int x;
        int &y = x;
        y = 20;
        cout << x << endl;
    }
    return 0;
}
