n,ans=int(input()),""
a=list(map(int,input().split()))
print ('PRL' * int(a[0]) + ''.join("R" + int(i) * ('PLR') for i in a[1:]) )
