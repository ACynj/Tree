//Prim算法
#include<stdio.h>
#include<stdlib.h>
typedef struct enode* Edge;
typedef struct graph* MGraph;
typedef struct node* Node;
typedef struct lgraph* LGraph;
struct enode {
	int v1, v2;
	int weight;
};
struct graph {
	int nv, ne;
	int G[1000][1000];
};
struct node {
	int adjl;
	Node Next;
	int weight;
};
typedef struct sndoe {
	Node Fristnode;
}adjlist[1000];
struct lgraph {
	int nv, ne;
	adjlist G;
};
LGraph creatlGraph(int nv) {
	LGraph MST = (LGraph)malloc(sizeof(struct lgraph));
	MST->nv = nv;
	MST->ne = 0;
	for (int i = 0; i < MST->nv; i++) {
		MST->G[i].Fristnode = NULL;
	}
	return MST;

}
MGraph creatGraph(int n)
{
	MGraph Graph= (MGraph)malloc(sizeof(struct graph));
	Graph->nv = n;
	for (int i = 0; i < Graph->nv; i++) {
		for (int j = 0; j < Graph->nv; j++) {
			Graph->G[i][j] = 10000;
		}
	}
	return Graph;
}
MGraph buildGraph() {
	int nv,ne;
	MGraph Graph;
	scanf_s("%d %d", &nv, &ne);
	Graph = creatGraph(nv);
	Graph->ne = ne;
	if (Graph->ne != 0) {
		for (int i = 0; i < Graph->ne; i++) {
			Edge E = (Edge)malloc(sizeof(struct enode));
			scanf_s("%d %d %d", &E->v1, &E->v2, &E->weight);
			Graph->G[E->v1][E->v2] = E->weight;
			Graph->G[E->v2][E->v1] = E->weight;
		}
	}
   
	return Graph;
}
void insert(LGraph MST,Edge E) {
	Node newnode = (Node)malloc(sizeof(struct node));
	newnode->weight = E->weight;
	newnode->adjl = E->v2;
	newnode->Next = MST->G[E->v1].Fristnode;
	MST->G[E->v1].Fristnode = newnode;
}
int findMinDist(MGraph Graph, int dist[]) {
	/*返回未被收录顶点中dist的最小值*/
	int minv, mindist=10000, v;
	for (v = 0; v < Graph->nv; v++) {
		if (dist[v] != 0 && dist[v] < mindist) {
			mindist = dist[v];
			minv = v;
		}


	}
	if (mindist < 10000) {
		return minv;
	}
	else return -1;
}
int Prim(MGraph Graph,LGraph MST) {
	int dist[1000], parent[1000], v, w,vcount, totalweight;
	Edge E;
	for (v = 0; v < Graph->nv; v++) {
		dist[v] = Graph->G[0][v];
		parent[v] = 0;
	}
	totalweight = 0;
	vcount = 0;
	MST = creatlGraph(Graph->nv);
	E = (Edge)malloc(sizeof(struct enode));
	dist[0] = 0;//收录V0
	vcount++;
	parent[0] = -1;//以V0为根节点
	
	while (1) {
		v = findMinDist(Graph, dist);
		if (v == -1)
			break;
		
		E->v1 = parent[v];
		E->v2 = v;
		E->weight = dist[v];
		insert(MST, E);
		totalweight += dist[v];
		dist[v] = 0;
		vcount++;
		for (w = 0; w < Graph->nv; w++) 
			if (dist[w] != 0 && Graph->G[v][w] < 10000) {                                       
				if (Graph->G[v][w] < dist[w]) {
					dist[w] = Graph->G[v][w];
					parent[w] = v;
				}
			}
	}
	Node x;
	for (int i = 0; i < MST->nv; i++) {
		x = MST->G[i].Fristnode;
		printf("%d: ", i);
		while (x) {
			printf("@%d ", x->adjl);
			x = x->Next;
		}
	}
	if (vcount < Graph->nv)totalweight = -1;
	return totalweight;
	
}
int main() {
	MGraph Graph = buildGraph();
	LGraph MST = (LGraph)malloc(sizeof(struct lgraph));
	Node w;
	int x = Prim(Graph, MST);
	/*for (int i = 0; i < Graph->nv; i++) {
		for (int j = 0; j < Graph->nv; j++) {
			printf("%d ", Graph->G[i][j]);
		}
		printf("\n");
	}
	*/
	
	printf("%d\n", x);

}