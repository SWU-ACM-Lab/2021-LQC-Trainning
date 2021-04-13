# 计算几何基础入门

计算几何是由微分几何、代数几何、数值计算、逼近论、拓扑学以及数控技术等形成的一门新兴边缘学科，其主要研究对象和内容是对自由形曲线、曲面的数学描述、设计、分析及图形的显示、处理等。

## 对于浮点数的处理
**不要直接用等号判断浮点数是否相等！**
>同样的一个数1.5。如果从不同的途径计算得来，它们的储存方式可能会是a=1.4999999 与 b=1.5000001，此时使用a==b判断将返回false。

所以我们引入一个什么小的量 `eps`,在对浮点数进行大小比较时，如果他们的
差的绝对值小于这个量，那么我们就认为他们是相等的。`eps`在大部分题目时取 `1e-8`或者`1e-9` 就够了，但要根据题目实际的内容进行调整。

### 代码模板
```c++
const double eps = 1e-8;
bool dcmp(double x, double y){
    if(fabs(x - y) < eps){// 这里注意要使用fabs()，不能用abs().
        return 0;//两数相等
    }else if(x > y){
        return 1; //  x > y
    }
    return -1;
}
```

### 浮点树输入输出
用 scanf 输入浮点数时， double 的占位符是 %lf ，但是浮点数 double 在 printf 系列函数中的标准占位符是 %f 而不是 %lf ，使用时最好使用前者。


### 开方
我们一般使用的是double sqrt (double x)函数来进行对正数的开方，但是当输入负数时,sqrt 会返回 nan ，输出时会显示成 nan 或 -1.#IND00 （根据系统的不同）。如果对一个几乎接近0的负数，由上面的误差分析可以知道，这个负数与0相等，但是开方不能得到正确的答案。那么这时我们就需要自定义一个函数了。
```c++
double mySqrt(double x) {
    return max(0.0,sqrt(x));
}
```

### 负零
输出时一定要小心不要输出 −0，比如
```c++
double a = -0.000001;
printf("%.4f", a);
// -0.0000
```

### 取整
```c++
    int fx = floor(x);//向下取整函数
    int cx = ceil(x);//向上取整函数
    int rx = round(x);//四舍五入函数

```

## 向量
简单来说，既有大小又有方向的量叫做向量在计算机中我们常用坐标表示

### 点的定义
我们使用结构体来存储点
```c++
struct Pt {
    double x, y;//必要时使用int
    Pt(double x, double y): x(x), y(y) { }
};
```

### 向量计算
在高中和大学中，我们已经学过了向量的加减法，就不给出公式了。
#### 加法
>$\overrightarrow{A} +\overrightarrow{B} = \overrightarrow{AB}$
```c++
pt operator + (pt A, pt B){
    return pt(A.x+B.x, A.y+B.y);
} 
```

#### 减法
>$\overrightarrow{A} -\overrightarrow{B} = \overrightarrow{BA}$
```c++
pt operator - (pt A, pt B){
    return pt(A.x-B.x, A.y-B.y);
} 
```

#### 数乘
向量的数乘是一个向量和实数的运算。
```c++
pt operator * (double A, pt p) { 
    return pt(p.x*A, p.y*A);
}
pt operator * (pt p, double A) { 
    return pt(p.x*A, p.y*A);
}

```
#### 点乘
```c++
double dot(pt A, pt B){
    return A.x*B.x + A.y*B.y; 
}
```
##### 应用
点积可以用来计算两向量的夹角。
$\cos\theta = \frac{\overrightarrow{a}\cdot\overrightarrow{b}}{|a|\cdot |b|}$
#### 叉积
$A \times B = |A||B|Sin(\theta)$
$A \times B = x_1y_2 – y_1x_2$
```c++
double det(pt A, pt B) { return A.x * B.y - A.y * B.x; }
```
##### 应用
- 计算两个两个构成的平行四边形面积或者三角形面积
- 根据$sin\theta$的出现的正负来判断A与B向量的方向
#### 除法
```c++
pt operator / (pt A, double p){
    return pt(A.x/p, A.y/p);
}
```
#### 等于运算
```c++
bool operator == (const Point& A, const Point& B){
    if(dcmp(A.x-B.x) == 0 && dcmp(A.y-B.y) == 0)
        return true;
    return false;
}
```
#### 长度
```c++
double Length(pt A){
    return mySqrt(Dot(A, A));
}

double Length(pt A){
    return mySqrt(Dot(A, A));
}
```
## 线段


