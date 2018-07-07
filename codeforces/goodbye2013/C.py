n = int(input() )
a = list(map(int, input().split(' ')))
id = sorted(range(n), key=lambda x : a[x])
for i in range(1, n):
    if a[id[i]] <= a[id[i - 1]]:
        a[id[i]] = a[id[i - 1]] + 1
print(' '.join(map(str, a)))