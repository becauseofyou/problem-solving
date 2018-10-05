# 状态压缩DP进阶

[TOC]

## lowbit优化

```cpp
inline int lowbit(int x) {
    return x & -x;
}
for (int i = 0; i < n; i++) {
    Log[1 << i] = i;
}
for (int i = 0; i < (1 << n); i++) {
    for (int k = i; k > 0; k -= lowbit(k) ) {
        int j = Log[lowbit(k)];
        transfer(dp[i] <-  dp[i ^ (1 << j)]);
    }
}
```



利用lowbit不断算出当前二进制的最低1位，跳过0的位置，复杂度为

$\sum\limits_{i=1}^n i * \binom n i   = n * 2 ^ {n - 1}$

 证明：$\sum\limits_{i=1}^n i * \binom n i  + \sum\limits_{i=1}^n i * \binom n i  = \sum\limits_{i=1}^n i * \binom n i   + \sum\limits_{i=1}^n (n - i) * \binom n i  = \sum\limits_{i=1}^n n* \binom n i  = 2^n * n$ 

我们发现这与原来的$n * 2^n $相比少了一倍常数

## 子集枚举 

有时候在做一些状压DP时，我们发现我们需要非常暴力的去枚举一个集合所有的子集来转移，这个时候我们可以采用如下方法

```cpp
for (int mask = 0; mask < (1 << n); mask++) {
    //从大到小枚举子集
    for (int sub = mask; sub; sub = (sub - 1) & mask) {
        transfer(dp[mask], dp[sub],dp[mask ^ sub]);
    }
}
```

- 为什么每次减1与mask进行与操作就能枚举出子集?

  相当于忽略mask里面的0位然后将一个全是1的二进制不断减1，每一个都是子集

- 复杂度怎么算?

  $\sum\limits_{i=1}^n \binom n i * 2 ^ i = (2 + 1) ^ n = 3 ^ n$



## 最小斯坦纳树

使得特定的K个点连通的最小生成树称为最小斯坦纳树，K一般比较小

最小生成树其实是斯坦纳树的特殊情况(K=n)

如果这K个点之间两两求最短路，然后求MST，答案不一定是对的，因为最终的生成树的边不一定是两个点之间的最短路，比如下面这个图

![image-20181004103858322](/Users/wuyiqi/Library/Application Support/typora-user-images/image-20181004103858322.png)

我要求ABC三个点的最小斯坦纳树，如果是两两之间跑最短路，那肯定会选择外层的三条边，但是实际上的最小斯坦纳树是里面的三条边。



K比较小，我们考虑状态压缩DP

尝试：

我们尝试记录集合的最小连通代价，在求一个$mask$的最小连通代价时,可以枚举这个$mask$的两个子集$sub$与$mask \oplus  sub$,然后跑最短路求这两个子集的最小连通代价作为转移,但是我们发现这样子还是跟刚才一样，并不会考虑到D点





