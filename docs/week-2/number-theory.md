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

### 5.0 $n$以内的素数有几个 ###

**素数计算函数：**

小于或等于$x$的素数的个数，可以用$\pi(x)$表示，有：

$$
\lim_{x \to \infty} {\pi(x)} = \frac{x}{\ln{x}}
$$

在$x \geq 10^5$时，此函数的误差已经小于$1\%$了。通常情况下，可以用此函数估计素数的个数。

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

其`C++`实现如下：

```cpp
/**
 * @description: 费马素性测试
 * @param {int} n 要判断的数n
 * @return {bool} n是否为素数，是则返回true
 */
bool millerRabin(int n) {
    if (n < 3) 
    {
        return n == 2;
    }

    // test_time为测试次数,建议设为不小于8的整数以保证正确率,但也不宜过大,否则会影响效率
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
/**
 * @description: 欧拉筛法
 * @param {int} n 要求的n以内的素数
 * @return {void}
 */
void EulerMethod (int n) {
	unsigned long long *phi = new unsigned long long[n];
	phi[1] = 1;
	int cnt = 0;

	for (int i = 2; i < n; ++i) 
	{
		if (!vis[i])
		{
			phi[i] = i - 1;
			pri[cnt++] = i;
		}

		for (int j = 0; j < cnt; ++j) 
		{
			if (1ll * i * pri[j] >= n) // 此处1ll是在计算时使用long long类型，避免溢出
			{
				break;
			}

			vis[i * pri[j]] = 1;
			if (i % pri[j]) 
			{
				phi[i * pri[j]] = phi[i] * (pri[j] - 1);
			} 
			else 
			{
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
> + [Sum of Multiplicative Function - min_25](https://\min-25.hatenablog.com/entry/2018/11/11/172216)
> + [min_25筛 - 租酥雨](https://www.cnblogs.com/zhoushuyu/p/9187319.html)
> + [min25筛学习笔记&模板详解 - Flyppy_White](https://blog.csdn.net/baiyifeifei/article/details/90454317)

首先我们定义一些符号和说明：

+ $p \in \R$并且$p \in 素数集$，$p_k$是所有素数中第$k$小的素数，特别定义$p_0 = 1$
+ $\operatorname{lpf}(n)$表示$n$最小的质因数，特别定义$\operatorname{lpf}(1) = 1$
+ $f(p)$是一个关于$p$的项数较少的多项式或者可以快速求值的多项式，$f(p^c)$需要能够快速求值
+ $\displaystyle x / y = \left\lfloor \frac{x}{y} \right\rfloor$
+ $\displaystyle F_k(n) = \sum^{n}_{i=2} [{p_k \leq \operatorname{lpf(i)}] f(i)}$

我们不难知道，通过枚举每个$i$的最小质因子及其次数可以得到$F_k(n)$的递推式

$$
\begin{aligned} 
    F_{k}(n) &= \sum_{i = 2}^{n} [p_{k} \le \operatorname{lpf}(i)] f(i) \\ 
    &= \sum_{\substack{k \le i \\ p_{i}^{2} \le n}} \sum_{\substack{c \ge 1 \\ p_{i}^{c} \le n}} f\left(p_{i}^{c}\right) ([c > 1] + F_{i + 1}\left(n / p_{i}^{c}\right)) + \sum_{\substack{k \le i \\ p_{i} \le n}} f(p_{i}) \\ 
    &= \sum_{\substack{k \le i \\ p_{i}^{2} \le n}} \sum_{\substack{c \ge 1 \\ p_{i}^{c} \le n}} f\left(p_{i}^{c}\right) ([c > 1] + F_{i + 1}\left(n / p_{i}^{c}\right)) + F_{\mathrm{prime}}(n) - F_{\mathrm{prime}}(p_{k - 1}) \\ 
    &= \sum_{\substack{k \le i \\ p_{i}^{2} \le n}} \sum_{\substack{c \ge 1 \\ p_{i}^{c + 1} \le n}} \left(f\left(p_{i}^{c}\right) F_{i + 1}\left(n / p_{i}^{c}\right) + f\left(p_{i}^{c + 1}\right)\right) + F_{\mathrm{prime}}(n) - F_{\mathrm{prime}}(p_{k - 1}) 
\end{aligned}
$$

最后一步推导基于这样一个事实：

对于满足$p_{i}^{c} \le n < p_{i}^{c + 1}$的$c$，有：

$$
p_{i}^{c + 1} < n \iff n / p_{i}^{c} < p_{i} < p_{i + 1}
$$

即

$$
F_{i + 1}\left(n / p_{i}^{c}\right) = 0
$$

其`C++`实现，请转到[min25筛学习笔记&模板详解 - Flyppy_White](https://blog.csdn.net/baiyifeifei/article/details/90454317)

# 数学板块 #

## 1. 矩阵快速幂 ##

// todo...看到记得提醒我写这里 \
// todo...看到记得提醒我写这里 \
// todo...看到记得提醒我写这里 \
// todo...看到记得提醒我写这里 \
// todo...看到记得提醒我写这里 \
// todo...看到记得提醒我写这里 \
// todo...看到记得提醒我写这里 \
// todo...看到记得提醒我写这里

## 2. 高精度计算 ##

高精度计算(Arbitrary-Precision Arithmetic)，也被称作大整数(bignum)计算，运用了一些算法结构来支持更大整数间的运算(数字大小超过语言内建整型)。

此节难度较低，同学们仅需知道竖式是怎么算的就行了，模拟实现这些过程就完事了。

~~不会建议退学重读小学。~~

可以参考高精度的模版：[高精度计算](https://oi-wiki.org/math/bignum/)

## 3. 组合数学 ##

排列组合是组合数学中的基础。

+ 排列就是指从给定个数的元素中取出指定个数的元素进行排序
+ 组合则是指从给定个数的元素中仅仅取出指定个数的元素，不考虑排序。
 
排列组合的中心问题是研究给定要求的排列和组合可能出现的情况总数。排列组合与古典概率论关系密切。

在我们所有的暴力、枚举题目中，无遗漏地进行排列组合是我们解题的关键。

`加法原理`、`乘法原理`、`二项式定理`啥的如果不知道自己回去补课，此处重点介绍全排列。

什么是全排列呢？以$1,2,3$三个数(状态)为例，它们的全排列为：

$$
\begin{matrix}
    1 & 2 & 3 \\
    1 & 3 & 2 \\
    2 & 1 & 3 \\
    2 & 3 & 1 \\
    3 & 1 & 2 \\
    3 & 2 & 1
\end{matrix}
$$

对于$n$种状态的全排列而言，它们有$n!$种情况。

对于$1,2,3$而言，我们可以很轻松地写出对应的代码：

```cpp
void printPermutation () 
{
    for (int i = 1; i <= 3; ++i) 
    {
        for (int j = 1; j <= 3; ++j) 
        {
            for (int k = 1; k <= 3; ++k) 
            {
                if (i == j || i == k || j == k) 
                {
                    continue;
                }
                else 
                {
                    print(i, j, k);
                }
            }
        }
    }
}
```

在状态数量较少的时候，我们可以使用循环来进行全排列，但是在状态较多的时候，循环就显得过于繁复，同时循环也无法处理状态数量未知的全排列。此时我们就应该考虑其他方法实现全排列了。

**递归实现：**

我们可以发现，全排列是把已知的所有状态按照不同的顺序分别展示出来，那么我们就不难想到我们可以使用图结构和深度优先搜索来实现这个需求，我们只需要从不同的节点出发，遍历有所有状态组成的图即可。

其`C++`实现如下：

```cpp
void printPermutation(int x, int n, bool *Visited, int *answer)
{
	if (x > n)
	{
		for (int i = 0; i < n; i++)
		{
			print(answer[i]);
		}
	}
	for (int i = 0; i < n; i++)
	{
		if (!Visited[i])
		{
			answer[x-1] = i+1;
			Visited[i] = true;
			printPermutation(x+1, n, Visited, answer);
			Visited[i] = false;
		}
	}
}
```

当然，建立树并对树进行遍历也是可以实现的，更多的写法可以转到[P1706 全排列问题 题解](https://www.luogu.com.cn/problem/solution/P1706)

**STL实现：**

在`C++ STL`中，有一个函数叫做全排列函数，它分为`next_permutation`和`prev_permutation`，作用是求当前排列的上一个排列和下一个排列。

```cpp
bool next_permutation(iterator start,iterator end);
bool prev_permutation(iterator start,iterator end)
```

其中`start`是排列状态的开始位置，`end`是排列状态的结束位置，返回值是能否找到下一个/上一个排列，能则返回`true`，不能则返回`false`。

同时，此函数的上一项、下一项按照字典序进行排列。

至于具体的使用方法，可以转到[C++STL中全排列函数next_permutation的使用 - AC_Gibson](https://blog.csdn.net/ac_gibson/article/details/45308645)

## 4. 概率论 ##



## 5. 博弈论 ##