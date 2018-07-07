n, m = map(int, input().split(' '))
s = (['#'*m] + ['.'*(m-1)+'#'] + ['#'*m] + ['#'+'.'*(m-1)])*100
for i in range(n):
    print(s[i])
