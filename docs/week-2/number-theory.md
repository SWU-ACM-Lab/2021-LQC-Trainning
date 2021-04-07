# 数论与数学 #

> 本节数学公式较多，由于GitHub不支持渲染`LaTeX`公式，所以需要查看公式的同学请将本文档下载到本地后在本地`Markdown`编辑器打开。
> 
> 推荐的Markdown编辑器：[Typora](https://typora.io)
> 
> 本文提供了渲染完成的pdf版本：[number-theory.pdf](https://sc-cos-1258290809.cos.ap-guangzhou.myqcloud.com/number-theory.pdf)
> 
> 虽然提供了pdf版本，但是我们的文档里有动图，还是建议同学们在markdown编辑器上查看

ACM实验室大一成员作业，请上交到`src/homework/number-theory`中，命名为自己的英文名，如`sunist.cpp`：

1. 了解并独立实现拓展欧几里得算法，格式如下：
   ```cpp
   int ExGcd(int a, int b, int *x, int *y);
   ```
2. 独立实现两种筛法、矩阵快速幂求`Fibonacci`数列。
3. (选做)实现`min_25`筛法。

# 数论板块 #

## 1. 裴蜀引理 ##

预备知识：

+ 约数和倍数: 如果一个整数$a$能够被正整数$b$整除，则存在另一个整数$p$使得$a = b \times p$或者$a / b = p$。称$b$是$a$的`约数`或`因数`，$a$是$b$的`倍数`。 
  正整数$a$的两个倍数的和或者差仍然是$a$的倍数。
+ 公约数和最大公约数: 如果正整数$p$同时是两个整数$a，b$的约数，称$p$为$a$和$b$的公约数，$a$和$b$所有公约数中最大的数称为`最大公约数`。 
  $0$是所有数的倍数。所有的正整数都是$0$的约数。
+ 带余除法: 给定一个整数$a$和一个整数$q$，总能找到一个整数$b$使得$a = bq + r$，其中$0 \leq r < q$，称$r$为$a$被$q$除的余数。 
  总能的证明: 画数轴，$q$为单位，$a − r$总能落在数轴上
+ 素数: 一个大于$1$的正整数，如果只有$1$和它本身两个约数，就称它为`素数`。
    两个整数的最大公约数如果为$1$，则称这两个数互素。

**裴蜀引理：** 给定两个整数$a$和$b$，假设他们的最大公约数是$p$，当且仅当$n$是$p$的倍数时，下列方程$(x, y)$有整数解:
$$
ax + by = n
$$

证明：

(1) 若$b=0$，则$(a,b)=a$. 这时定理显然成立。

(2) 若$a,b$不等于$0$：

记$d = (a, b)$, 对$ax + by = d$，两边同时除以$d$，可得$a_1x + b_1y = 1$，其中$(a_1,b_1) = 1$。

转证$a_1x + b_1y = 1$。由带余除法:
$$
a_1 = q_1b_1 + r_1, 0 < r_1 < b_1 \tag{1}
$$
$$
b_1 = q_2r_1 + r_2, 0 < r_2 < r_1 \tag{2}
$$
$$
r_1 = q_3r_2 + r_3, 0 < r_3 < r_2 \tag{3}
$$
$$
\cdots
$$
$$
r_{n-4} = q_{n-2}r_{n-3} + r_{n-2} \tag{4}
$$
$$
r_{n-3} = q_{n-1}r_{n-2} + r_{n-1} \tag{5}
$$
$$
r_{n-2} = q_{n}r_{n-1} + r_{n} \tag{6}
$$
$$
r_{n-1} = q_{n+1}r_{n} + 1 \tag{7}
$$

所以，由$(7)$和$(6)$推出

$$
r_{n-2}A_n-2 + r_{n-1}B_n-1 = 1
$$

再结合$(5)$推出

$$
r_{n-3}A_n-3 + r_{n-2}B_n-2 = 1
$$

再结合$(4)$推出

$$
r_{n-4}A_n-4 + r_{n-3}B_n-3 = 1
$$

$$
\cdots
$$

再结合$(3)$推出

$$
r_1A_1 + r_2B_2 = 1
$$

再结合$(2)$推出

$$
b_1A_0 + r_1B_0 = 1
$$

再结合$(1)$推出

$$
a_1x + b_1y = 1
$$

证明完毕。

**推论**

+ 当且仅当下面方程$(x, y)$有整数解时，两个整数$a$和$b$互素：
  $$
  ax + by = 1
  $$
+ 如果素数$p$整除两个整数$a$和$b$的乘积$ab$，则$p$必然会整除$a$或$b$

## 2. 辗转相除法 ##

辗转相除法是求两个数的最大公约数的算法。

辗转相除法是求两个数的最大公约数的算法，对于$a, b(a > b, a,b \ne 0)$而言，其有以下步骤:

1. 求$c = a \% b$
2. 令$a = b, b = c$，重复步骤$(1)$
3. 当$c=0$时，$b$为所求最大公约数

使用辗转相除法时，其步骤如下，以求$82$和$24$的最大公约数为例：

$$
\begin{matrix}
    a &  &  &  &  b &  & c\\
    82 & = & 3 & \times & 24 & + & 10 \\
    24 & = & 2 & \times & 10 & + & 4 \\
    10 & = & 2 & \times & 4 & + & 2 \\
    4 & = & 2 & \times & 2 & + & 0 \\
\end{matrix}
$$

此时求得$82$和$24$的最大公约数为$2$。

辗转相除法(欧几里得算法)的`C++`实现如下：

```cpp
/**
 * @description: 欧几里得算法的递归实现
 * @param {int} a 求最大公约数的某数
 * @param {int} b 求最大公约数的某数
 * @return {int} 求得的最大公约数
 */
int gcd(int a, int b) 
{
    return b ? gcd(b, a % b) : a;
}

/**
 * @description: 欧几里得算法的循环实现
 * @param {int} a 求最大公约数的某数
 * @param {int} b 求最大公约数的某数
 * @return {int} 求得的最大公约数
 */
int gcd(int a, int b) 
{
    int c = a % b;
    while (c != 0) 
    {
        a = b;
        b = c;
        c = a % b; 
    }
    return b;
}
```

## 3. 算术基本定理 ##

**算术基本定理：** 如果不考虑排列次序的话，每个大于1的自然数都只能有一种方式分解成若干个素数的乘积。

可以理解为：
+ **存在性：** 每个大于$1$的自然数都可以分解成素数的乘积
+ **唯一性：** 这种分解不考虑次序排列的意义下是唯一的

证明：

若$n$是素数，则$n = n$。若$n$是合数，则$n = n_1 \times n_2$，对$n_1, n_2$重复上过程，可得$n = n_p \times \cdots \times n_q, n_i \in 素数集$。

则任意$n > 1$，均可以分解成素数的乘积，证得存在性。

设

$$
\begin{aligned}
    n &= p_1 \times p_2 \times p_3 \times \cdots \times p_s \\
    &= q_1 \times q_2 \times q_3 \times \cdots \times q_t
\end{aligned}
$$

则$n \% p_1 = 0$，即$q_1 \times q_2 \times q_3 \times  \cdots \times q_t \% p_1 = 0$。

又$p_i, q_i \in 素数集$，则当$p_i \ne q_i$时，$p_i \% q_i \ne 0$。

所以必定有$q_i = p_1$，才能使得$q_1 \times q_2 \times q_3 \times  \cdots \times q_t \% p_1 = 0$。

令$n = n \div q_i = n \div p_1$，重复上述过程，可以得知对于任意$p_x$，必然有一个$q_y$与之对应。

所以必然有一种排列使得$p_i = q_i$，即在不考虑排列的情况下，这种分解是唯一的，唯一性得证。

证明完毕。

## 4. 最大公约数与最小公倍数的关系 ##

如果正整数$p$同时是两个整数$a，b$的约数，称$p$为$a$和$b$的公约数，$a$和$b$所有公约数中最大的数称为最大公约数，记作$(a,b)$。

如果正整数$p$同时是两个整数$a, b$的倍数，称$p$为$a$和$b$的公倍数，$a$和$b$所有公倍数中最小的数称最小公倍数，记作$[a, b]$。

**最大公约数与最小公倍数的关系：** 对于任意的正整数$a, b$，其最大公约数与最小公倍数满足下述关系：

$$
a \times b = (a, b) \times [a, b]
$$

证明：

若$a, b$中某数等于$1$，满足上述关系。

已知任意大于一的整数都可以表示为若干个素数的乘积，则对于$a, b$：

$$
\begin{aligned}
    a &= p_1^{s_1} \times p_2^{s_2} \times \cdots \times p_n^{s_n} \\
    b &= p_1^{t_1} \times p_2^{t_2} \times \cdots \times p_n^{t_n}
\end{aligned}
$$

其中$p_i \in 素数集$，所以$a, b$的最大公约数可以表示为：

$$
(a, b) = p_1^{\min(s_1, t_1)} \times p_2^{\min(s_2, t_2)} \times \cdots \times p_n^{\min(s_n, t_n)}
$$

$a, b$的最小公倍数可以表示为：

$$
[a, b] = p_1^{\max(s_1, t_1)} \times p_2^{\max(s_2, t_2)} \times \cdots \times p_n^{\max(s_n, t_n)}
$$

而对于任意$p_i^{s_i}, p_i^{t_i}$，都有$p_i^{s_i} \times p_i^{t_i} = p_i^{\min(s_i, t_i)} \times p_i^{\max(s_i, t_i)}$恒成立。

则有：

$$
\begin{aligned}
    a \times b &= p_1^{s_1} \times p_1^{t_1} \times p_2^{s_2} \times p_2^{t_2} \times \cdots \times p_n^{s_n} \times p_n^{t_n} \\
    &= p_1^{\min(s_1, t_1)} \times p_1^{\max(s_1, t_1)} \times p_2^{\min(s_2, t_2)} \times p_2^{\max(s_2, t_2)} \times \cdots \times p_n^{\min(s_n, t_n)} \times p_n^{\max(s_n, t_n)} \\
    &= (a, b) \times [a, b]
\end{aligned}
$$

证明完毕。

## 5. 素数 ##

### 5.1 如何判断素数 ###

**$O(n)$复杂度算法：**

判断一个大于$2$的整数$n$是否为素数，最简单的方法便是根据素数的定义去判断，即使用从$2$到$n$之间的所有整数与$n$做除法，看能否与$n$整除，其代码实现如下：

```cpp
bool isPrime(int n) 
{
	for (int i = 2; i < n; ++i)
	{
		if (n % i == 0) 
		{
			return false;
		}
	}
	return true;
}
```

**$O(\sqrt{n})$复杂度算法：**

在上面的算法中，其实并不需要按照定义一直判断到$n$，我们只需要判断从$2$到$\sqrt{n}$之间的整数就可以了。

证明：

若$n$不是素数，则其可以表示为$n = n_1 \times n_2$，我们不妨令$n_1 \leq n_2$。

此时我们知道$n_1$可能取得最大值时，有$\max(n_1) = n \div \min(n_2)$，即$n_1 = n_2$，此时$n_1 = n \div n_2 = \sqrt{n}$。

所以$n_1 \in [2, \sqrt{n}]$，即若$n$不是素数，其必有一个因数在区间$[2, \sqrt{n}]$。

证明完毕。

其代码实现较上文差别不大，此处就不单独展示了。

**(选学)Fermat素性测试：**

我们可以根据`费马小定理`得出一种检验素数的思路：

不断地选取在$[2, n-1]$中的基$a$，并检验是否每次都有$a^{n-1} \equiv 1 \pmod n$ 

```cpp
/**
 * @description: 
 * @param {int} n 要判断的数n
 * @return {bool} n是否为素数，是则返回true
 */
bool millerRabin(int n) {
    if (n < 3) 
    {
        return n == 2;
    }

    // test_time 为测试次数,建议设为不小于 8
    // 的整数以保证正确率,但也不宜过大,否则会影响效率
    for (int i = 1; i <= test_time; ++i) 
    {
        int a = rand() % (n - 2) + 2;
        if (quickPow(a, n - 1, n) != 1) 
        {
            return false;
        }
    }
    return true;
}
```

但是费马小定理的逆定理并不成立，这个方法也不是完全准确的，需要额外考虑`Carmichael Number`。这个方法的时间复杂度大致为$O(\log n)$。

### 5.2 如何生成素数 ###

在上面我们知道了如何判断一个数是不是素数，那么引申出了另一个问题，我们要如何求某个区间内的所有素数呢？

我们当然可以按照上面的方法对区间内每一个数都进行一次判断，但我们稍作分析就知道，判断一个数是不是素数的时间复杂度是$O(\sqrt{n})$，那么判断$n$个数是不是素数的时间复杂度就是$O(n\log n)$，这其实是一个十分费时的算法，通常情况下会被比赛卡超时。

然后我们就要讲到我们的两大法宝： `埃拉托斯特尼筛法`和`线性筛法`

**埃氏筛**

埃氏筛法的基本原理是：如果找到一个质数，那么这个质数的倍数都不是质数。

我们只需要将范围内的所有数从头开始并标记出他们的倍数，遇到标记过的数就跳过，直到标记到最后为止。其过程表示如下：

<div aligned="center"><img src = "https://www.pianshen.com/images/522/fc4debb1d5aae09a985ee372829aed02.gif"/></div>

这个过程的`C++`实现如下：

```cpp
// include <cstdlib>

/**
 * @description: 埃拉托斯特尼筛法
 * @param {int} n 要求的素数区间，即求[2, n]之间的素数
 * @return {*} isPrime为true的均为素数
 */
void EratosthenesMethod(int n) 
{
    bool *tag = new bool[n];
    for (int i = 0; i < n; ++i) 
    {
        isPrime[i] = true;
    }

    for (int i = 2; i * i < n; ++i) 
    {
        if (isPrime[i]) 
        {
            for (int j = i * i; j < n; j += i) 
            {
                isPrime[j] = false;
            }
        }
    }
}
```

上面的算法可以预先处理每个数都有的质因数以提升效率。其复杂度为$O(n \log \log n)$

想看其复杂度计算过程吗？

> 参考自[OI-Wiki.org](https://oi-wiki.org/math/sieve/)

可以直接观察知埃氏筛法的复杂度为

$$
n \sum_p {1 \over p}
$$

调和级数$\displaystyle \sum_n {1 \over n} = \ln n$，由唯一分解定理可得：

$$
\sum_n {\frac{1}{n}} = \prod_{p} (1 + \frac{1}{p} + \frac{1}{p^2} + \cdots) = \prod_p {\frac{p}{p-1}}
$$

两边同时取对数，得：

$$
\begin{aligned}
    \ln \sum_n {\frac{1}{n}} &= \ln \prod_p {\frac{p}{p-1}} \\
    \ln \ln n &= \sum_p ({\ln p - \ln (p-1)})
\end{aligned}
$$

易知$\displaystyle \int \frac{1}{x} dx = \ln x$，由微积分基本定理：

$$
\sum_p ({\ln p - \ln (p-1)}) = \sum_p {\int_{p-1}^{p} {\frac{1}{x}dx}}
$$

得

$$
\int_{p-1}^{p} {\frac{1}{x}dx} > \frac{1}{p}
$$

即

$$
\ln \ln n = \sum_p {\int_{p-1}^{p} {\frac{1}{x}dx}} > \sum_p {\frac{1}{p}}
$$

用$O$法表示即为$O(n \log \log n)$

**线性筛**

埃氏筛法仍有优化空间，它会将一个合数重复多次标记。有没有什么办法省掉无意义的步骤呢？答案是肯定的。

如果能让每个合数都只被标记一次，那么时间复杂度就可以降到$O(n)$了。

其`C++`代码实现如下：

```cpp
void EulerMethod (int n) {
phi[1] = 1;
for (int i = 2; i < n; ++i) 
{
if (!vis[i]) {
phi[i] = i - 1;
pri[cnt++] = i;
}
for (int j = 0; j < cnt; ++j) {
if (1ll * i * pri[j] >= n) break;
vis[i * pri[j]] = 1;
if (i % pri[j]) {
phi[i * pri[j]] = phi[i] * (pri[j] - 1);
} else {
// i % pri[j] == 0
// 换言之，i 之前被 pri[j] 筛过了
// 由于 pri 里面质数是从小到大的，所以 i 乘上其他的质数的结果一定也是
// pri[j] 的倍数 它们都被筛过了，就不需要再筛了，所以这里直接 break
// 掉就好了
phi[i * pri[j]] = phi[i] * pri[j];
break;
}
}
}
}
```

**(选学) `min_25`筛法**

这个筛法是`min_25`大佬在比赛的时候发明的筛法，其时间复杂度为$O(n^{2 \over 3})$，其中很多内容~~我们也不会~~需要同学们自己理解

> 本节参考了大量资料：
> + [Sum of Multiplicative Function - min_25's blog](https://\min-25.hatenablog.com/entry/2018/11/11/172216)
> + [min_25筛 - 租酥雨的博客](https://www.cnblogs.com/zhoushuyu/p/9187319.html)

min_25筛主要步骤由两步组成：

# 数学板块 #

## 1. 矩阵快速幂 ##