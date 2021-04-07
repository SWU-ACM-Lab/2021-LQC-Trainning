# 数论与数学 #

> 本节数学公式较多，由于GitHub不支持渲染`LaTeX`公式，所以需要查看公式的同学请将本文档下载到本地后在本地`Markdown`编辑器打开。
> 
> 推荐的Markdown编辑器：[Typora](https://typora.io)
> 
> 本文提供了渲染完成的pdf版本：[number-theory.pdf](https://sc-cos-1258290809.cos.ap-guangzhou.myqcloud.com/number-theory.pdf)

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
(a, b) = p_1^{min(s_1, t_1)} \times p_2^{min(s_2, t_2)} \times \cdots \times p_n^{min(s_n, t_n)}
$$

$a, b$的最小公倍数可以表示为：

$$
[a, b] = p_1^{max(s_1, t_1)} \times p_2^{max(s_2, t_2)} \times \cdots \times p_n^{max(s_n, t_n)}
$$

而对于任意$p_i^{s_i}, p_i^{t_i}$，都有$p_i^{s_i} \times p_i^{t_i} = p_i^{min(s_i, t_i)} \times p_i^{max(s_i, t_i)}$恒成立。

则有：

$$
\begin{aligned}
    a \times b &= p_1^{s_1} \times p_1^{t_1} \times p_2^{s_2} \times p_2^{t_2} \times \cdots \times p_n^{s_n} \times p_n^{t_n} \\
    &= p_1^{min(s_1, t_1)} \times p_1^{max(s_1, t_1)} \times p_2^{min(s_2, t_2)} \times p_2^{max(s_2, t_2)} \times \cdots \times p_n^{min(s_n, t_n)} \times p_n^{max(s_n, t_n)} \\
    &= (a, b) \times [a, b]
\end{aligned}
$$

证明完毕。

## 5. 素数 ##

### 如何判断素数 ###

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

在上面的算法中，其实并不需要按照定义一直判断到$n$

> 以下内容较难，有困难的同学可以选择跳过本节。

### 诶氏筛 ###



### 线性筛 ###


### (选学) `min_25`筛法 ###

这个筛法是`min_25`大佬在比赛的时候发明的筛法，其时间复杂度为$O(n^{2 \over 3})$，其中很多内容~~我们也不会~~需要同学们自己理解

> 本节参考了大量资料：
> + [Sum of Multiplicative Function - min_25's blog](https://min-25.hatenablog.com/entry/2018/11/11/172216)
> + [min_25筛 - 租酥雨的博客](https://www.cnblogs.com/zhoushuyu/p/9187319.html)

min_25筛主要步骤由两步组成：

# 数学板块 #

## 1. 矩阵快速幂 ##