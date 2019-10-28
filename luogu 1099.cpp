#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5E5 + 5 , inf = 0x7fffffff;//数组开小辣  
int n,s,tail,d1,d2,cur = -1;
int Head[MAXN],Temp[MAXN],Reach[MAXN];
int Fa[MAXN],Falen[MAXN],Q[MAXN],Vis[MAXN],D[MAXN]; 
struct wyy
{
	int to,next,val;
}Edge[MAXN * 2];
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
void Add(int from,int to,int val)
{
	Edge[++ cur].to = to;
	Edge[cur].next = Head[from];
	Edge[cur].val = val;
	Head[from] = cur;
	
	Edge[++ cur].to = from;
	Edge[cur].next = Head[to];
	Edge[cur].val = val;
	Head[to] = cur;
}
void Read()
{
	n = read() , s = read();
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i < n ; i ++)
	{
		int x = read() , y = read() , v = read();
		Add(x,y,v);
	}
}
void DFS(int x,int fa)
{
	Reach[x] = x , Temp[x] = 0;
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to , val = Edge[h].val;
		if(y == fa)	continue;
		Fa[y] = x , Falen[y] = val;
		DFS(y,x);
		if(Temp[y] + val > Temp[x])	
		{
			Temp[x] = Temp[y] + val;
			Reach[x] = Reach[y];
		}
	}
}
void getD()
{
	DFS(1,0);
	d1 = Reach[1];
	DFS(d1,0);
	d2 = Reach[d1];
	int x = d2;
	while(1)
	{
		Q[++ tail] = x;
		if(x == d1)	break;
		x = Fa[x];
	}
	//Falen：从d1到d2的顺序，各个点的falen 
	for(int i = 1 ; i * 2 <= tail ; i ++)	swap(Q[i],Q[tail - i + 1]);//使得点的排列从d1到d2。 
}
void getECC(int x,int fa,int src,int dis)//无论如何要记fa以dfs!!! 
{
	D[src] = max(D[src],dis);
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to , val = Edge[h].val;
		if(Vis[y] || y == fa)	continue;
		getECC(y,x,src,dis + val);
	}
}
void Calc()
{
	int maxd = 0;
	for(int i = 1 ; i <= tail ; i ++)	Vis[Q[i]] = 1;
	for(int i = 1 ; i <= tail ; i ++)	getECC(Q[i],0,Q[i],0);
	for(int i = 1 ; i <= tail ; i ++)	maxd = max(maxd,D[Q[i]]);
	
	int lef = 0 , rig = 0 , j = 0 , dis = 0 , ans = inf;
	Falen[Q[1]] = 0;
	for(int i = 1 ; i <= tail ; i ++)	rig += Falen[Q[i]];
	for(int i = 1 ; i <= tail ; i ++)
	{
		while(j < tail && dis + Falen[Q[j + 1]] <= s)	dis += Falen[Q[++ j]] , rig -= Falen[Q[j]];
		ans = min(ans,max(maxd,max(lef,rig)));
		lef += Falen[Q[i]] , dis -= Falen[Q[i]];
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("luogu 1099.in","r",stdin);
	freopen("luogu 1099.out","w",stdout);
	Read();
	getD();
	Calc();
	return 0;
}
