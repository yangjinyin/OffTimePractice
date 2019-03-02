#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>

using namespace std;

int  v[100][100];
bool hasPaht(int g[][5],int s,int t,int *path)
{
	bool visited[6]={false};
	queue<int> q;
	q.push(s);
	visited[s] = true;

	//BFS
	while(q.size())
	{
		int top =q.front();
		q.pop();
		for(int i = 0;i<5;i++)
		{
			if(!visited[i]&&g[top][i]>0)
			{
				q.push(i);
				visited[i] = true;
				path[i] = top;
			}
		}
		
	}
	return visited[t]== true;
}
int maxFlow(int g[][5],int s,int t)
{
	for(int i = 0;i<5;i++)
		for(int j = 0;j<5;j++)
			v[i][j] = g[i][j];

	int maxflow = 0;

	int path[5];
	while(hasPaht(g,s,t,path))
	{
		int min_flow = INT_MAX;

		//更新路径上的每条边，找出最小的流量
		for(int i = t;i!=s;i = path[i])
		{
			int u = path[i];
			min_flow = min(min_flow,g[u][i]);
		}
		//更新路径中的每条边
		for(int i = t;i!=s;i = path[i])
		{
			int u = path[i];
			g[u][i] -=min_flow;
			g[i][u] += min_flow;
		}
		maxflow+=min_flow;
	}
	return maxflow;
}
void Edmonds_Karp()
{
	int graph[5][5] = {{0,2,0,0,0},
						{1,0,3,4,0},
						{0,2,0,0,5},
						{0,2,0,0,0},
						{0,0,3,0,0}};
	int flow = maxFlow(graph,0,4);
	cout<<flow;
	
}


//匈牙利算法；
const int N=1000;
int leftV,rightV; //边的左点数与右点数；
int k;				//边数；
int maps[N][N],vis[N],link[N]; //link记录右点y所匹配左点的编号

int Hungarianfind(int x)
{
	int i;
	for(i = 1;i <= rightV;i++)
	{
		if(maps[x][i] && !vis[i])      //x和i相连且节点i未被搜索
		{
			vis[i] = 1;					//标记点被搜索过；
			if(link[i] == 0 || Hungarianfind(link[i])) //如果i不属于前一个匹配或匹配到的点可以找到增广路，就更新；
			{
				link[i] = x;
				return 1;
			}
		}
	}
	return 0;
}

void Hungarian()
{
	int i,x,y,sum = 0;
	scanf("%d%d%d",&leftV,&rightV,&k);
	for(i = 0;i<k;i++)
	{
		scanf("%d%d",&x,&y);
		maps[x][y] = 1;
	}
	for(i = 1;i<=leftV;i++)
	{
		memset(vis,0,sizeof(vis));
		if(Hungarianfind(i))
			sum++;
	}
	printf("%d\n",sum);
}

int Hmain()
{
	int i,x,y,sum = 0;
	scanf("%d%d",&leftV,&k);
	rightV = leftV;
	for(i = 0;i<k;i++)
	{
		scanf("%d%d",&x,&y);
		maps[x][y] = 1;
	}
	for(i = 1;i<=leftV;i++)
	{
		memset(vis,0,sizeof(vis));
		if(find(i))
			sum++;
	}
	printf("%d\n",(leftV-sum));
	return 0;
}