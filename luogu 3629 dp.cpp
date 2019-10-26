#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1E5 + 5;
int n,k,cur,ans,dsum;
int Head[MAXN];
int f[MAXN][5],g[MAXN],d[MAXN];
struct wyy
{
	int to,next;
}Edge[2 * MAXN];
void Add(int from,int to)
{
	Edge[++ cur].to = to;
	Edge[cur].next = Head[from];
	Head[from] = cur;
	
	Edge[++ cur].to = from;
	Edge[cur].next = Head[to];
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
	n = read() , k = read();
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i < n ; i ++)
	{
		int x = read() , y = read();
		Add(x,y);
	}
}
bool cmp(int x,int y)	{return x > y;}
void DFS(int x,int fa)
{
	int maxd = 0 , premaxd = 0;
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(y == fa)	continue;
		DFS(y,x);	
		//其实不然。路径数可以少不可以多，因为除了长度为1的路径，任意路径都可被拆分成2条路径。 
		dsum = max(dsum,maxd + d[y]);//d[y1] + d[y2]
		premaxd = maxd;
		maxd = max(maxd,d[y]);
		
		dsum = max(dsum,f[x][0] + f[x][1] + d[y]);
		dsum = max(dsum,f[x][0] + g[y] + 1);
		dsum = max(dsum,g[x] + f[y][0] + 1);
		
		g[x] = max(g[x],premaxd + f[y][0] + 1);
		g[x] = max(g[x],f[x][0] + d[y]);
	    g[x] = max(g[x],g[y] + 1);		
		
		if(f[y][0] + 1 > f[x][3])	f[x][3] = f[y][0] + 1;
		sort(f[x],f[x] + 4,cmp);
		
		d[x] = max(d[x],d[y]);
		d[x] = max(d[x],f[x][0] + f[x][1]);
		g[x] = max(g[x],f[x][0] + f[x][1] + f[x][2]);
		dsum = max(dsum,f[x][0] + f[x][1] + f[x][2] + f[x][3]);
	}
}
int main()
{
	freopen("luogu 3629.in","r",stdin);
	freopen("luogu 3629.out","w",stdout);
	Read();
	DFS(1,0);
	if(k == 1)	ans = 2 * (n - 1) - (d[1] - 1);
	else	ans = 2 * n - dsum;
	printf("%d\n",ans);	
	return 0;
}
//我讨厌这种恶心的树形DP！太恶心辣！ 
