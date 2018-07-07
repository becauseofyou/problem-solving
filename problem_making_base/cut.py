input_file = "B-small-practice.in"

with open(input_file, "r") as f:
    li = f.readlines()

f.close()
cnt = 1
for i in range(5,10,1):
    target = "data" + str(i) + ".in"
    with open (target, "w") as f:
        f.write("20\n")
        for j in  range(20):
            s = li[cnt]
            begin, cards = map(int, s.split())
            nxt_cnt = cnt + cards + 1
            for k in range(cnt, nxt_cnt):
                f.write(li[k])
            cnt = nxt_cnt
    f.close()
