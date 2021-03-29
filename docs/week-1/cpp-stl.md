# STL学习

> STL即标准模板库(Standard Template Library)，隶属于C++标准库，包含了一些常用的模板化的数据结构和算法。STL作为模板，拥有极强的兼容性和普适性，大大提高了我们编写代码的效率，使得其在各大算法比赛中都得到了广泛的应用。

本文将STL的学习分为两个板块：`container`和`algorithm`，各个板块只介绍一些在ACM/ICPC等比赛中常用的函数和功能，如果哪里有内容错误还请同学们海涵和反馈。

## 容器container

![img](https://oi-wiki.org/lang/csl/images/container1.png)

### 一、向量Vector

> `std::vector`是STL提供的能够存放任意类型的、内存连续的、**可变长度（动态）**的数组，可以提供线性复杂度的插入和删除。

#### Vector的优良特性

- 可以动态分配内存
  - `vector`不像`c++`中普通数组一样需要在定义时设定大小，支持动态扩容，即数组的大小会随着你的插入/删除而变大/变小
  - 允许存储的size也要比普通数组大
- 便利的初始化
- 自带常用的函数

#### Vector使用方法

**1.构造函数**

为了可以使用vector，请在你的头文件中包含`#include<vector>`

```c++
// 提示，T代表数据类型，可以是int/string/...，也可以是自己定义的数据类型
vector<T> v1;				//定义一个空的vector v1,元素类型为T,这也是我们最常用的一种初始化方法
vector<T> v2(v1);			//v2中包含v1所有元素的副本
vector<T> v2 = v1;			//等价于v2(v1)
vector<T> v3(n,val);		//v3包含了n个重复的元素，每个元素的值都是val
vector<T> v4(n);			//v4包含了n个重复执行了值初始化的对象，换而言之就是规定了v4的size
vector<T> v5{a,b,c...};		//v5包含了初始化个数的元素，每个元素被赋予相应的初始值
vector<T> v5={a,b,c...};	//等价于上条
```

**2.元素的增删改**

- `v.push_back(element)`：在尾部插入元素element
- `v.pop_back()`：在尾部删除一个元素
- `v.insert(pos,n,element)`：在pos位置前增加n个相同的元素element，n可省略不写，默认添加一个
- `v.erase(begin,end)`：删除v中`[begin,end)`范围内的所有元素

- `v.clear()`：清除所有元素

**3.元素的访问**

- `v.at(pos)`：返回v中pos位置的引用
- `v.front()`：返回v中首元素的引用
- `v.back()`：返回v中尾元素的引用
- `v.data()`：返回指向数组第一个元素的指针

**4.迭代器**

> 迭代器(Iterator)用来访问和检查STL容器中的对象，可以看作是一个数据指针
>
> 学过指针的朋友可以很简单的理解这里hahah
>
> 本文章暂时只介绍常用的一些迭代器，感兴趣的同学可以自学更多

- `v.begin()`：返回指向v中首元素的迭代器，其中`*begin=front`
- `v.end()`：返回指向v中尾元素的迭代器，其中`*end=back`

**5.长度和容量**

- `v.empty()`：若v为空返回`true`，非空返回`false`
- `v.size()`：返回v的元素个数（长度）
- `v.resize()`：改变v的长度

**6.容器的遍历**

以下才是我们经常写的玩意

```c++
//1.最常用的
for(int i=0;i<v.size();i++){
    cout<<v[i]<<" ";
}
//2.利用迭代器
for(vector<int>::iterator it=v.begin();it<v.end();it++){
    cout<<*it<<endl;
}
```

### 二、双端队列Deque

> `std::deque`是STL提供的双端队列数据结构。
>
> `vector`对于头部的插入删除效率低，数据量越大，效率越低；`deque`相对而言，对头部的插入删除速度回比`vector`快
>
> `vector`访问元素时的速度会比`deque`快,这和两者内部实现有关

#### Deque的优良特性

- 随机访问的时间复杂度为常数$O(1)$
- 在结尾或起始插入或移除元素的时间复杂度均为常数$O(1)$
- 插入或溢出元素的时间复杂度同vector一样为线性$O(n)$

#### Deque使用方法

1.**构造函数**

为了可以使用deque，请在你的头文件中包含`#include<deque>`

```c++
// deque的构造函数基本同vector相同，下面只列出最常用的一种
deque<T> d;
...
```

**2.元素的增删改**

- `d.push_back(element)`：在尾部插入元素element
- `d.push_front(element)`：在头部插入元素element
- `d.pop_back()`：在尾部删除一个元素
- `d.pop_front()`：在头部删除一个元素
- `d.insert(pos,n,element)`：在pos位置前增加n个相同的元素element，n可省略不写，默认添加一个
- `d.erase(begin,end)`：删除d中`[begin,end)`范围内的所有元素
- `d.clear()`：清除所有元素

**3.元素的访问**

- `d.at(pos)`：返回d中pos位置的引用
- `d.front()`：返回d中首元素的引用
- `d.back()`：返回d中尾元素的引用
- `d[pos]`：访问d中pos位置的值

**4.长度和容量**

- `d.empty()`：若d为空返回`true`，非空返回`false`
- `d.size()`：返回d的元素个数（长度）
- `d.resize()`：改变d的长度

**5.容器的遍历**

```c++
//1.最常用的
for(int i=0;i<d.size();i++){
    cout<<d[i]<<" ";
}
//2.利用迭代器
for(deque<int>::const_iterator it=d.begin();it!=d.end();it++){
    cout<<*it<<" ";
}
//3.通过at方式访问元素
for(int i=0;i<d.size();i++){
    cout<<d.at(i)<<" ";
}
```

### 三、双向链表List

> `std::list` 是 STL 提供的**双向链表**数据结构。能够提供线性复杂度的随机访问，以及常数复杂度的插入和删除。
>
> `list` 的使用方法与 `deque` 基本相同，但是由于`list`本质是链表，不允许人们随机访问它，所以它与`deque`增删操作和访问的复杂度不同。
>
> `list` 的迭代器、长度、元素增删及修改相关的函数与 `deque` 相同，因此不作详细介绍。

#### List使用方法

由于链表的特性，若想访问中间元素，必须使用迭代器才能进行（不能随机访问），常用的两个元素访问函数如下：

- `l.front()`：访问第一个元素
- `l.back()`：访问最后一个元素

### 四、关联式容器Set

> `std::set`是STL提供的一种关联式容器，所有元素都会在插入时自动被排序。
>
> `set`和数学概念中的集合含义相同，不允许容器中存在相同元素，若将要插入的元素在集合中存在，则无法插入。
>
> `set` 内部采用红黑树实现。平衡二叉树的特性使得 `set` 非常适合处理需要同时兼顾查找、插入与删除的情况，因为它的搜索、移除和插入均为对数复杂度$O(logn)$。

#### Set的优良特性

- 增删改查的时间复杂度非常优秀，均为对数级，懂自懂
- 自动进行排序和查重操作，省了很多麻烦

#### Set使用方法

为了可以使用`set/muliset`，请在你的头文件中包含`#include<set>`

**1.元素的增删改**

- `s.insert(element)`：当s中没有element时，将该元素插入set中
- `s.erase(element)`：删除值为element的所有元素，并返回删除元素的个数
- `s.erase(pos)`：删除迭代器为 pos 的元素，要求迭代器必须合法
- `s.erase(begin,end)`：删除s中`[begin,end)`范围内的所有元素
- `s.clear()`：清空集合

**2.元素的查找和统计**

- `s.count(element)`：统计s中元素值为element的个数，在set中该值为0或1
- `s.find(element)`：若s中存在element会返回该元素的迭代器，否则返回 `end()`
- `empty()` 返回容器是否为空
- `size()` 返回容器内元素个数

**3.set指定排序规则**

```c++
//由于set默认在插入元素时将元素从小到大排序，若想不遵循此排列方式需要自定义排序规则
#include<iostream>
#include<set>
using namespace std;
class MyCompare{
public:
    bool operator()(int v1,int v2){
        return v1>v2;
    }
};
set<int>s1;	//默认排序方式，从小到大
set<int,MyCompare>s2;	////自定义排序方式，从大到小
```

#### Mulitset

> `mulitset`也存在于头文件`set`中
>
> 唯一与set不同的是，set不允许容器中有重复的元素，而multiset允许容器中有重复的元素

### 五、Pair

> `std::pair` 是标准库中定义的一个类模板。用于将两个变量关联在一起，组成一个“对”，而且两个变量的数据类型可以是不同的。
>
> 当你需要返回成对出现的数据时，可能要用到pair嗷

#### Pair使用方法

- `p.first`：访问pair的第一个数据（key），该元素起到索引作用
- `p.second`：访问pair的第二个数据（value）

#### Pair创建方法

pair的创建不需要头文件，以下是pair创建的两种方法

- `pair<type, type> p ( value1, value2 )`
- `pair<type, type> p = make_pair( value1, value2 )`

```c++
// 对这两种方法进行实例化演示
pair<string,int>p("Tom",20);
cout<<"name : "<<p.first<<endl;
cout<<"age : "<<p.second<<endl;
//第二种方式
pair<string,int>p2=make_pair("Jerry",30);
cout<<"name : "<<p2.first<<endl;
cout<<"age : "<<p2.second<<endl;
```

### 六、有序键值对容器Map

> `std::map`中的所有元素都是`pair`，所有元素都会根据元素的键值自动排序
>
> `map` 内部采用红黑树实现，红黑树的好处懂自懂
>
> 如果你需要存储一些键值对，那就可以考虑使用`map`

#### Map的优良特性

- 一对一处理数据提供了便捷
- map内部已进行自动排序

#### Map使用方法

**1.构造函数**

为了可以使用map，请在你的头文件中包含`#include<map>`

```c++
map<int,int> m; 	//创建pair类型为<int,int>的map
map<T1,T2> m;		//创建pair类型为<T1,T2>的map
map<int,int>m2(m);	//拷贝构造m2
map<int,int>m3=m;	//赋值构造m3
```

**2.元素的增删改**

- `m.insert(pair<T,T>)`：在容器中插入元素
- `m.erase(key)`：删除容器中值为key的元素
- `m.erase(pos)`：删除pos迭代器所指的元素，返回下一个元素的迭代器
- `m.erase(begin,end)`：删除m中`[begin,end)`范围内的所有元素，返回下一个元素的迭代器
- `m.clear()`：清空map

**3.元素的查找和统计**

- `m.count(key)`：统计key的元素个数，返回非0及1
- `m.find(key)`：查找key是否存在,若存在，返回该键的元素的迭代器；若不存在，返回end()
- `m.empty()` 返回容器是否为空
- `m.size()` 返回容器内元素个数

#### Multimap

map和multimap区别：

map不允许容器中有重复key值元素，multimap允许容器中有重复key值元素

### 七、栈Stack

> `std::stack`是STL提供的一种后进先出（LIFO）的容器适配器，仅支持查询或删除最后一个加入的元素（栈顶元素），不支持随机访问，且为了保证数据的严格有序性，不支持迭代器。

#### Stack使用方法

**1.构造方法**

为了可以使用stack，请在你的头文件中包含`#include<stack>`

```c++
stack<T> s;
```

**2.常用函数**

- `top()` 访问栈顶元素（如果栈为空，此处会出错）
- `push(x)` 向栈中插入元素 x
- `pop()` 删除栈顶元素
- `size()` 查询容器中的元素数量
- `empty()` 询问容器是否为空

### 八、队列Queue

> `std::queue`是STL提供的一种先进先出（FIFO）的容器适配器，仅支持查询或删除第一个加入的元素（队首元素），不支持随机访问，且为了保证数据的严格有序性，不支持迭代器。

**1.构造方法**

为了可以使用queue，请在你的头文件中包含`#include<queue>`

```c++
queue<T> s;
```

**2.常用函数**

- `front()` 访问队首元素（如果队列为空，此处会出错）
- `push(x)` 向队列中插入元素 x
- `pop()` 删除队首元素
- `size()` 查询容器中的元素数量
- `empty()` 询问容器是否为空

## 算法algorhtim

to be continued...

