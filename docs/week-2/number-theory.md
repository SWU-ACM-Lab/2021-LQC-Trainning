# 数论与数学 #

> 本节数学公式较多，由于GitHub不支持渲染`LaTeX`公式，所以需要查看公式的同学请将本文档下载到本地后在本地`Markdown`编辑器打开。
> 
> 推荐的Markdown编辑器：[Typora](https://typora.io)
> 
> 本文提供了渲染完成的pdf版本：[number-theory.pdf](https://sc-cos-1258290809.cos.ap-guangzhou.myqcloud.com/files/number-theory.pdf)
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

<center><div aligned="center"><img src = "https://www.pianshen.com/images/522/fc4debb1d5aae09a985ee372829aed02.gif"/></div></center>

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

### 1.1 矩阵 ###

这一点回去找你们的线性代数老师。

~~需要的这里有一份线性代数笔记：[线性代数 - sunist](https://sc-cos-1258290809.cos.ap-guangzhou.myqcloud.com/files/%E7%BA%BF%E6%80%A7%E4%BB%A3%E6%95%B0.pdf)~~

### 1.2 快速幂 ###

对于任意的数$n$，都可以通过位运算将它化为多个$2$的幂的和的形式。

例如:

$$
\begin{aligned}    
    100_{10} &= 1100100_{2}=2^2+2^5+2^6 \\ 
    735_{10} &= 1011110001_2 = 2^0+2^4+2^5+2^6+2^7+2^9
\end{aligned}
$$

但是，当指数特别大的时候，如$n^{114514}$，我们想要计算它的时候，就得计算$114513$次乘法才能得出结果。这样我们就得等很久才能计算完毕，那么有没有什么办法能够加速这一过程呢？

亲亲，有的！这个方法就是快速幂：

以$n^{735}$为例：

$$
n^{735} = n^{2^0+2^4+2^5+2^6+2^7+2^9}=n^{2^0}+n^{2^4}+n^{2^5}+n^{2^6}+n^{2^7}+n^{2^9}  \tag{1}
$$

同时，根据~~常识~~ 常人所不知道的知识：

$$
2^n = 1 << n
$$

我们知道其时间复杂度为$O(1)$，对于$(1)$式$2$的幂只需要$6$次位运算即可求得：

$$
2^0=1，2^4=16,2^5=32,2^6=64,2^7=128,2^8=256
$$

即：

$$
n^{735} = n^{2^0+2^4+2^5+2^6+2^7+2^9}=n^1+n^{16}+n^{32}+n^{64}+n^{128}+n^{256}
$$

我们再再依次求$n$的幂，求完相加次数就变为了$(1+16+32+64+128+256)$次乘法和$5$次加法，一共$502$次运算。但实际编程中后一次运算的结果可以由前一次运算的结果迭代而来。

即：

$$
n^1  \tag{1}
$$

$$
n^2 = {(n^1)}^2
$$

$$
n^4 = {(n^{2})}^2
$$

$$
n^{8} = (n^4)^2
$$

$$
n^{16} = {(n^{8})}^2 \tag{2}
$$

$$
n^{32} = {(n^{16})}^2 \tag{3}
$$

$$
n^{64} = {(n^{32})}^2 \tag{4}
$$

$$
n^{128} = {(n^{64})}^2 \tag{5}
$$

$$
n^{256} = {(n^{128})}^2 \tag{6}
$$

由于位运算帮助我们计算是否该取该数，实际上运算次数是$8$次乘法运算、$5$次加法运算和$8$次位运算，一共$21$次。由$734$次运算降低为$21$次运算，效率上大大提高。这就是快速幂。

快速幂的`C++`实现如下：

```cpp
/**
 * @description: 快速幂，计算base^index
 * @param {int} base 底数
 * @param {int} index 指数
 * @return {int} 计算结果base^index
 */
int quick_power (int base, int index)
{
    int result = 1;
    while (index)
    {
        if (index & 1)
        {
            result *= base;
        }
        base *= base;
        index = index >> 1;
    }
    return result;
}
```

### 1.3 矩阵快速幂 ###

现在我们已经知道了什么是矩阵，什么是快速幂。~~聪明的同学们一定能很简单的推出什么是矩阵快速幂吧！~~

那么什么是矩阵快速幂呢？答案当然是矩阵的快速幂啦！

> 下面为了叙述方便，我们使用方阵举例，矩阵也有同样的性质。

对于一个方阵$A$,它的$n$次幂为：

$$
A^n=\prod_{i=1}^n{A}
$$

对于$A^n$，需要做$n-1$次乘法运算。由整数快速幂的计算方法，你可能已经想到了，方阵也可以简化运算。没错，这就是矩阵快速幂。

如$A^{19}$:

$$
A^{19} = A^{16} + A^2 + A^1
$$
同样后面的运算结果可以由前面的运算结果迭代而来:
$$
A^1
$$

$$
A^2 = A^1 * A^1
$$

$$
A^4 = A^2 * A^2
$$

$$
A^8 = A^4 * A^4
$$

$$
A^{16}=A^8*A^8
$$

运算过程和整数快速幂相同，而两个矩阵的乘法运算~~我们早就刻进DNA啦~~ 我们也能没什么难度地实现。

那么下面就是方阵快速幂的`C++`代码实现了：

```cpp
/**
 * @description: 方阵快速幂
 * @param {SquareMatrix} A 快速幂的底，即方阵A
 * @param {int} n 指数
 * @return {SquareMatrix} 计算结果，即A^n
 */
SquareMatrix matrix_quick_power(SquareMatrix A,int n){
    SquareMatrix base = A;
    SquareMatrix result;
    //对B进行初始化，初始化为单位阵
    for(int i = 0;i < N;i++){
        for(int j = 0;j < N;j++){
            if(i == j){
                result.matrix[i][j] = 1;
            }else{
                result.matrix[i][j] = 0;
            }
        }
    }
    while(n)
    {
        if(n&1)
        {
            result = mul(result,base);
        }
        base = mul(base,base);
        n = n>>1;
    }
    return result;
}
```

那么矩阵快速幂有什么用呢？**请同学们转到[快速幂](https://oi-wiki.org/math/quick-pow/)仔细阅读。** ~~不是懒不写啊，已经加粗了，自己没看错过了后果自负。~~

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

### 3.1 排列组合 ###

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

当然，建立树并对树进行遍历也是可以实现的，更多的写法可以转到[P1706 全排列问题 题解 - 洛谷](https://www.luogu.com.cn/problem/solution/P1706)

**STL实现：**

在`C++ STL`中，有一个函数叫做全排列函数，它分为`next_permutation`和`prev_permutation`，作用是求当前排列的上一个排列和下一个排列。

```cpp
bool next_permutation(iterator start,iterator end);
bool prev_permutation(iterator start,iterator end);
```

其中`start`是排列状态的开始位置，`end`是排列状态的结束位置，返回值是能否找到下一个/上一个排列，能则返回`true`，不能则返回`false`。

同时，此函数的上一项、下一项按照字典序进行排列。

至于具体的使用方法，可以转到[C++STL中全排列函数next_permutation的使用 - AC_Gibson](https://blog.csdn.net/ac_gibson/article/details/45308645)

### 3.2 容斥原理 ###

我们先引入一个问题：

> 假设班里有$11$个学生喜欢数学，$45$个学生喜欢语文，$14$个学生喜欢编程，班里至少喜欢一门学科的有多少个学生呢？
> 
> 是$11+45+14 = 70$个吗？显然不是的，因为有些学生可能同时喜欢数学和语文，或者语文和编程，甚至还有可能三者都喜欢。

对于上面的问题，其很有可能是下图这种情况：

<center><div aligned="center"><img src="https://oi-wiki.org/math/images/incexcp.png"/></div></center>

现在我们引入容斥原理。

设$U$种元素有$n$种不同的属性，而第$i$种属性称为$P_i$，拥有属性$P_i$的元素构成集合$S_i$，那么有：

$$
\begin{aligned}
    \left| \bigcup_{i=1}^{n} S_i \right| &= \sum_{i} | S_i | - \sum_{i<j} | S_i \cap S_j | + \sum_{i<j<k} |S_i \cap S_j \cap S_k | - \cdots \\ 
    & \quad + (-1)^{m-1} \sum_{a_i<a_{i+1} } \left| \bigcap_{i=1}^{m} S_{a_i} \right| + \cdots + (-1)^{n-1} \left| S_1 \cap \cdots \cap S_n \right|
\end{aligned}
$$

即：

$$
\left|\bigcup_{i=1}^{n}S_i\right|=\sum_{m=1}^n(-1)^{m-1}\sum_{a_i<a_{i+1} }\left|\bigcap_{i=1}^mS_{a_i}\right|
$$

~~看懂了吗？是不是超级简单。~~ 上面的乱七八糟的公式其实就是在做一件事：

先不考虑重叠的情况，把包含于某内容中的所有对象的数目先计算出来，然后再把计数时重复计算的数目排斥出去，使得计算的结果既无遗漏又无重复。

这种原理在我们的程序设计中有着广泛的应用。

## 4. 概率论 ##

这玩意主要以理论为主，与计算机没有直接交集，此处跳过。

~~需要的同学们可以拿这份笔记： [概率论与数理统计(不完整版) - sunist](https://sc-cos-1258290809.cos.ap-guangzhou.myqcloud.com/files/%E6%A6%82%E7%8E%87%E8%AE%BA%E4%B8%8E%E6%95%B0%E7%90%86%E7%BB%9F%E8%AE%A1.pdf)~~

## 5. (选学)博弈论 ##

博弈论，是经济学的一个分支，主要研究具有竞争或对抗性质的对象，在一定规则下产生的各种行为。博弈论考虑游戏中的个体的预测行为和实际行为，并研究它们的优化策略。

通俗地讲，博弈论主要研究的是：在一个游戏中，进行游戏的多位玩家的策略。

下面是一个`Nim游戏`的示例：

$n$堆物品，每堆有$a_i$个，两个玩家轮流取走任意一堆的任意个物品，但不能不取。取走最后一个物品的人获胜。

> 例如，如果现在有$3$堆物品，而每堆分别有$2,5,4$个，那么可以取走第$1$堆中的$2$个物品，局面就变成了$0,5,4$；或者也可以取走第$2$堆的$4$个物品，局面就变成了$2,1,4$。
> 
> 如果现在的局面为$0,0,4$，甲取走了第$3$堆的$4$个物品，也就是取走了最后一个物品，此时甲获胜。

如果将每个状态视为一个节点，再从每个状态向它的后继状态连边，我们就可以得到一个博弈状态图。如果节点$(i,j,k)$表示局面为$i,j,k$时的状态，则我们可以画出下面的博弈图(由于篇幅有限，故仅显示部分状态节点和部分边)：

<center><div aligned="center"><img src="https://oi-wiki.org/math/images/game1.png"/></div></center>

定义`必胜状态`为`先手必胜`的状态，`必败状态`为`先手必败`的状态。

通过推理，我们可以得出下面三条定理：

+ 定理 1：没有后继状态的状态是必败状态。
+ 定理 2：一个状态是必胜状态当且仅当存在至少一个必败状态为它的后继状态。
+ 定理 3：一个状态是必败状态当且仅当它的所有后继状态均为必胜状态.

对于定理 1，如果游戏进行不下去了，那么这个玩家就输掉了游戏。

对于定理 2，如果该状态至少有一个后继状态为必败状态，那么玩家可以通过操作到该必败状态；此时对手的状态为必败状态——对手必定是失败的，而相反地，自己就获得了胜利。

对于定理 3，如果不存在一个后继状态为必败状态，那么无论如何，玩家只能操作到必胜状态；此时对手的状态为必胜状态——对手必定是胜利的，自己就输掉了游戏。

现在我们定义`Nim和`，记作$\operatorname{Nim}_S$：

$$
\operatorname{Nim}_S = a_1 \oplus a_2 \oplus \cdots \oplus a_n 
$$

则当且仅当$\operatorname{Nim}_S = 0$时，该状态为必败状态，否则为必胜状态。

该结论的证明过程可见[Nim游戏 - 博弈论](https://oi-wiki.org/math/game-theory/#_3)

为了计算这个$\operatorname{Nim}_S$，我们引入$\operatorname{mex}$函数与$\operatorname{SG}$函数：

$$
\operatorname{mex}(S)=\min\{x\} \quad (x \notin S, x \in N)
$$

即$\operatorname{mex}$函数计算不属于集合$S$中的最小非负整数。

$$
\operatorname{SG}(x)=\operatorname{mex}\{\operatorname{SG}(y_1), \operatorname{SG}(y_2), \ldots, \operatorname{SG}(y_k)\}
$$

对于由$n$个有向图游戏组成的组合游戏，设它们的起点分别为$s_1, s_2, \cdots , s_n$，则有定理：

当且仅当:

$$
\operatorname{SG}(s_1) \oplus \operatorname{SG}(s_2) \oplus \ldots \oplus \operatorname{SG}(s_n) \neq 0
$$

这个游戏是先手必胜的。

我们就可以使用$\operatorname{SG}$函数与$\operatorname{Nim}_S$的结论来计算博弈论中的必胜问题了。

## 6. 进制转换 ##

讲过太多次，不想再讲了。