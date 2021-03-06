<!--
 * @Author: Jaron
 * @Date: 2021-04-12 16:14:57
-->
## 简介

贪心算法是指在每一步求解的过程中选择最优操作，通过一步步的迭代，最终获得问题的最优解。  

可想而知，并不是所有的时候贪心法都能获得最优解，所以一般使用贪心法的时候，都要确保自己能证明其正确性，即通过每一小步的最优操作，不断迭代获得的最终结果是问题的最优解。

## 适用范围

贪心算法在有最优子结构的问题中尤为有效。最优子结构的意思是问题能够分解成子问题来解决，子问题的最优解能递推到最终问题的最优解。

## 证明方法

贪心算法有两种证明方法：反证法和归纳法。一般情况下，一道题只会用到其中的一种方法来证明。

1. 反证法：如果交换方案中任意两个元素/相邻的两个元素后，答案不会变得更好，那么可以推定目前的解已经是最优解了。
</br>

2. 归纳法：先算得出边界情况（例如${n = 1}$）的最优解${F_1}$，然后再证明：对于每个${n}$,$F_{n+1}$，都可以由${F_n}$推导出结果。

## 与动态规划的区别

贪心算法与动态规划的不同在于它对每个子问题的解决方案都做出选择，不能回退。动态规划则会保存以前的运算结果，并根据以前的结果对当前进行选择，有回退功能。

## 例题详解

<a href="https://www.luogu.com.cn/problem/P1090">题目传送：合并果子</a>

>解题思路:每次合并最小的那两堆果子，直到剩下只有一堆为止

>本题的证明请参考生成最优二叉树即哈夫曼树