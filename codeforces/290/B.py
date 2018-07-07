n, m = map(int, input().split(' '))
s = [list(input()+'.') for i in range(n)] + [list('.'*(m + 1))]
def trans():
    flag = False
    for i in range(n):
        for j in range(m):
            if s[i][j] != '.':
                ch = s[i][j]
                d = 0
                d += s[i + 1][j] == ch
                d += s[i - 1][j] == ch
                d += s[i][j + 1] == ch 
                d += s[i][j - 1] == ch
                if d < 2:
                    s[i][j] = '.'
                    flag = True
    return flag

while trans():
    flag = True
    #do nothing

for i in range(n):
    for j in range(m):
        if s[i][j] != '.':
            print ('Yes')
            quit()

print('No')
