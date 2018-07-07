n = int(input())
m = int(input())
mx=0
for i in range(30):
    if (2**i == m and i == n):
        print(0)
        exit(0)
    elif (2 ** i > m):
        mx = i
        break
if (n > mx) :
    print (m)
else:
    print (m%(2**n))
