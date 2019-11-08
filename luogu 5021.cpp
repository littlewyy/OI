#include<bits/stdc++.h>
using namespace std;
const int MAXN = 5E4 + 5 , inf = 0x7fffffff;
int n,m,ans,cur = -1;
int Head[MAXN],Q[MAXN],Vis[MAXN],Len[MAXN];
struct wyy
{
	int to,next,val;
}Edge[MAXN * 2];
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
void Read()
{
	n = read() , m = read();
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i < n ; i ++)
	{
		int x = read() , y = read() , val = read();
		Add(x,y,val);
	}
}
int getMax(int tail,int lim)
{
	int j = 0 , nans = 0;
	for(int i = tail ; i >= 1 ; i --)
	{
		if(Vis[i])	continue;
		if(Q[i] >= lim)	
		{
			Vis[i] = 1;
			nans ++;
		}
		else
		{
			while(j < tail && (Q[i] + Q[j] < lim || Vis[j]))	j ++;
			if(!Vis[j] && i != j && Q[i] + Q[j] >= lim)//细节：不能自己跟自己配 
			{
				nans ++;
				Vis[i] = Vis[j] = 1;
			}
		}
	}	
	return nans;
}
void DFS(int x,int fa,int lim)
{
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(y == fa)	continue;
		DFS(y,x,lim);
	}
	int tail = 0;
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to , val = Edge[h].val;
		if(y == fa)	continue;
		Q[++ tail] = Len[y] + val;
	}
	sort(Q + 1 , Q + 1 + tail);
//	printf("%d : ",x);
//	for(int i = 1 ; i <= tail ; i ++)	printf("%d ",Q[i]);
//	printf("\n");
	for(int i = 1 ; i <= tail ; i ++)	Vis[i] = 0;
	int nans = getMax(tail,lim);
	
	ans += nans;//计数 
	
	int lo = 0 , hi = tail + 1;
	while(lo + 1 < hi)
	{
		int mid = (lo + hi) >> 1;
		for(int i = 1 ; i <= tail ; i ++)	Vis[i] = 0;Vis[mid] = 1;
		if(getMax(tail,lim) == nans)	lo = mid;
		else	hi = mid;
	}
	
	Len[x] = Q[lo];
}
void Calc()
{
	int lo = 0 , hi = inf;
	while(lo + 1 < hi)
	{
		int mid = (lo + hi) >> 1;
		ans = 0 , DFS(1,0,mid);
		if(ans >= m)	lo = mid;
		else	hi = mid;
	}
	printf("%d\n",lo);
}
int main()
{
	freopen("luogu 5021.in","r",stdin);
	freopen("luogu 5021.out","w",stdout);
	Read();
	Calc();
	return 0;
}
