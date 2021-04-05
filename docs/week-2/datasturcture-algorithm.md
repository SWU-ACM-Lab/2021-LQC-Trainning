# 数据结构算法

## 最小生成树

### 生成树

兄贵，学习MST​之前先来了解一下什么是生成树吧，概念如下

> 对于无向带权图G和一棵树T来说，如果T是G的子图，则称T为G的树，如果T是G的生成子图，则称T是G的生成树。
>
> 简而言之，生成树是一个极小连通子图，它含有图中全部顶点，但只有n-1条边。

### 最小生成树

最小生成树$(Minimum\ cost\ Spanning\ Tree)$，就是所有生成树中各边权值之和最小的那个生成树。

[![cMEOte.png](https://z3.ax1x.com/2021/04/05/cMEOte.png)](https://imgtu.com/i/cMEOte)


> **构造最小生成树的准则**
>
> - 必须只使用该网络中的边来构造最小生成树；
> - 必须使用且仅使用*n*-1条边来联结网络中的*n*个顶点；
> - 不能使用产生回路的边。

对于最小生成树，常见的生成算法有两种：$Kruskal$算法和$Prim$算法，[参考链接](https://www.bilibili.com/video/BV1Eb41177d1?from=search&seid=5353145092427265999)

### $Kruskal$算法

**定义**

此算法可以称为“加边法”，初始最小生成树边数为0，每迭代一次就选择一条满足条件的最小代价边，加入到最小生成树的边集合里。（贪心思想）

**具体步骤**

1. 把图中的所有边按代价从小到大排序； 

2. 把图中的$n$个顶点看成独立的$n$棵树组成的森林； 

3. 按权值从小到大选择边，所选的边连接的两个顶点$ui,vi$。$ui,vi$,应属于两颗不同的树，则成为最小生成树的一条边，并将这两颗树合并作为一颗树。 

4. 重复3,直到所有顶点都在一颗树内或者有$n-1$条边为止。

**步骤演示**

[![cMEXfH.png](https://z3.ax1x.com/2021/04/05/cMEXfH.png)](https://imgtu.com/i/cMEXfH)

### Prim算法

**定义**

此算法可以称为“加点法”，每次迭代选择代价最小的边对应的点，加入到最小生成树中。算法从某一个顶点$s$开始，逐渐长大覆盖整个连通网的所有顶点。

**具体步骤**

1. 从任意一个顶点开始构造生成树，将该顶点加入生成树中，用一个一维数组selected来标记哪些顶点已经加入了生成树。

2. 用数组$minDist$记录生成树到各个顶点的距离，最初生成树中之后1号 顶点，有直连边时，数组$minDist$中存储的就是1号顶点到该顶点的边的权值，没有直连边的时候就是INF，即初始化$minDist$数组。

3. 从数组$minDist$中选出离生成树最近的顶点（假设这个顶点为j）加入到生成树中（即在数组$minDist$中找到最小值）。再以j为中间点，更新生成树到每一个非树顶点的距离（松弛）， 即如果$minDist[k]>e[j][k]$则更新$minDist[k]=e[j][k]$。

4. 重复第三步，直到生成树中有n个顶点为止。

**步骤演示**

[![cMELkD.png](https://z3.ax1x.com/2021/04/05/cMELkD.png)](https://imgtu.com/i/cMELkD)

### 两种算法的比较

**从策略上来说**

Prim算法是直接查找，多次寻找邻边的权重最小值

Kruskal是需要先对权重排序后查找的

**从时间复杂度分析**

prim: 该算法的时间复杂度为$O(n2)$。 与图中边数无关，该算法适合于**稠密图**

kruskal: 时间复杂度为$O(eloge)$。 适合**稀疏图**

**所以说**

Kruskal在算法效率上是比Prim快的，因为Kruskal只需一次对权重的排序就能找到最小生成树；而Prim算法需要多次对邻边排序才能找到

### 练习

[P3366 【模板】最小生成树](https://www.luogu.com.cn/problem/P3366)

**Kruskal算法实现**

```c++
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int gen[5005],n,m,ans,cnt;

struct Edge{
    int u;//左边的点
    int v;//右边的点
    int w;//权值
}edge[200005];

bool cmp(Edge a,Edge b){//排序方法
    return a.w<b.w;
}
int find(int x){
    if(gen[x]==x) return x;
    return gen[x]=find(gen[x]);
}

inline void kruskal(){
    sort(edge+1,edge+m+1,cmp);//按照权值排序
    for(int i=1;i<=m;i++){
        int eu=find(edge[i].u);//找到左边点和右边点的老大
        int ev=find(edge[i].v);
        if(ev==eu){//如果老大是一个，说明这俩在一个集合中，跳过
            continue;
        }//否则
        ans+=edge[i].w;//加上权值
        gen[ev]=eu;//连接两个并查集
        cnt++;
        if(cnt==n-1){//退出的条件
            break;
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        gen[i]=i;
    }
    for(int i=1;i<=m;i++){
        cin>>edge[i].u>>edge[i].v>>edge[i].w;
    }
    kruskal();
    cout<<ans;
    return 0;
}
```

**Prim算法实现**

```c++
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
const int maxn=200001;
bool selected[maxn];//是否被选中，初始为0
int minDist[maxn];//最小值，初始为INF
int parent[maxn];//存储最小值的那个边的父亲，初始为-1，代表不存在
int n,m,cnt,ans;

struct Edge{
	int begin;
	int end;
	int longth;
}edge[maxn];

void Prim(int x){
	cnt++;
	for(int i=1;i<=m;i++){
		if(edge[i].begin==x&&minDist[edge[i].end]>edge[i].longth){
			minDist[edge[i].end]=edge[i].longth;
			parent[edge[i].end]=x;	
		}else if(edge[i].end==x&&minDist[edge[i].begin]>edge[i].longth){
			minDist[edge[i].begin]=edge[i].longth;
			parent[edge[i].begin]=x;
		}
	}
}
int main(){
	ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++){
		cin>>edge[i].begin>>edge[i].end>>edge[i].longth;
	}
	memset(minDist,0x3f3f3f,sizeof(minDist));//minDist初始化
	selected[1]=1;//先选择1加入最小生成树中
	Prim(1);//遍历查找
	while(cnt!=n){//循环
		int minn=0x3f3f3f;
		int chose=1;
		for(int i=1;i<=n;i++){
			if(!selected[i]&&minDist[i]<minn){
				minn=minDist[i];
				chose=i;
			}
		}
		selected[chose]=1;
		ans+=minn;
		Prim(chose);
	}
	cout<<ans;
	return 0;
}
```

## 并查集

### 定义

> 并查集是一种树型的数据结构，用于处理一些不相交集合的合并及查询问题。

### 应用情境

- 由于最小生成树需要维护连通性，并查集刚好可以做到通过构建树来判断元素之间的连通性、查找出两个元素是否位于同一元素。所以并查集在$MST$的建立过程中有着很大的作用
- 集合操作

### 操作

在最开始的时候，每个元素都可以看做是一个单独的集合。我们在不断地进行查询和合并（并查集）请求操作中，元素之间进行合并。

一般都会用帮派来形容并查集的操作。每个集合都有一个帮主（人为设定），他统领着集合中的所有元素；在每一次帮派大战（合并），战败的集合便会被战胜的集合吞并，战胜集合的帮主成为合并帮主的新帮主，循环往复。

执行查询操作也很简单，只需要看他们的帮主是不是一个人即可~

1.**初始化**

把每个点所在集合初始化为其自身。（自己是自己的帮主）

```c++
for(int i=1;i<=n;i++){
    f[i]=i;	//初始化
}
```

2.**查找**

> 查找元素所在的集合，即总帮主

- 普通做法（递归）

```c++
int find(int k){
    if(f[k]==k) return k;	//如果自己是自己所在集合的帮主，那它就是总帮主
    return find(f[k]);		//如果不是，就找他老大哥的老大哥
}
```

- 路径压缩

上面这种做法很慢，所以我们可以直接在查找的过程中顺便把中间人士都指向总帮主

```c++
int find(int k){
   if(f[k]==k) return k;	//如果自己是自己所在集合的帮主，那它就是总帮主
    return f[k]=find(f[k]);		//把图中的人的老大哥都变成总帮主
}
```

**3.查询**

> 查询两个元素是否在同一个集合中

```c++
if(find(p1)==find(p2)){	//如果这俩隶属于同一个帮派
    cout<<"YES"<<endl;
}else{
    cout<<"NO"<<endl;
}
```

**4.合并**

> 把两个不相交的集合合并为一个集合

```c++
f[find(a)]=find(b);		//让b和a的帮主变成一个人
```

### 练习

[P3367 【模板】并查集](https://www.luogu.com.cn/problem/P3367)

**AC代码**

```c++
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=10005;
int n,m,f[maxn];

int find(int k){
    if(f[k]==k) return k;//如果自己的老大就是自己，那它就是总老大
    return f[k]=find(f[k]);//使途中经过的人的大哥也变成老大
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        f[i]=i;//初始化i的老大为自己
    }
    for(int i=1,p1,p2,p3;i<=m;i++){
        cin>>p1>>p2>>p3;
        if(p1==1){//如果是执行合并操作
            f[find(p2)]=find(p3);//让p2的老大变成p3的老大
        }else{//查询操作
            if(find(p2)==find(p3)){//如果p2的老大和p3的老大是一个人
                cout<<"Y"<<endl;
            }else{
                cout<<"N"<<endl;
            }
        }
    }

    return 0;
}
```

## 拓扑排序
在学习拓扑排序之前，我们先来了解什么事AOV网。
### AOV网
>- 用顶点表示活动，用弧表示活动间优先关系的**有向图**称为顶点表示活动的网(Activity On Vertex network)，简称AOV网。
>- 在网中，若从顶点$i$到顶点$j$有一条有向路径，则$i$是$j$的前驱，$j$是$i$的后继。若$<v_i,v_j>$是图中有向边，则$v_i$是$v_j$的直接前驱；$v_j$是$v_i$的直接后继。
>- **AOV网中不允许有回路**，这意味着某项活动以自己为先决条件。
>- **对于给定的AOV网应首先判定网中是否存在环**。检测的办法是对有向图构造其顶点的**拓扑有序序列**，若网中所有顶点都在它的拓扑有序序列中，则该AOV网必定不存在环。
[![AOV.png](https://z3.ax1x.com/2021/04/05/cMtvOf.png)](https://imgtu.com/i/cMtvOf)

拓扑排序就是在AOV的基础上进行的。
### AOE网
>AOE网(Activity On Edge)：也叫边表示活动的网。AOE网是一个带权的有向无环图，其中顶点表示事件，弧表示活动，权表示活动持续时间
### 定义
>拓扑排序(Topological Sort) 是由某个集合上的一个偏序得到该集合上的一个全序，这个操作就称之为拓扑排序。

例如，一个软件专业的学生必须学习一系列基本课程，其中有些课是基础课，它独立于其它课程，如《高等数学》；而另一些课程必须在学完作为它的基础的先修课程才能开始。如在《程序设计基础》和《离散数学》学完之前就不能开始学习《数据结构》。
### 构造方法
>- 选择一个入度为 0 的顶点并输出。
>- 从 AOV 网中删除此顶点及以此顶点为起点的所有关联边。
>- 重复上述两步，直到不存在入度为 0 的顶点为止。
>- 若输出的顶点数小于 AOV 网中的顶点数，则说明 AOV 网中回路，不是一个标准的 AOV 网。

[![cMtbYd.png](https://z3.ax1x.com/2021/04/05/cMtbYd.png)](https://imgtu.com/i/cMtbYd)

[更加具体的过程请参考](https://www.bilibili.com/video/BV1Ut41197TE?from=search&seid=17211423774363355925)

### 练习
接下来我们来练习一道有关拓扑排序的[题目](http://acm.hdu.edu.cn/showproblem.php?pid=1285)。
>这道题是一道简单的拓扑排序，题中已经给出了`具体的提示`(其他说明：符合条件的排名可能不是唯一的，`此时要求输出时编号小的队伍在前`；输入数据保证是正确的，即输入数据确保一定能有一个符合要求的排名)。
正是练习拓扑排序的好机会。

#### AC代码
```c++
#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;
const int maxn=1000;
vector<int>vec[maxn]; // 邻接表建图。
int du[maxn];
int n,m;
void topsort(){
	priority_queue<int,vector<int>,greater<int> > s;//使用优先队列，来保证输出时编号小的队伍在前
	int flag=0;
	for(int i=1;i<=n;i++)
	{
		if(!du[i])//将入度为0的节点入队
			s.push(i);
	}
	while(!s.empty())
	{
		int now=s.top();
       	  s.pop();
		if(flag==0)
		{
			cout<<now;
			flag=1;
		}
		else
			cout<<" "<<now; // 最后一名没有空格
		
		for(int i=0;i<vec[now].size();i++) //除去与该节点相关的节点的关联边。
		{
			if(--du[vec[now][i]]==0)	
				s.push(vec[now][i]);
		}
	}
}
int main(){

	while(cin>>n>>m)
	{
		memset(du,0,sizeof(du));
		for(int i=1;i<=n;i++)
			vec[i].clear();
		for(int i=1;i<=m;i++)
		{
			int a,b;
			cin>>a>>b;
			vec[a].push_back(b);
			du[b]++;
		}
		topsort();
		cout<<endl;
	}
	return 0;	
} 
```
[如果有兴趣可以试试做下这道题，判断图中是否有环](http://acm.hdu.edu.cn/showproblem.php?pid=3342)
## 最短路
### 定义
>如果从图中某一顶点(称为源点)到达另一顶点(称为终点)的路径可能不止一条，如何找到一条路径，使得沿此路径各边上的权值总和达到最小。

解决这个问题，我们有两种算法：Dijkstra算法 和 Floyd算法。
### Dijkstra算法
Dijkstra算法是单源最短路径，也就是说一个点到其他所有点的最短路径。
**它的主要思想就是根据已经确定了的点的距离，来确定该点相邻顶点的距离，不断的向外散射，直到所以的点的到起点的最短距离确定为止。**  
#### 算法思想
>- 把图中所有顶点分成两组，第一组包括已确定最短路径的顶点，第二组包括尚未确定最短路径的顶点，按最短路径长度递增的顺序逐个把第二组的顶点加到第一组中去，直至从$v_0$出发可以到达的所有顶点都包括到第一组中。
>- 在这过程中，总保持从$v_0$到第一组各顶点的最短路径长度都不大于从$v_0$到第二组的任何顶点的最短路径长度。
#### 求解步骤
>- 一开始第一组只包括顶点$v_0$，第二组包括其他所有的顶点，$v_0$对应的距离为0。
>- 第二组的顶点对应的距离是这样确定的：若图中有边$<v_0，v_i>$， vi的距离为此边所带的权值，否则$v_i$的距离为一个很大的数（大于所有顶点间的路径长度）。
>- 然后每次从第二组的顶点中选一个其距离值为最小的$v_m$加入到第一组中。
>- 每往第一组加入一个顶点$v_m$ ，就要对第二组中的各个顶点的距离值进行一次修正。若加进$V_m$做中间顶点使从$v_0$到$v_j$的最短路径比不加$v_m$的路径为短，则要修改$v_j$的距离值。修改后再选距离值最小的顶点加入到第一组中。
>- 重复3和4步骤直至所有点都在第一组中

[动画演示](https://www.bilibili.com/video/BV1q4411M7r9?from=search&seid=4117483000935554948)
#### 时间复杂度
>$O(n^2)$
#### 代码
这里可以尝试一下[这道题](https://www.luogu.com.cn/problem/P4779), 这道题对其算法进行了堆优化。
```c++
...
```
### Floyd算法
Floyd算法是每一对顶点之间的最短路径。在此有两种解决方法：每次以一个顶点为源点，重复执行Dijkstra算法n次 和 弗洛伊德(Floyd)算法。
#### 算法思想
逐个顶点试探
>- 初始时设置一个$n$阶方阵，令其对角线元素为$0$，若存在弧$<vi,vj>$，则对应元素为权值；否则为$\infty$。
>- 逐步试着在原直接路径中增加中间顶点，若加入中间点后路径变短，则修改之；否则，维持原值。
>- 所有顶点试探完毕，算法结束。

[详细过程](https://www.bilibili.com/video/BV1LE411R7CS?from=search&seid=4295088178287909313)

#### 时间复杂度
Floyd算法的时间复杂度和重复执行Dijkstra算法n次的时间复杂度相同都是$O(n^3)$。但是Floyd的形式更加简单。

## 强连通分量

### Tarjon算法

### Kosaraju算法

### Gabow算法