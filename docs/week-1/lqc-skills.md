<!--
 * @Author: Sunist Chan
 * @Date: 2021-03-29 05:33:50
 * @LastEditTime: 2021-03-29 05:51:54
 * @LastEditors: Sunist Chan
 * @Description: 
 * @FilePath: /2021-LQC-Trainning/docs/week-1/lqc-skills.md
-->
# 蓝桥杯做题技巧 #

> 请注意，除非特殊说明，所有的代码片段均为C/C++代码

## 1. 递归的使用 ##

### 1.1 什么是递归 ###

递归，英文为`Recursion`，在数学与计算机科学中，是指在函数的定义中使用函数自身的方法。

这个定义主要有两层含义：

+ 递归要有一个函数
+ 这个函数要调用自己

我们举一个实际的例子，这个用例是数学领域的：

$$
\begin{aligned}
n! =& n \times(n-1)! \\
1! =& 1
\end{aligned}
$$

即：n的阶乘是n-1的阶乘乘上n。特殊的，1的阶乘为1。

我们用代码来实现它：

```cpp
int Factorial(int n) {
    if (n == 1) {
        return 1;
    }
    else {
        return n * Factorial(n-1);
    }
}
```

这样子我们可以很方便的将一些能够用递推公式表示的函数(方法)用递归代码写出来，又比如大名鼎鼎的`Fibonacci`数列：

$$
\begin{aligned}
Fib(1) =& 1 \\
Fib(2) =& 1 \\
Fib(n) =& Fib(n-1) + Fib(n-2), \quad n \geq 3
\end{aligned}
$$

用代码表示就是：

```cpp
int Fibonacci(int n) {
    if (n == 1 || n == 2) {
        return 1
    }
    else {
        return Fibonacci(n-1) + Fibonacci(n-2);
    }
}
```

我们通过观察上面两个递归函数可以发现他们的共同特点：

+ 都有一个或若干个`if/else`语句来区分特殊情况
+ 都有一个或若干个情况函数调用了它自身来计算结果

其中，我们将用于定义特殊情况的`if (case == ${exit_case})`语句称为递归出口。请注意，**如果一个递归函数没有递归出口，那么这个函数将无限运行下去直到内存溢出**。