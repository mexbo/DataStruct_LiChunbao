typedef int InfoType;
#define	MAXV 100				//最大顶点个数
#define INF 32767				//INF表示∞
//以下定义邻接矩阵类型
typedef struct 
{  	int no;						//顶点编号
	InfoType info;				//顶点其他信息
} VertexType;					//顶点类型
typedef struct  				//图的定义
{  	int edges[MAXV][MAXV]; 		//邻接矩阵
   	int n,e;   					//顶点数，边数
	VertexType vexs[MAXV];		//存放顶点信息
} MGraph;						//图的邻接矩阵类型
//以下定义邻接表类型
typedef struct ANode           	//边的节点结构类型
{	int adjvex;              	//该边的终点位置
   	struct ANode *nextarc; 		//指向下一条边的指针
   	InfoType info;           	//该边的相关信息,这里用于存放权值
} ArcNode;
typedef int Vertex;
typedef struct Vnode      		//邻接表头节点的类型
{	Vertex data;            	//顶点信息
    ArcNode *firstarc;     		//指向第一条边
} VNode;
typedef VNode AdjList[MAXV];	//AdjList是邻接表类型
typedef struct 
{	AdjList adjlist;         	//邻接表
    int n,e;                 	//图中顶点数n和边数e
} ALGraph;                   	//图的邻接表类型
