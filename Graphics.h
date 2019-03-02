#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <list>
#include <queue>
#include <vector>

using namespace std;
const int maxnum = 100;  
const int maxint = 99999;  

class Edge
{
public:
	int start,end;          //start,end
	int value;              //边的权重

	Edge(){};
	Edge(int s,int e ,int v ){start = s;end = e;value = v;}
	Edge& operator= (Edge& tmp){this->start = tmp.start;this->end = tmp.end;this->value = tmp.value;}
};

class G
{
	Edge m_edge[maxnum];
	int m_nodenum;
	int m_edgenum;
public:
	G(){};
	G(int nodenum ,int edgenum,Edge edge[])
	{
		m_edgenum = edgenum;
		m_nodenum = nodenum;

		for(int i = 0 ;i < m_edgenum;i++)
		{
			m_edge[i] = edge[i];
		}
	}

	//source开始BFS的起始点;
	list<int> BFS(int source)
	{
		//无向图邻接图
		int **GMatrix = new int*[m_nodenum];
		for(int i = 0; i < m_nodenum; ++i)
		{
			GMatrix[i] = new int[m_nodenum];
		}
		for(int i = 0; i < m_nodenum; ++i)
		{
			for(int j = 0; j < m_nodenum; j++)
				GMatrix[i][j] = 0;
		}

		for(int i = 0;i < m_edgenum;i++)
		{
			int s = m_edge[i].start;
			int t = m_edge[i].end;

			GMatrix[s][t] = m_edge[i].value;
			GMatrix[t][s] = m_edge[i].value;
		}
		int *color = new int[m_nodenum];
		for(int i = 0; i < m_nodenum; ++i)
		{
			color[i] = 0;                 //0: unfind
		}
		
		stack<int> s;
		list<int> l;
		color[source] = 1;               //1:push in stack;
		s.push(source);

		while(!s.empty())
		{
			int tmp = s.top();
			s.pop();
			color[tmp] = 2;
			l.push_back(tmp);

			int j = 0;
			while(j<m_nodenum && GMatrix[tmp][j] != 0 && color[j]==0)
			{
				color[j] = 1;
				s.push(j);
				j++;
			}
		}

		delete[] GMatrix;
		delete[] color;
		
		return l;
		
	}

	list<int> DFS(int source)
	{
		//无向图邻接图
		int **GMatrix = new int*[m_nodenum];
		for(int i = 0; i < m_nodenum; ++i)
		{
			GMatrix[i] = new int[m_nodenum];
		}
		for(int i = 0; i < m_nodenum; ++i)
		{
			for(int j = 0; j < m_nodenum; j++)
				GMatrix[i][j] = 0;
		}

		for(int i = 0;i < m_edgenum;i++)
		{
			int s = m_edge[i].start;
			int t = m_edge[i].end;

			GMatrix[s][t] = m_edge[i].value;
			GMatrix[t][s] = m_edge[i].value;
		}
		int *color = new int[m_nodenum];
		for(int i = 0; i < m_nodenum; ++i)
		{
			color[i] = 0;                 //0: unfind
		}

		list<int> l;
		color[source] = 1;               //1:push in stack;
		l.push_back(source);
		int nextV = source;
	

		delete[] GMatrix;
		delete[] color;

		return l;
	}

	//单源点的最短路径
	void Bellman_Ford()
	{

	}
	
};

void Dijkstra(  
	const int numOfVertex,    /*节点数目*/  
	const int startVertex,    /*源节点*/  
	int a[][5],          /*有向图邻接矩阵*/  
	int *distance,            /*各个节点到达源节点的距离*/  
	int *prevVertex           /*各个节点的前一个节点*/  
	)
{
	int isSet[5]={0,0,0,0,0};
	isSet[startVertex] = 1;

	//初始化distance；
	for(int i = 0;i<numOfVertex;i++)
	{
		if(a[startVertex][i]!=0)
			distance[i] = a[startVertex][i];
	}
	int nextVertex = startVertex;
	int u = startVertex;
	for(int i = 1;i<numOfVertex;i++)
	{
		int mindistance = INT_MAX;
		for(int j = 0;j<numOfVertex;j++)
		{
			if((isSet[j] == 0) && (distance[j] < mindistance)) //寻找不在集合中最小距离的点
			{
				mindistance = distance[j];
				nextVertex = j;              //加入下一个节点j;				
			}
		}
		isSet[nextVertex] = 1;
		u = nextVertex;
		//更新distance
		for(int j = 0;j<numOfVertex;j++)
		{
			if(isSet[j] == 0&&a[nextVertex][j]!=0&&a[nextVertex][j]<INT_MAX)
			{
				int temp = distance[nextVertex]+a[nextVertex][j];
				if(temp<distance[j])
				{
					distance[j] = temp;
					prevVertex[j] = nextVertex;       //保存元素的前一个；
				}
			}
		}
	}
}

void Floyd(int a[][5],int distance[][5],int path[][5])
{
	for(int k = 0;k<5;k++)
	{
		for(int i = 0;i<5;i++)
		{
			for(int j = 0;j<5;j++)
			{
				if(distance[i][j]>distance[i][k]+distance[k][j])
				{
					distance[i][j]=distance[i][k]+distance[k][j];
					path[i][j] = path[i][k];
				}
			}
		}
	}
}
int degree[100];
bool topmap[100][100];
int a[100];
int n,m;
void topu()
{
	queue<int> q;
	int count = 0;
	while(!q.empty())
		q.pop();
	for(int i = 1;i<n;i++)
		if(degree[i] == 0)
			q.push(i);

	int u;
	while(!q.empty())
	{
		u = q.front();
		a[count++] = u;
		q.pop();
		for(int i = 1;i<=n;i++)
		{
			if(topmap[u][i])
			{
				degree[i]--;
				if(degree[i] == 0)
					q.push(i);
			}
		}

		if(count==n)
		{
			for(int i = 0;i<n;i++)
				printf("%d",a[i]);
		}
	}

}
void TopSort()
{
	int u,v;
	while(~scanf("%d%d",&n,&m))
	{
		memset(degree,0,sizeof(degree));
		memset(topmap,0,sizeof(topmap));

		for(int i = 0;i<m;i++)
		{
			scanf("%d%d",&u,&v);
			if(!topmap[u][v])
			{
				degree[v]++;
				topmap[u][v] = 1;
			}
		}
		topu();
	}
}

int Primdistance[100]={INT_MAX};
int Primvis[100]={0};
int preVerdix[100]={0};
static int Map[100][100];
void PrimCount()
{
	int ans = 0;
	int k;
	for(int i = 1;i<=n;i++)
		Primdistance[i] = INT_MAX;
	Primdistance[1] = 0;

	for(int i = 1;i<=n;i++)
	{
		int temp = INT_MAX;

		for(int j = 1;j<=n;j++)
		{
			if(!Primvis[j]&&temp>Primdistance[j])
			{
				temp = Primdistance[j];
				k = j;
			}
		}
		Primvis[k] = 1;
		ans +=Primdistance[k];
		for(int j = 1;j<=n;j++)
		{
			if(!Primvis[j] && Primdistance[j]>Map[k][j])
			{
				Primdistance[j] = Map[k][j];
				preVerdix[j] = k;
			}
		}
	}
	printf("%d",ans);
}

void Prim()
{
	memset(Map,0x7F,sizeof(Map));//设置INT的最大值
	int m;
	scanf("%d%d",&n,&m);
	int u,v,value;
	for(int i = 0;i < m;i++)
	{
		scanf("%d%d%d",&u,&v,&value);
		Map[u][v] = Map[v][u] = value;
	}
	PrimCount();
}
