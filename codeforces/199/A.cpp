#include <cstdio>
#include <cstring>
int a[100010];
int cnt[10];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i = 1; i <= n; i++) {
        scanf("%d",&a[i]);
        cnt[a[i]] ++;
    }
    if(cnt[5] || cnt[7]) {
        return puts("-1"),0;
    }
    bool flag = true;
    int first = 0, second = 0, third = 0;
    if(cnt[4])
    {
        if(cnt[1] >= cnt[4] && cnt[2] >= cnt[4])
        {
            cnt[1] -= cnt[4];
            cnt[2] -= cnt[4];
            first += cnt[4];
        }
        else 
        {
            flag = false;
        }
    }
    if(!flag) return puts("-1"),0;
    if(cnt[2])
    {
        if(cnt[1] >= cnt[2] && cnt[6] >= cnt[2])
        {
            cnt[1] -= cnt[2];
            cnt[6] -= cnt[2];
            second += cnt[2];
        }
        else 
        {
            flag = false;
        }
    }
    if(!flag) return puts("-1"),0;
    if(cnt[3] == cnt[1] && cnt[1] == cnt[6])
    {
        third = cnt[3];
    }
    else flag = false;
    if(!flag) return puts("-1"),0;
    if(first) {
        for(int i = 0; i < first;i++) {
            printf("1 2 4\n");
        }
    }
    if(second) {
        for(int i = 0; i < second; i++) {
            printf("1 2 6\n");
        }
    }
    if(third) {
        for(int i = 0; i < third; i++) {
            printf("1 3 6\n");
        }
    }
    return 0;
}
