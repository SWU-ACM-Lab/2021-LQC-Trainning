# STL学习

> STL即标准模板库(Standard Template Library)，隶属于C++标准库，包含了一些常用的模板化的数据结构和算法。STL作为模板，拥有极强的兼容性和普适性，大大提高了我们编写代码的效率，使得其在各大算法比赛中都得到了广泛的应用。

本文将STL的学习分为两个板块：`container`和`algorithm`

## 容器container

![img](https://oi-wiki.org/lang/csl/images/container1.png)

### 向量Vector

> `std::vector`是STL提供的能够存放任意类型的、内存连续的、**可变长度（动态）**的数组，可以提供线性复杂度的插入和删除。

#### Vector的优良特性

- 可以动态分配内存
  - `vector`不像`c++`中普通数组一样需要在定义时设定大小，支持动态扩容，即数组的大小会随着你的插入/删除而变大/变小
  - 允许存储的size也要比普通数组大
- 便利的初始化
- 自带常用的函数

#### Vector使用方法

##### 构造函数

为了可以使用vector，请在你的头文件中包含`#include<vector>`

```c++
// 提示，T代表数据类型，可以是int/string/...，也可以是自己定义的数据类型
vector<T> v1;	//定义一个空的vector v1,元素类型为T,这也是我们最常用的一种初始化方法
vector<T> v2(v1);	//v2中包含v1所有元素的副本
vector<T> v2 = v1;	//等价于v2(v1)
vector<T> v3(n,val);	//v3包含了n个重复的元素，每个元素的值都是val
vector<T> v4(n);	//v4包含了n个重复执行了值初始化的对象，换而言之就是规定了v4的size
vector<T> v5{a,b,c...};		//v5包含了初始化个数的元素，每个元素被赋予相应的初始值
vector<T> v5={a,b,c...};	//等价于上条
```

##### 元素的增删改

- `v.push_back(element)`：在尾部插入元素element
- `v.pop_back()`：在尾部删除一个元素
- `v.insert(pos,n,element)`：在pos位置前增加n个相同的元素element，n可省略不写，默认添加一个
- `v.erase(begin,end)`：删除v中`[begin,end)`范围内的所有元素

- `v.clear()`：清除所有元素

##### 元素的访问

- `v.at(pos)`：返回v中pos位置的引用
- `v.front()`：返回v中首元素的引用
- `v.back()`：返回v中尾元素的引用
- `v.data()`：返回指向数组第一个元素的指针

##### 迭代器

> 迭代器(Iterator)用来访问和检查STL容器中的对象，可以看作是一个数据指针
>
> 学过指针的朋友可以很简单的理解这里hahah

- `v.begin()`：返回指向v中首元素的迭代器，其中`*begin=front`
- `v.end()`：返回指向v中尾元素的迭代器，其中`*end=back`

##### 长度和容量

- `v.empty()`：若v为空返回`true`，非空返回`false`
- `v.size()`：返回v的元素个数（长度）
- `v.resize()`：改变v的长度

##### 容器的遍历

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

## 算法algorhtim



