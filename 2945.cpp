#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3E5 + 5;
int n,cur;
int Fa[MAXN],Siz[MAXN],U[MAXN],V[MAXN];
int Jump[MAXN][25],Dep[MAXN],Head[MAXN];
struct wyy
{
	int to,next;
}Edge[2 * MAXN];
int read()
{
	char ch = getchar();
	int w = 0;
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
	Head[from] = cur;
	
	Edge[++ cur].to = from;
	Edge[cur].next = Head[to];
	Head[to] = cur;
}
int findA(int x)
{
	if(x == Fa[x])	return x;
	return Fa[x] = findA(Fa[x]);
}
void DFS(int x,int fa)
{
	Jump[x][0] = fa , Dep[x] = Dep[fa] + 1;
	for(int i = 1 ; i <= 20 ; i ++)
	{
		int mid = Jump[x][i - 1];
		Jump[x][i] = Jump[mid][i - 1];
	}
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(y != fa)	DFS(y,x);
	}
}
int getLca(int x,int y)
{
	if(Dep[x] < Dep[y])	swap(x,y);//强制Dep[x] >= Dep[y] 
	for(int i = 20 ; i >= 0 ; i --)
	{
		if(Dep[x] - (1 << i) >= Dep[y])	
			x = Jump[x][i];
	}
	if(x != y)
	{
		for(int i = 20 ; i >= 0 ; i --)
		{
			if(Jump[x][i] != Jump[y][i])
				x = Jump[x][i],//逗号！括号！ 
				y = Jump[y][i];
		}
		return Jump[x][0];
	}
	else	return x;
}
int getDis(int x,int y)
{
	int lca = getLca(x,y);
	return Dep[x] + Dep[y] - 2 * Dep[lca];
}
int main()
{
	freopen("2945.in","r",stdin);
	freopen("2945.out","w",stdout);
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++)	Fa[i] = i , Siz[i] = 1 , U[i] = V[i] = i;//直径两端。 
	
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i < n ; i ++)
	{
		int x = read() , y = read();
		int rootx = findA(x) , rooty = findA(y);
		
		int ans = 0 , ans1 = 1 , nu = x , nv = y;
		int dis1 = getDis(x,U[rootx]) , dis2 = getDis(x,V[rootx]);
		if(dis1 > dis2)	nu = U[rootx] , ans1 += dis1;
		else	nu = V[rootx] , ans1 += dis2;
		int dis3 = getDis(y,U[rooty]) , dis4 = getDis(y,V[rooty]);
		if(dis3 > dis4)	nv = U[rooty] , ans1 += dis3;
		else	nv = V[rooty] , ans1 += dis4;
		//printf("%d %d %d %d\n",dis1,dis2,dis3,dis4);		
		int dis5 = getDis(U[rootx],V[rootx]) , dis6 = getDis(U[rooty],V[rooty]);
		ans = max(ans,ans1);
		ans = max(ans,dis5);
		ans = max(ans,dis6);
		printf("%d\n",ans);
		
		if(Siz[rootx] < Siz[rooty])
		{
			Fa[rootx] = rooty;
			Siz[rooty] += Siz[rootx];
			//U[rooty] = nu , V[rooty] = nv;
			if(dis5 >= dis6 && dis5 >= ans1)	U[rooty] = U[rootx] , V[rooty] = V[rootx];
			else	if(dis6 >= dis5 && dis6 >= ans1)	U[rooty] = U[rooty] , V[rooty] = V[rooty];
			else	U[rooty] = nu , V[rooty] = nv;
			Add(x,y);DFS(x,y);
		}
		else
		{
			Fa[rooty] = rootx;
			Siz[rootx] += Siz[rooty];
			//U[rootx] = nu , V[rootx] = nv;
			if(dis5 >= dis6 && dis5 >= ans1)	U[rootx] = U[rootx] , V[rootx] = V[rootx];
			else	if(dis6 >= dis5 && dis6 >= ans1)	U[rootx] = U[rooty] , V[rootx] = V[rooty];
			else	U[rootx] = nu , V[rootx] = nv;
			Add(x,y);DFS(y,x);
		}
	}
	return 0;
}
