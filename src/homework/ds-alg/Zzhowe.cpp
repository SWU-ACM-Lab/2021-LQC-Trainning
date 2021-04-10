//🌲的四个遍历

#include <queue>
#include <iostream>
#include <string>
using namespace std;
typedef int Status;
typedef struct BiNode
{
    int data;
    struct BiNode *lchild,*rchild;
}BiNode,*BiTree;
int PreOrderTraverse(BiTree T)
{
    if(T == NULL)
    return 0;
    else
    {
        cout << T->data;
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}
int InOrderTraverse(BiTree T)
{
    if(T == NULL)
    return 0;
    else
    {
        InOrderTraverse(T->lchild);
        cout << T->data;
        InOrderTraverse(T->rchild);
    }
}
int PostOrderTraverse(BiTree T)
{
    if(T == NULL)
    return 0;
    else
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout << T->data;
    }
}
int LevelOrderTraverse(BiTree T)
{
    if(T == NULL)
    return 0;
    queue<BiTree>q;
    q.push(T);
    q.pop();
    cout << T->data << " ";
    while(!q.empty())
    {
        if(T->lchild != NULL)
        q.push(T->lchild);
        if(T->rchild != NULL)
        q.push(T->rchild);
    }
    cout << endl;
}
int main()
{
    BiTree T;
    PreOrderTraverse(T);
    InOrderTraverse(T);
    InOrderTraverse(T);
    LevelOrderTraverse(T);
    return 0;   
}

//prim

#include <cstdio>
#include <iostream>
using namespace std;
const int Num = 100;     //最大顶点数
const int MAX = 3897987; //表示极大值
typedef int Status;
bool B[1005];
int MST_prim = 0;

typedef struct
{
    int vexs[Num];      //顶点表
    int arcs[Num][Num]; //邻接矩阵
    int vexnum, arcnum; //图当前的点数和边数
} AMGraph;

void prim(AMGraph &G)
{
    int min[1005];
    cin >> G.vexnum >> G.arcnum;
    for (int i = 1; i <= G.vexnum; ++i)
    {
        min[i] = MAX;
        B[i] = true;
    }
    min[1] = 0;
    for (int i = 1; i <= G.vexnum; ++i)
    {
        int k = 0;
        for (int j = 1; j <= G.vexnum; ++j)
        {
            if (B[j] && min[j] < min[k])
                k = j;
        }
        B[k] = false;
        MST_prim += min[k];
    }
    cout <<  MST_prim;
}
int main()
{
    AMGraph G;
    prim(G);
}

//Krus

#include <iostream>
#include <algorithm>
using namespace std;
const int Num = 100;     //最大顶点数
int pre[1004];
struct  Edge
{
    int u;
    int v;
    int w;
}E[1004];

typedef struct
{
    int vexs[Num];      //顶点表
    int arcs[Num][Num]; //邻接矩阵
    int vexnum, arcnum; //图当前的点数和边数
} AMGraph;


void Init(int x)
{
    for(int i = 1; i <= x; ++i)
    {
        pre[i] = i;
    }
}
int find(int x){
    if(pre[x]==x) 
    return x;
    else
    return pre[x]=find(pre[x]);
}
void join(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if(fx != fy)
    pre[fx] = fy;
}
bool MyCompare(Edge a , Edge b)
{
    return a.w < b.w;
}
void Krus(AMGraph &G)
{
    int cnt = 0;
    cin >> G.vexnum >> G.arcnum;
    int MST_Krus = 0;
    Init(G.vexnum);
    sort(E + 1,E + G.arcnum,MyCompare);
    for(int i = 1; i <= G.arcnum; ++i)
    {
        if(find(E[i].u) != find(E[i].v))
        {
            join(E[i].u,E[i].v);
            MST_Krus += E[i].w;
            cnt++;
        }
        if(cnt == G.vexnum - 1)
        break;
    }
    cout << MST_Krus;
}
int main()
{
    AMGraph G;
    Krus(G);
}
