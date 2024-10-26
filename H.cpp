//
// Created by XXS on 2024/10/23.
//

#include<iostream>
#include <vector>
using namespace std;

#define INF 65535          //定义无穷大
#define MaxVerNum  100     //定义最大顶点个数
typedef int eInfoType;     //边链表中关于边的信息的数据类型，比如，带权图中可以表示边的权值
typedef int cellType;      //定义邻接矩阵中元素的数据类型。

typedef struct eNode       //边链表结点结构
{
	int adjVer;            //邻接顶点地址，此处为顶点在顶点表中序号，从1开始
	eInfoType eInfo;       //边链表中表示边的相关信息，比如表的权值
	eNode* next;    //指向边链表中的下一个结点
}EdgeNode;                 //边链表结点类型

typedef struct vNode       //顶点表中元素结构
{
	int data;      //存放图中顶点的数据
	EdgeNode* firstEdge;   //指向此顶点关联的第一条边的指针，即边链表的头指针
}VerNode;

typedef struct GraphAdjLinkList
{
	VerNode VerList[MaxVerNum+1];  //存放顶点的顺序表，数组0单元不用
	int VerNum;                    //顶点数
	int ArcNum;                    //弧（边）数
}Graph;                            //图的类型名


bool visited[MaxVerNum+1];  //全局数组，标记顶点是否已经被访问。0--未访问；1--已访问。数组0单元不用

void visit(Graph &G, int verID)
{         //顶点编号从1开始，数组0单元不用
	cout<<G.VerList[verID].data<<" ";
	visited[verID]=true;
}

//搜索顶点v的第一个邻接顶点
int firstAdj(Graph &G, int v)
{
	EdgeNode *p;
	p=G.VerList[v].firstEdge;
	if(p)
		return p->adjVer;
	else
		return 0;
}
//搜索顶点v位于邻接点w之后的下一个邻接点
int nextAdj(Graph &G, int v, int w)
{
	EdgeNode *p;
	p=G.VerList[v].firstEdge;         //取顶点v的边链表头指针
	while(p->next)
	{
		if(p->adjVer==w)
			return p->next->adjVer;  //返回w之后下一个邻接点编号
		p=p->next;
	}
	return 0;                        //未找到下一个邻接点，返回0
}

void addArc(Graph &G,int v,int w,int len) //v,m代表两个顶点,len代表输送量
{
	if(G.VerNum<w)
	{
		G.VerList[w].data=w;
		G.VerList[w].firstEdge=nullptr;
		G.VerNum++;
	}
	EdgeNode* edgeNode=new EdgeNode;
	edgeNode->next=nullptr;
	edgeNode->eInfo=len;
	edgeNode->adjVer=w;
	EdgeNode *p=G.VerList[v].firstEdge;
	if(p==nullptr) {
		G.VerList[v].firstEdge=edgeNode;
		G.ArcNum++;
		return;
	}
	while(p->next!=nullptr)
	{
		p=p->next;
	}
	p->next=edgeNode;
	G.ArcNum++;
}

int getLen(Graph &G,int v,int w)   //获取两个顶点之间的输送量
{
	EdgeNode *p;
	p=G.VerList[v].firstEdge;
	while(p->adjVer!=w)
	{
		p=p->next;
	}
	return p->eInfo;
}
int TEMP_NUM=9999999;//全局变量表示当前路径的输送量
int MAX_NUM=0;//全局变量表示输送最大值
void getMax(Graph &G,int v,int N)
{
	if(v==N)
	{
		if(TEMP_NUM>MAX_NUM)
		{
			MAX_NUM=TEMP_NUM;
		}
		return;
	}
	for(int i=firstAdj(G,v);i!=0;i=nextAdj(G,v,i))
	{
		if(visited[i]==1&&i!=N)continue;
		visited[i]=1;
		int tempLen=getLen(G,v,i);
		int currentLen=TEMP_NUM;
		TEMP_NUM=min(TEMP_NUM,tempLen);
		getMax(G,i,N);
		TEMP_NUM=currentLen;
	}
}

int main()
{
	Graph G;
	G.ArcNum=0;
	G.VerNum=1;
	VerNode verNode=VerNode();
	verNode.data=1;
	verNode.firstEdge=nullptr;
	G.VerList[1]=verNode;//初始化第一个站点
	int N,M;
	cin>>N>>M;
	for(int i=1;i<=M;i++)
	{
		int x,y,len;
		cin>>x>>y>>len;
		cout<<x<<" "<<y<<" "<<len<<endl;
		if(y>N) {
			cout<<"input error"<<endl;
			return 0;
		}
		addArc(G,x,y,len);
	}
	getMax(G,1,N);
	cout<<MAX_NUM<<endl;
}