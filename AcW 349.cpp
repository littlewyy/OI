#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 1005 , inf = 0x3f3f3f3f;
const LL mod = (1ll << 31) - 1;
int n,m,A[MAXN][MAXN],Dis[MAXN],Vis[MAXN];//邻接矩阵。 
LL ans;
struct wyy
{
	int dis,id;
	bool operator < (const wyy &t)const
	{
		return dis < t.dis;
	}
}D[MAXN];
void Read()
{
	scanf("%d%d",&n,&m);
	memset(A,0x3f,sizeof(A));
	for(int i = 1 ; i <= m ; i ++)
	{
		int x,y,l;
		scanf("%d%d%d",&x,&y,&l);
		A[x][y] = A[y][x] = min(A[x][y],l);
	}	
}
int getMin()
{
	int id = -1 , mina = inf;
	for(int i = 1 ; i <= n ; i ++)
	{
		if(Vis[i] == 0 && Dis[i] < mina)
		{
			id = i;
			mina = Dis[i];
		}
	}
	return id;
}
void Relax(int x)
{
	for(int i = 1 ; i <= n ; i ++)	
		Dis[i] = min(Dis[i],Dis[x] + A[x][i]);
}
void Dijkstra()
{
	memset(Dis,0x3f,sizeof(Dis));
	memset(Vis,0,sizeof(Vis));
	Dis[1] = 0;
	for(int i = 1 ; i < n ; i ++)
	{
		int id = getMin();
		if(id == -1)	break;
		Vis[id] = 1;
		Relax(id);
	}
}
void Calc()
{
	for(int i = 1 ; i <= n ; i ++)	if(Dis[i] == inf)	{printf("0\n");return;}
	for(int i = 1 ; i <= n ; i ++)
	{
		D[i].dis = Dis[i];
		D[i].id = i;
	}
	sort(D + 1 , D + 1 + n);
	
	ans = 1;//仅有1点时，方案数为1 
	for(int i = 2 ; i <= n ; i ++)
	{
		int num = 0;
		for(int j = 1 ; j < i ; j ++)
			if(D[j].dis + A[D[j].id][D[i].id] == D[i].dis)
				num ++;
		ans = ans * num % mod;
	}
	printf("%lld\n",ans);
}
int main()
{
	freopen("AcW 349.in","r",stdin);
	freopen("AcW 349.out","w",stdout);
	Read();
	Dijkstra();
	Calc();
	return 0;
}
