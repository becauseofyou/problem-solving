n = int(input())
out = [0 for i in range(n + 1)]
cnt = [0 for i in range(n + 1)]
p = [-1 for i in range(n + 1)]

for i in range(2, n + 1):
    p[i]=int(input())
    out[p[i]] += 1
for i in range(1, n + 1):
    if (out[i] == 0):
        cnt[p[i]] += 1
for i in range(1, n + 1):
    if (out[i] != 0 and cnt[i] < 3):
        print("No")
        exit(0)

print("Yes")
