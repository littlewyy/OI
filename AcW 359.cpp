#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1E5 + 5 , inf = 0x7fffffff;
int n,g,k,cur = -1;
int Head[MAXN],Fa[MAXN];
int Rt[MAXN],Nt[MAXN],f[MAXN][2];
struct wyy
{
	int to,next;
}Edge[MAXN];
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
}
int findA(int x)
{
	if(x == Fa[x])	return x;
	return Fa[x] = findA(Fa[x]);
}
void Read()
{
	n = read();//外向树：找到环中任一边即可 
	memset(Head,-1,sizeof(Head));
	for(int i = 1 ; i <= n ; i ++)	Fa[i] = i;
	for(int i = 1 ; i <= n ; i ++)
	{
		int x = read();//x -> i
		int root1 = findA(x) , root2 = findA(i);
		if(root1 == root2)	
		{
			Rt[++ g] = i;
			Nt[g] = x;
		}
		else	Fa[root2] = root1 , Add(x,i);//只连树边 
	}
}
void Dp(int x)
{
	f[x][0] = 0;
	int diff = inf;
	for(int h = Head[x] ; h != -1 ; h = Edge[h].next)
	{
		int y = Edge[h].to;
		if(y != k)	Dp(y);
		f[x][0] += max(f[y][0],f[y][1]);
		diff = min(diff,max(f[y][0],f[y][1]) - f[y][0]);
	}
	f[x][1] = f[x][0] + 1 - diff;
}
void Calc()
{
	int ans = 0;
	for(int i = 1 ; i <= g ; i ++)
	{
		int rt = Rt[i] , nt = Nt[i] , nans;
		k = 0 , Dp(nt);
		k = nt , Dp(rt);
		nans = f[rt][1] , f[nt][1] = f[nt][0] + 1;
		Dp(rt);
		nans = max(nans,f[rt][0]); 
		ans += nans;
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("AcW 359.in","r",stdin);
	freopen("AcW 359.out","w",stdout);
	Read();
	Calc();
	return 0;
}
