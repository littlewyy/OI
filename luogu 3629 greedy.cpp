#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1E5 + 5;
int n,k,d1,d2,d,ans,cur = -1;
int Head[MAXN],D[MAXN],Dis[MAXN];
int Fa[MAXN],FaE[MAXN],Q[MAXN],f[MAXN],MaxD[MAXN];
struct wyy
{
	int to,next,val;
}Edge[2 * MAXN];
int read()
{
	char ch = getchar();int w = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >= '0' && ch <= '9')	
	{
		w = w * 10 + ch - '0';
		ch = getchar();
	}
	return w;
}
void Add(int from,int to)
{
	Edge[++ cur].to = to;
	Edge[cur].next = Head[from];
	Edge[cur].val = 1;
	Head[from] = cur;
	
	Edge[++ cur].to = from;
	Edge[cur].next = Head[to];
	Edge[cur].val = 1;
	Head[to] = cur;
}
void Read()
{
	n = read() , k = read();
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i < n ; i ++)
	{
		int x = read() , y = read();
		Add(x,y);
	}
}
int DFS(int x,int fa)
{
	int node = x;
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(y == fa)	continue;
		int ynode = DFS(y,x);
		if(D[y] + 1 > D[x])	
		{
			D[x] = D[y] + 1;
			node = ynode;
		}
	}
	return node;
}
void BFS(int st)
{
	int head,tail;
	head = tail = 1 , Q[head] = st;
	while(head <= tail)
	{
		int x = Q[head ++];
		for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
		{
			int y = Edge[h].to;
			if(y == Fa[x])	continue;
			Fa[y] = x , FaE[y] = h , Dis[y] = Dis[x] + 1;
			Q[++ tail] = y;
		}
	}
	int maxdis = 0;
	d2 = d1;
	for(int i = 1 ; i <= n ; i ++)	
		if(Dis[i] > maxdis)
			maxdis = Dis[i] , d2 = i;
	ans = 2 * (n - 1) - (maxdis - 1);
//	printf("%d\n",ans);
}
void Dp(int x,int fa)
{
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to , val = Edge[h].val;
		if(y == fa)	continue;
		Dp(y,x);
		f[x] = max(f[x],MaxD[x] + val + MaxD[y]);
		MaxD[x] = max(MaxD[x],val + MaxD[y]);
	}
	d = max(d,f[x]);
}
void Calc()
{
	d1 = DFS(1,0);//直径端点之1。
	BFS(d1);//记录每个点的fa和深度，找到1条直径
	//printf("%d %d\n",d1,d2);
	
	if(k > 1)
	{
		int x = d2;
		while(x != d1)
		{
			//printf("%d ",x);
			int e = FaE[x];
			Edge[e].val = -1 , Edge[e ^ 1].val = -1;
			x = Fa[x];
		}
		Dp(1,0);
		ans -= (d - 1);
	}
	//printf("\n");
	printf("%d\n",ans);
}
int main()
{
	freopen("luogu 3629.in","r",stdin);
	freopen("luogu 3629.out","w",stdout);
	Read();
	Calc();
	return 0;
}
