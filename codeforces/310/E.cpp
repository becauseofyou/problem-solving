#include <bits/stdc++.h>
using namespace std;

int n, q;
map<int, char> direction;
map<int, int> answer;
map<int, int> row;
int main () {
    scanf("%d%d", &n, &q);
    long long ret = 0;
    int x, y; char dir[3];
    set <int> event;
    for (int i = 0; i < q; i++) {
        scanf("%d%d%s", &y, &x, dir);
        if (direction.find(y) != direction.end()) {
            printf("0\n");
            continue;
        }
        int ret = -1;
        if (dir[0] == 'U') {
            // find the first event to the right 
            auto firstEvent = event.upper_bound(y);
            if(firstEvent == event.end()) {
                ret = x;
            } else {
                if (direction[*firstEvent] == 'U') {
                   ret = answer[*firstEvent] + x - row[*firstEvent];
                } else {
                    ret = x - row[*firstEvent];
                }
            }
        } else {
            // find the first event to the left
            if ((int)event.size() == 0) {
                ret = y;
            } else {
                auto firstEvent = event.upper_bound(y);
                if (firstEvent == event.begin()) {
                    ret = y;
                } else {
                    --firstEvent;
                    if (direction[*firstEvent] == 'U') {
                        ret = y - *firstEvent;
                    } else {
                        ret = answer[*firstEvent] + y - *firstEvent;
                    }
                }
            }
        }
        row[y] = x;
        event.insert(y);
        direction[y] = dir[0];
        answer[y] = ret;
        printf("%d\n", ret);
    }
    return  0;
}