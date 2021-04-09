//二叉树遍历
#include<iostream>
#include<queue>
using namespace std;
typedef struct node {
	char date;
	struct node*lchild;
	struct node*rchild;
} BiTreeNode, *BiTree;
void CreatBiTree(BiTree &T) {
	char ch;
	cin >> ch;
	if (ch == '#') {
		T = NULL;
	} else {
		T = new BiTreeNode;
		T->date = ch;
		CreatBiTree(T->lchild);
		CreatBiTree(T->rchild);
	}
}
void preTraversal(BiTree T) {
	if (T == NULL) {
		return ;
	} else {
		cout << T->date <<" ";
		preTraversal(T->lchild);
		preTraversal(T->rchild);
	}
}
void midTraversal(BiTree T) {
	if (T == NULL) {
		return ;
	} else {
		preTraversal(T->lchild);
		cout << T->date <<" ";
		preTraversal(T->rchild);
	}
}
void postTraversal(BiTree T) {
	if (T == NULL) {
		return ;
	} else {
		preTraversal(T->lchild);
		preTraversal(T->rchild);
		cout << T->date <<" ";
	}
}
void levelTreval(BiTree T) {
	if (T == NULL) {
		return;
	}
	queue<BiTree> qu;
	qu.push(T);
	while (!qu.empty()) {
		T = qu.front();
		qu.pop();
		cout << T->date << " ";
		if (T->lchild != NULL) {
			qu.push(T->lchild);
		}
		if (T->rchild != NULL) {
			qu.push(T->rchild);
		}
	}
}
int main() {
	BiTree t;
	CreatBiTree(t);
	cout << "preTraversal" << endl;
	preTraversal(t);
	cout << endl;
	cout << "midTraversal" << endl;
	midTraversal(t);
	cout << endl;
	cout << "postTraversal" << endl;
	postTraversal(t);
	cout << endl;
	cout << "levelTraversal" << endl;
	levelTreval(t);
	cout << endl;
	return 0;
}
//Kruskal
#include<iostream>
#include<algorithm>
using namespace std;
typedef char VertexType;
typedef int EdgeType;
#define MAXVEX 100
#define INFINITY 65535
typedef struct {
	VertexType vex[MAXVEX];
	EdgeType arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
} MGraph;
struct Edge{
	int s;
	int t;
	int next;
	int wight;
};
bool cmp(Edge a,Edge b){
	if(a.wight!=b.wight)
	return a.wight<b.wight;
}
int Find(int *parent,int f){
	while(parent[f]>0)
	f=parent[f];
	return f;
}
//生成邻接矩阵
void CreateMGraph(MGraph *G) {
	int i, j, w;
	cin >> G->numVertexes >> G->numEdges;
	for (i = 0; i < G->numVertexes; i++) {
		cin >> G->vex[i];
	}
	for (i = 0; i < G->numVertexes; i++) {
		for (j = 0; j < G->numVertexes; j++) {
			G->arc[i][j] = INFINITY;
		}
	}
	for (i = 0; i < G->numVertexes; i++) {
		cin >> i >> j >> w;
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];
	}
}
void MiniSpanTree_Kruskal(MGraph G){
	int i,j,n,m=0;
	Edge edges[MAXVEX];
	int parent[MAXVEX];
	for(i=0;i<G.numVertexes;i++){
		for(j=0;j<G.numVertexes;j++){
			edges[m].s=i;
			edges[m].t=j;
			edges[m].wight=G.arc[i][j];
			m++;
		}
	}
	sort(edges,edges+G.numVertexes,cmp);
	for(i=0;i<G.numEdges;i++){
		parent[i]=0;
	}
	for(i=0;i<G.numEdges;i++){
		n=Find(parent,edges[i].s);
		m=Find(parent,edges[i].t);
		if(n!=m){
			parent[n]=m;
			cout<<edges[i].s<<" "<<edges[i].t<<" "<<edges[i].wight<<endl;
		}
	}
}
int main(){
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_Kruskal(G);
	return 0;
}
//prim
#include<iostream>
using namespace std;
typedef char VertexType;
typedef int EdgeType;
#define MAXVEX 100
#define INFINITY 65535
typedef struct {
	VertexType vex[MAXVEX];
	EdgeType arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;
} MGraph;
void CreateMGraph(MGraph *G) {
	int i, j, w;
	cin >> G->numVertexes >> G->numEdges;
	for (i = 0; i < G->numVertexes; i++) {
		cin >> G->vex[i];
	}
	for (i = 0; i < G->numVertexes; i++) {
		for (j = 0; j < G->numVertexes; j++) {
			G->arc[i][j] = INFINITY;
		}
	}
	for (i = 0; i < G->numVertexes; i++) {
		cin >> i >> j >> w;
		G->arc[i][j] = w;
		G->arc[j][i] = G->arc[i][j];
	}
}
void Prim(MGraph G){
	int min,i,j,k;
	int adjvex[MAXVEX],lowcost[MAXVEX];
	adjvex[0]=0;
	lowcost[0]=0;
	for(i=1;i<G.numVertexes;i++){
		lowcost[i]=G.arc[0][i];
		adjvex[i]=0;
	}
	for(i=1;i<G.numVertexes;i++){
		min=MAXVEX;
		j=1;
		k=0;

		for(;j<G.numVertexes;j++){
			if(lowcost[j]<min&&lowcost[j]!=0){
				min=lowcost[j];
				k=j;
			}
		}
		cout<<adjvex[k]<<" "<<k;
		lowcost[k]=0;
		for(i=0;i<G.numVertexes;i++){
			if(lowcost[i]!=0&&lowcost[i]>G.arc[k][i]){
				lowcost[i]=G.arc[k][i];
				adjvex[i]=k;
			}
		}
	}
}
int main() {
	MGraph G;
	CreateMGraph(&G);
	Prim(G);
	return 0;
}
