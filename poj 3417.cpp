//#include<bits/stdc++.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;
const int MAXN = 1E5 + 5;
int n,m,ans,cur = -1,qcur = -1;
int Head[MAXN],HeadTag[MAXN];
int Fa[MAXN],Sta[MAXN],Dep[MAXN];
int Sum[MAXN],Diff[MAXN];
struct wyy
{
	int to,next,lca;
}Edge[MAXN * 2],Tag[MAXN * 2];
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
	Head[from] = cur;
	
	Edge[++ cur].to = from;
	Edge[cur].next = Head[to];
	Head[to] = cur;
}
void AddQue(int from,int to)
{
	Tag[++ qcur].to = to;
	Tag[qcur].next = HeadTag[from];
	Tag[qcur].lca = 0;
	HeadTag[from] = qcur;
	
	Tag[++ qcur].to = from;
	Tag[qcur].next = HeadTag[to];
	Tag[qcur].lca = 0;
	HeadTag[to] = qcur;
}
void Read()
{
	n = read() , m = read();
	memset(Head,-1,sizeof(Head));
	memset(HeadTag,-1,sizeof(HeadTag));
	for(int i = 1 ; i < n ; i ++)
	{
		int x = read() , y = read();
		Add(x,y);
	}
	for(int i = 1 ; i <= m ; i ++)
	{
		int x = read() , y = read();
		AddQue(x,y);		
	}
	for(int i = 1 ; i <= n ; i ++)	Fa[i] = i;
}
int findA(int x)
{
	if(x == Fa[x])	return x;
	return Fa[x] = findA(Fa[x]);
}
void getLCA(int x,int fa)
{
	Sta[x] = 1;
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(y == fa)	continue;
		Dep[y] = Dep[x] + 1;
		getLCA(y,x);
		Fa[y] = x;
	}
	for(int h = HeadTag[x] ; h != -1 ; h = Tag[h].next)
	{
		int y = Tag[h].to;
		if(Sta[y] == 2)	
		{
			int rt = findA(y);
			Tag[h].lca = rt;
		}
	}
	Sta[x] = 2;
}
void getDiff(int x,int fa)
{
	for(int h = HeadTag[x] ; h != -1 ; h = Tag[h].next)
	{
		int y = Tag[h].to , lca = Tag[h].lca;
		if(lca)	
		{
			Diff[x] ++;
			Diff[y] ++;
			Diff[lca] -= 2;
		}
	} 
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(y == fa)	continue;
		getDiff(y,x);
	}
}
void getSum(int x,int fa)
{
	Sum[x] = Diff[x];
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(y == fa)	continue;
		getSum(y,x);
		Sum[x] += Sum[y];
	}
	if(x == 1)	return;
	if(Sum[x] == 0)	ans += m;
	else	if(Sum[x] == 1)	ans ++;
}
int main()
{
	freopen("poj 3417.in","r",stdin);
	freopen("poj 3417.out","w",stdout);
	//freopen("2989.in","r",stdin);
	//freopen("2989.out","w",stdout);
	Read();
	getLCA(1,0);
	getDiff(1,0);
	getSum(1,0);
	printf("%d\n",ans);
	return 0;
}
