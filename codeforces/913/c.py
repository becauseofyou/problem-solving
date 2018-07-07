n,L=map(int,input().split())
c = [int(i) for i in input().split()]
for i in range(n):
    if(i > 0):
        c[i] = min(c[i], c[i - 1] * 2)

s = 0
ret = -1
for i in range(n - 1, -1, -1):
    if (L > 0):
        cnt = L // (2 ** i)
        s +=  c[i] * cnt
        L %= (2 ** i)
        if (L == 0):
            continue
        if (ret == -1 or s + c[i] < ret):
            ret = s + c[i];
if(ret == -1 ||s <ret):
    ret = s;
print (ret)
