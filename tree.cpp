#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 1E5 + 5;
LL f[MAXN],Dep[MAXN],MaxD[MAXN],Ext[MAXN],Tmp[MAXN],Tag[MAXN];
int n,cur = -1;
int Head[MAXN],Son[MAXN],Siz[MAXN],Father[MAXN],Vis[MAXN];
struct wyy
{
	int to,w,next;
}Edge[2 * MAXN];
struct bdd
{
	int id;
	LL f;
}Node[MAXN];
void Add(int from,int to,int w)
{
	Edge[++ cur].to = to;
	Edge[cur].w = w;
	Edge[cur].next = Head[from];
	Head[from] = cur;
	
	Edge[++ cur].to = from;
	Edge[cur].w = w;
	Edge[cur].next = Head[to];
	Head[to] = cur;
}
LL read()
{
	char ch = getchar();LL w = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >= '0' && ch <= '9')
	{
		w = w * 10 + ch - '0';
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
		int x = read() , y = read() , w = read();
		Add(x,y,w);
	}
}
void DFS(int x,int fa)
{
	//Ext[x] = max{Dep[j] - 2 * Dep[lca(i,j)]}
	MaxD[x] = Dep[x];
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to , w = Edge[h].w;
		if(y == fa)	continue;
		Dep[y] = Dep[x] + w;
		DFS(y,x);
		MaxD[x] = max(MaxD[x],MaxD[y]);
	}
	Ext[x] = MaxD[x] - 2 * Dep[x];
	int temp = 0;
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(y == fa)	continue;
		Son[++ temp] = y;
	}
	LL lmax = 0 , rmax = 0;
	for(int i = 1 ; i <= temp ; i ++)
	{
		Tmp[i] = lmax;
		lmax = max(lmax,MaxD[Son[i]]);
	} 
	for(int i = temp ; i >= 1 ; i --)
	{
		Tmp[i] = max(Tmp[i],rmax);
		rmax = max(rmax,MaxD[Son[i]]);
	}
	for(int i = 1 ; i <= temp ; i ++)	
	{
		int y = Son[i];
		Tag[y] = max(Tag[y],Tmp[i] - 2 * Dep[x]);
	}	
}
void PushDown(int x,int fa)
{
	Ext[x] = max(Ext[x],Tag[x]);
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(y == fa)	continue;
		Tag[y] = max(Tag[y],Tag[x]);
		PushDown(y,x);
	}
}
bool cmp(bdd x,bdd y)
{
	return x.f > y.f;
}
void getF()
{
	for(int i = 1 ; i <= n ; i ++)
		f[i] = Dep[i] + Ext[i];
	//for(int i = 1 ; i <= n ; i ++)
	//	printf("%lld ",f[i]);
	//printf("\n");
	for(int i = 1 ; i <= n ; i ++)
	{
		Node[i].id = i;
		Node[i].f = f[i];
	}
	sort(Node + 1 , Node + 1 + n , cmp);
	
	//for(int i = 1 ; i <= n ; i ++)
		//printf("%d %lld\n",Node[i].id,Node[i].f);
}
int findA(int x)
{
	if(x == Father[x])	return x;
	return Father[x] = findA(Father[x]);
}
void Query()
{
	int q = read();
	while(q --)
	{
		LL l = read();
		
		for(int i = 1 ; i <= n ; i ++)	Siz[i] = 1 , Father[i] = i;
		memset(Vis,0,sizeof(Vis));
		
		int j = 0 , ans = 1;
		for(int i = 1 ; i <= n ; i ++)
		{
			int x = Node[i].id;LL f = Node[i].f;
			if(i > 1)//½«i - 1Çå³ý¡£ 
			{
				int lx = Node[i - 1].id;
				int lroot = findA(lx);
				Siz[lroot] --;Vis[lx] = 0;
			}
			while(j < n && Node[j + 1].f >= f - l)	
			{
				j ++;
				int nx = Node[j].id;Vis[nx] = 1;
				for(int h = Head[nx] ; h != -1 ; h = Edge[h].next)
				{
					int y = Edge[h].to;
					if(Vis[y] == 1)	
					{
						int rootx = findA(nx) , rooty = findA(y);
						Father[rootx] = rooty;
						Siz[rooty] += Siz[rootx];
						ans = max(ans,Siz[rooty]);
					}
				}
			}
			//printf("%d ",j);
		} 
		printf("%d\n",ans);
	}
}
int main()
{
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	Read();
	DFS(1,0);
	PushDown(1,0);
	getF();
	Query();
	return 0;
}
