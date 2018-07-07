n,x0,y0 = map(int, input().split(' '))
st = set()
for i in range (n):
    a,b=map(int, input().split())
    st.add((a-x0)/(b-y0) if b != y0 else float("INF"))
print (len(st))