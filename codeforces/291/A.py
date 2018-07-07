n = input()
for i in range(len(n)):
    if i == 0 and n[i] == '9':
        print (9,end='')
    elif n[i] < '5': 
        print (n[i],end='')
    else:
        print (9 - int(n[i]),end='')
