# DP(动态规划)基础入门

在此，一定要强调的一件事，DP不像DFS、BFS、二分等这样的算法，有着固定的格式，**DP是一种思想**，虽然代码在一定程度上有迹可循，但是，更多的是思考和发现模型的能力。所以有关于动态规划的部分将会区便于其他部分，会有更少的代码，而去展示更多的思考过程和理论知识。



## 动态规划中的重要性质

首先，我们说一下DP里你看了也不一定会懂的三个性质。

### 具有最优子结构

最优子结构可这样阐述：一个最优化策略具有这样的性质，不论过去状态和决策如何，对前面的决策所形成的状态而言，余下的诸决策必须构成最优策略。简而言之，一个最优子结构的子策略总是最优的。

### 状态无后效性

将各阶段按照一定的次序排列好之后，对于某个给定的阶段状态，它以前各阶段的状态无法直接影响它未来的决策，而只能通过当前的这个状态。换句话说，每个状态都是过去历史的一个完整总结。这就是无后效性。

### 有重叠子问题

动态规划算法的关键在于解决冗余，这是动态规划算法的根本目的。动态规划实质上是一种以空间换时间的技术，它在实现的过程中，存储过程中产生的各种状态，所以它的空间复杂度要大于其他的算法。选择动态规划算法是因为动态规划算法在空间上可以承受，而搜索算法在时间上却无法承受，所以我们舍空间而取时间。同时，这点也是DP和分治的区别。

***

好了，说完这三点性质，你理解DP了吗？反正我当初看完是一头雾水。其实究其本质，**DP就是将解题过程中的一些数据存储起来，来避免我们的重复计算，以此达到节省时间的目的。**

DP最关键的只有两步：1、确定这题是DP的题。2、找出状态转移方程。

首先，如何确定这题是不是DP的题。刚入门的这个阶段，我们只能多去做题，去体悟，慢慢的，你就会理解上面DP的重要的三个性质究竟意味着什么，你就会明白这题为什么会采取DP，而不是其他的算法。

其次，关于状态转移方程，定义是：动态规划中本阶段的状态往往是上一阶段状态和上一阶段决策的结果。若给定了第$K$阶段的状态$Sk$以及决策$uk(Sk)$,则第$K+1$阶段的状态$Sk+1$也就完全确定。也就是说$Sk+1$与$Sk,uk$之间存在一种明确的数量对应关系，记为$Tk(Sk,uk)$,即有$Sk+1= Tk(Sk,uk)$。 这种用函数表示前后阶段关系的方程，称为状态转移方程。

估计看完你也晕了，完全不能理解他说的是什么。其实状态转移方程一般情况下就是一个等式，它在类似的题目里一般是有迹可循的，通过后面的例题讲解，估计你也能很快的领悟到，这里我们就不多说了。



下面，我们来具体讲解DP题的求解过程。

# DP题求解的三大步骤

### 定义数组元素的含义

上面我们提到，**DP就是将解题过程中的一些数据存储起来，来避免我们的重复计算**。在通常情况下，我们是用**一维数组**或者**二维数组**来保存这些数据的(至少我目前遇到的题都是这样的)。

假设用一维数组 dp[] 吧。这个时候有一个非常非常重要的点，就是规定你这个数组元素的含义，例如你的 dp[i] 是代表什么意思？具体的意思，讲例题的时候你们肯定能明白。

### 找出数组元素之间的关系式(其实就是状态转移方程)

当我们要计算$dp[n]$时，是可以利用$dp[n-1],dp[n-2],\cdots,dp[1]$，来推出$dp[n]$的，也就是可以利用**历史数据**来推出新的元素值，所以我们要找出数组元素之间的关系式，例如$dp[n]=dp[n-1]+dp[n-2]$，这个就是他们的关系式了。而这一步，也是最难的一步，后面我会讲几种类型的题来说。

### 找出初始值

虽然我们知道了数组元素之间的关系式，例如$dp[n]=dp[n-1]+dp[n-2]$，我们可以通过$dp[n-1]$和$dp[n-2]$来计算$dp[n]$，但是，我们得知道初始值啊，例如一直推下去的话，会有$dp[3]=dp[2]+dp[1]$。而$dp[2]$和$dp[1]$是不能再分解的了，所以我们必须要能够直接获得$dp[2]$和$dp[1]$的值，而这，就是**所谓的初始值**。

***

下面，我们将通过几道例题来走进DP的世界.

### 例1、简单的一维 DP

问题描述

```
一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法。
```

这题是最经典的一道DP入门题，具体有多经典，后面上算法课的时候你就知道了。

下面，我们开始按照上面给定的步骤来进行求解。

#### 定义数组元素的含义

我们的问题是要求青蛙跳上$n$级的台阶总共由多少种跳法，那我们就定义$dp[i]$的含义为：跳上一个$i$级的台阶总共有$dp[i]$种跳法。这样，如果我们能够算出$dp[n]$，那么，这题我们就解出来了。

#### 找出数组元素之间的关系式

就是把一个**规模**比较大的问题分成几个**规模**比较小的问题，然后由小的问题推导出大的问题。也就是说，$dp[n]$的规模为$n$，比它规模小的是$n-1, n-2, n-3,\cdots$也就是说，$dp[n]$一定会和$dp[n-1], dp[n-2],\cdots$存在某种关系的。我们要找出他们的关系。最大的问题就是，怎么找？

对于这道题，由于情况可以选择跳一级，也可以选择跳两级，所以青蛙到达第 n 级的台阶有两种方式：

一种是从第$n-1$级跳上来

一种是从第$n-2$级跳上来

由于我们是要算**所有可能的跳法的**，所以有$dp[n]=dp[n-1] + dp[n-2]$。

#### 找出初始值

当$n=1$时，$dp[1] = dp[0] + dp[-1]$，而我们是数组是不允许下标为负数的，所以对于$dp[1]$，我们必须要直接给出它的数值，相当于初始值，显然，$dp[1] = 1$。一样，$dp[0] = 0$.（因为 0 个台阶，那肯定是 0 种跳法了)，同时，要注意$dp[2]$这个情况，我们简单的计算，能发现$dp[2]=2$，是不满足$dp[2]=dp[1]+dp[0]$的，于是得出初始值：$dp[0] = 0,dp[1] = 1,dp[2]=2$

三个步骤都做出来了，那么我们就来写代码吧。

```c++
#include<iostream>
using namespace std;
int main(){
    int dp[MAX];//数组的大小取决于n的最大取值,请根据具体的题目进行替换MAX
    dp[0] = 0,dp[1] = 1，dp[2] = 2;//初始化初始值
    // 通过关系式来计算出 dp[n]
    for(int i = 2; i <= n; ++i){
        dp[i] = dp[i-1] + dp[i-2];
    }
    cout<<dp[n];//根据题目要去输出答案
    return 0;
}
```

这样，这道dp的题就做出来了，是不是感觉比起定义来还是很简单的。

这里附上两个相似的题，希望大家自己能去做一做，好好体悟一下

[洛谷P1255 数楼梯](https://www.luogu.com.cn/problem/P1255)

[洛谷P1192 台阶问题](https://www.luogu.com.cn/problem/P1192)

***

### 例2、二维数组的 DP

问题描述

```
一个NxN的网格，你一开始在(1,1)(1,1)，即左上角。每次只能移动到下方相邻的格子或者右方相邻的格子，问到达(N,N)(N,N)，即右下角有多少种方法。
```

我们依旧按照上面给定的步骤来进行求解。

#### 定义数组元素的含义

由于我们的目的是从左上角到右下角一共有多少种路径，那我们就定义$dp[i] [j]$的含义为：当机器人从左上角走到$(i, j)$这个位置时，一共有$dp[i] [j]$种路径。那么，$dp[m][n]$就是我们要的答案了。

注：此处为了方便理解，我们将数组下标从1开始算起。

#### 找出关系数组元素间的关系式

想象以下，机器人要怎么样才能到达$(i, j)$这个位置？由于机器人可以向下走或者向右走，所以有两种方式到达：

一种是从$(i-1, j)$这个位置走一步到达

一种是从$(i, j - 1)$这个位置走一步到达

因为是计算所有可能的步骤，所以是把所有可能走的路径都加起来，所以关系式是$dp[i] [j] = dp[i-1] [j] + dp[i] [j-1]$。

#### 找出初始值

显然我们的初始值是计算出所有的$dp[1][1,\cdots,n]$和所有的$dp[1,\cdots,m] [1]$。这个还是非常容易计算的，相当于计算机图中的最上面一行和左边一列。因此初始值如下：

$dp[1][1,\cdots,n]=1$; // 相当于最上面一行，机器人只能一直往右走

$dp[1,\cdots,m][1]=1$; // 相当于最左面一列，机器人只能一直往下走



三个步骤都写出来了,直接写代码

```c++
#include <iostream>
using namespace std;
int main(){
    int dp[M][N]; //数组的大小取决于题目给的M，N的大小，请根据具体的题目进行替换
    // 初始化
    for(int i = 1; i <= m; i++){
      dp[i][1] = 1;
    }
    for(int i = 1; i <= n; i++){
      dp[1][i] = 1;
    }
    //很明显，我们这里的计算是从2开始的
    for (int i = 2; i <= m; i++) {
        for (int j = 2; j <= n; j++) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];//推导出来的状态转移方程
        }
    }
    cout<<dp[m][n];//根据题目要去输出答案
    return 0;
}
```

至此，这题结束。下面给大家一个这题的变种，希望大家能够完成它，找一找感觉。

[洛谷P1176 路径计数2](https://www.luogu.com.cn/problem/P1176)

***

### 例3、编辑距离

[洛谷P2758 编辑距离](https://www.luogu.com.cn/problem/P2758)

这道题比较难，并且还牵扯到了字符串的处理，希望大家能够好好的去学习理解。

题目描述

```
设A和B是两个字符串。我们要用最少的字符操作次数，将字符串A转换为字符串B。这里所说的字符操作共有三种：

1、删除一个字符；

2、插入一个字符；

3、将一个字符改为另一个字符；

！皆为小写字母！

示例：
输入: word1 = "horse", word2 = "ros"
输出: 3
解释: 
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')
```

我们依旧按照上面给定的步骤来进行求解。

#### 定义数组元素的含义

由于我们的目的求将 word1 转换成 word2 所使用的最少操作数 。那我们就定义$dp[i] [j]$的含义为：当字符串 word1 的长度为 $i$，字符串 word2 的长度为$j$ 时，将 word1 转化为 word2 所使用的最少操作次数为$dp[i] [j]$

这题的数组定义比较不直观，如何定义数组的含义，没有简单的套路，只有靠自己多练DP的题去感悟，希望同学们下来多练习。

#### 找出关系数组元素间的关系式

接下来我们就要找$dp[i] [j]$元素之间的关系了，比起其他题，这道题相对比较难找一点，但是，不管多难找，大部分情况下，$dp[i] [j]$和$dp[i-1] [j]$、$dp[i] [j-1]$、$dp[i-1] [j-1]$肯定存在某种关系。因为我们的目标就是，从规模小的，通过一些操作，推导出规模大的。对于这道题，我们可以对 word1 进行三种操作

插入一个字符 删除一个字符 替换一个字符

由于我们是要让操作的次数最小，所以我们要寻找最佳操作。那么有如下关系式：

一、如果我们$word1[i]$与$word2 [j]$相等，这个时候不需要进行任何操作，显然有$dp[i] [j] = dp[i-1] [j-1]$。（别忘了$dp[i] [j]$的含义哈）。

二、如果我们$word1[i]$与$word2[j]$不相等，这个时候我们就必须进行调整，而调整的操作有 3 种，我们要选择一种。三种操作对应的关系试如下（注意字符串与字符的区别）：

（1）如果把字符$word1[i]$替换成与$word2[j]$相等，则有$dp[i][j]=dp[i-1][j-1]+1$;

（2）如果在字符串$word1$末尾插入一个与 word2[j] 相等的字符，则有$dp[i][j]=dp[i][j-1]+1$;

（3）如果把字符$word1[i]$删除，则有$dp[i][j]=dp[i-1][j]+1$;

那么我们应该选择一种操作，使得$dp[i][j]$的值最小，显然有

$dp[i] [j] = min(dp[i-1] [j-1]，dp[i] [j-1]，dp[[i-1] [j]]) + 1$;

于是，我们的关系式就推出来了

#### 找出初始值

显然，当$dp[i][j]$中，如果$i$或者$j$有一个为$0$，那么还能使用关系式吗？答是不能的，因为这个时候把 $i - 1$或者$j - 1$，就变成负数了，数组就会出问题了，所以我们的初始值是计算出所有的$dp[0] [0,\dots,n]$和所有的$dp[0,\cdots,m][0]$。这个还是非常容易计算的，因为当有一个字符串的长度为$0$时，转化为另外一个字符串，那就只能一直进行插入或者删除操作了。



下面开始写代码

```c++
#include <iostream>
#include <cstring>
using namespace std;
int main(){
    string word1,word2;
    cin>>word1>>word2;
    int n1 = word1.length();
    int n2 = word2.length();
    int dp[N1][N2];//数组的大小取决于题目给的N1，N2的大小，请根据具体的题目进行替换
    // dp[0][0,...,n2]的初始值
    for (int j = 1; j <= n2; j++) 
        dp[0][j] = dp[0][j - 1] + 1;
    // dp[0,...,n1][0] 的初始值
    for (int i = 1; i <= n1; i++) dp[i][0] = dp[i - 1][0] + 1;
        // 通过公式推出 dp[n1][n2]
    for (int i = 1; i <= n1; i++) {
        for (int j = 1; j <= n2; j++) {
            // 如果 word1[i] 与 word2[j] 相等。第 i 个字符对应下标是 i-1
            if (word1[i-1] == word2[j-1]){
                p[i][j] = dp[i-1][j-1];
            }else {
               dp[i][j] =min(min(dp[i - 1][j - 1], dp[i][j - 1]), dp[i - 1][j]) + 1;
            }         
        }
    }
    cout<<dp[n1][n2];
    return 0;
}
```

***

上面的这些题，基本都是不怎么难的入门题，除了最后一道相对难一点,希望大家能够多理解，下来多去练习。