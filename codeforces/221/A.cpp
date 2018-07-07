#include <cstdio>
#include <cstring>
char ss[8][5] = {"1869", "1968", "1689", "6198", "1698", "1986",
"1896"};
char s[1000010];
int cnt[10];
int main() {
  scanf("%s",s);
  int n = strlen(s);
  for(int i = 0; i < n; i++)  {
    cnt[s[i] - '0'] ++;
  }
  cnt[1] --;
  cnt[6] --;
  cnt[9] --;
  cnt[8] --;
  bool flag = false;
  int sum = 0;
  for(int i = 9; i >= 1; i--) if(cnt[i]){
    flag = true;
    for(int j = 0; j < cnt[i]; j++) 
      printf("%d",i),sum = (sum * 10 + i) % 7;
  }
  if(!flag) {
    printf("%s",ss[0]);
  } else {
    sum = sum * 10000 % 7;
    printf("%s",ss[(7-sum)%7]);
  }
  for(int j = 0; j < cnt[0]; j++) printf("0");
  puts("");
  return 0;
}