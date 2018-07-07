/*
 相同长度的字符串建字典树，正 反各建一次
 预处理的时候枚举模式串的每一个位置，删除，查找前缀 后缀对应在字典树中的节点
 组成一个pair <A B> ，询问的时候枚举每一个位置删除， 用相同的方法在字典树中查找前后缀
 在字典树中的节点C D，如果这个pair出现过，就表示模式串中有一个串除了这个位置外都与当前串相同。

 这里有个小坑，就是模式串中既有完全相等的，又有仅有一个位置不相等的，所以要记录一下每一个pair
 是可以通过删除哪些字符得来的
 复杂度为大概字符串长度 len * log(len)
 */
#include <bits/stdc++.h>
using namespace std;

#define Clr(a, v) memset(a, v, sizeof(a))

const int N = 600010;
int n, m;
int ch[N][3];
int value[N];
int rootPrefix[N];
int rootSuffix[N];
int sz;

int Insert(int &root, char *s) {
    if(root == -1) {
        root = ++sz;
    }
    int p = root;
    for(; *s; s++) {
        int c = *s - 'a';
        if(!ch[p][c]) {
            ch[p][c] = ++sz;
        }
        p = ch[p][c];
    }
    value[p] = 1;
    return p;
}

bool Find(int root, char *s, vector<int> &v) {
    int p = root;
    for(; *s; s++) {
        v.emplace_back(p);
        if(p == -1) continue;
        int c = *s - 'a';
        if(!ch[p][c]) {
            p = -1;
            continue;
        }
        p = ch[p][c];
    }
    v.emplace_back(p);
    if(p == -1 || !value[p]) return false;
    return true;
}

char s[N], t[N];
map<pair<int, int>, int> mp;
vector<string> str;

int main() {
   // freopen("C.in", "r", stdin);
    scanf("%d%d", &n, &m);
    Clr(rootPrefix, -1);
    Clr(rootSuffix, -1);

    for(int i = 0; i < n; i++) {
        scanf("%s", s);
        str.push_back(s);
        strcpy(t, s);
        int len = strlen(s);
        reverse(t, t + len);
        Insert(rootPrefix[len], s);
        Insert(rootSuffix[len], t);
        vector<int> v0, v1;
        Find(rootPrefix[len], s, v0);
        Find(rootSuffix[len], t, v1);
        for(int j = 0; j < len; j++) {
            pair<int, int> pp = make_pair(v0[j], v1[len - 1 - j]);
            if(mp.count(pp) ) {
                mp[pp] |= 1 << (s[j]-'a') ;
            } else {
                mp[pp] = 1 << (s[j]-'a') ;
            }
        }
    }
    for(int i = 0; i < m; i++) {
        scanf("%s", s);
        strcpy(t, s);
        int len = strlen(s);
        reverse(t, t + len);
        vector<int> v0, v1;
        Find(rootPrefix[len], s, v0);
        Find(rootSuffix[len], t, v1);
        bool flag = false;
        for(int j = 0; j < len; j++) {
            pair<int, int> pp = make_pair(v0[j], v1[len - 1 - j]);
            if(mp.find(pp) != mp.end() && (mp[pp] ^ (1 << (s[j]-'a')) )) {
                flag = true;
                break;
            }
        }
        if(flag) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
    return 0;
}
