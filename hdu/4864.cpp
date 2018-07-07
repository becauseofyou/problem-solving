#include <bits/stdc++.h>
using namespace std;

vector <int> task[1444];
vector <int> machine[1444];

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        int x, y;
        for (int i = 0; i <= 1440; i++) {
            machine[i].clear();
            task[i].clear();
        }
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &x, &y);
            machine[x].push_back(y);
        }
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &x, &y);
            task[x].push_back(y);
        }
        for (int i = 0; i <= 1440; i++) {
            sort(task[i].begin(), task[i].end());
        }
        multiset <int> st;
        int cnt = 0;
        long long value = 0;
        for (int i = 1440; i >= 0; i--)  {
            for (auto it: machine[i]) {
                st.insert(it);
            }
            int sz = (int) task[i].size();
            for (int j = sz - 1; j >= 0; j--) {
                int it = task[i][j];
                auto it2 = st.lower_bound(it);
                if(it2 != st.end()){
                    st.erase(it2);
                    cnt++;
                    value += i * 500 + 2 * it;
                }
            } 
        }
        cout << cnt << " " << value << endl;
    }
    return 0;
}



