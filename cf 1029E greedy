#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN = 2E5 + 5 , inf = 0x7fffffff;
int n,node,cur = -1;
int Head[MAXN],Fa[MAXN],Dep[MAXN],Vis[MAXN],Legal[MAXN];
struct wyy
{
	int to,next;
}Edge[2*MAXN];
struct heap
{
	int id,dep;
	bool operator < (const heap &x)const
	{
		return dep < x.dep;
	}
};
priority_queue<heap>Heap;
void Add(int from,int to)
{
	Edge[++cur].to = to;
	Edge[cur].next = Head[from];
	Head[from] = cur;
	
	Edge[++cur].to = from;
	Edge[cur].next = Head[to];
	Head[to] = cur;
}
int read()
{
	char ch = getchar();
	int w = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >= '0' && ch <= '9')	
	{
		w = w * 10 + (int)(ch - '0');
		ch = getchar();
	}
	return w;
}
void Read()
{
	n = read();
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i < n ; i ++)
	{
		int x,y;
		x = read() , y = read();
		Add(x,y);
	}
}
void DFS(int x,int fa)
{
	Heap.push((heap){x,Dep[x]});
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(y == fa)	continue;
		Fa[y] = x , Dep[y] = Dep[x] + 1;
		DFS(y,x);
	}
}
void Calc()
{
	int ans = 0;
	memset(Vis,0,sizeof(Vis));//是否被选择过。 
	memset(Legal,0,sizeof(Legal));//是否已经合法。 
	while(Heap.top().dep > 2)
	{
		int x = Heap.top().id;
		Heap.pop();
		if(Legal[x])	continue;//已合法，则不用操作。 
		
		x = Fa[x];//不合法，选择父亲 
		if(Vis[x])	continue;//父亲已被选择过，不用重复 
		ans ++ , Vis[x] = Legal[x] = 1;//父亲已合法且被选择 
		
		for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
		{
			int y = Edge[h].to;
			Legal[y] = 1;//使相邻点合法。 
		}
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("zcy.in","r",stdin);
	freopen("zcy.out","w",stdout);
	Read();
	DFS(1,0);
	Calc();
	return 0;
}
