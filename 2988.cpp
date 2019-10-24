#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 2005;
const LL mod = 998244353;
int n,k,tail;
int Vis[2 * MAXN],Q[MAXN];//存储各条链中的点数 
LL f[MAXN][MAXN][2],g[MAXN][MAXN],Fact[MAXN];
void Read()
{
	scanf("%d%d",&n,&k);
	for(int i = 1 ; i <= n ; i ++)
	{
		int x = i , num;
		if(Vis[x] == 0)//左边点出发 
		{
			num = 0;
			while(1)
			{
				Vis[x] = 1 , num ++;
				if(x > n)	
				{
					if(x - n + k <= n)	x = x - n + k;
					else	break;
				}
				else
				{
					if(x + k <= n)	x = x + k + n;
					else	break;
				}
			}			
			//得到链长
			if(num > 1)	Q[++ tail] = num; 
		}
		x = i + n;//右边点出发 
		if(Vis[x] == 0)
		{
			num = 0;
			while(1)
			{
				Vis[x] = 1 , num ++;
				if(x > n)	
				{
					if(x - n + k <= n)	x = x - n + k;
					else	break;
				}
				else
				{
					if(x + k <= n)	x = x + k + n;
					else	break;
				}
			}			
			//得到链长
			if(num > 1)	Q[++ tail] = num; 
		}
	}
	//for(int i = 1 ; i <= tail ; i ++)	printf("%d ",Q[i]);
}
void Dp()
{
	f[2][0][0] = f[2][1][1] = 1;
	for(int i = 3 ; i <= n ; i ++)
	{
		f[i][0][0] = 1;
		for(int j = 1 ; j < i ; j ++)
		{
			f[i][j][1] = f[i - 1][j - 1][0];
			f[i][j][0] = (f[i - 1][j][0] + f[i - 1][j][1]) % mod;
		}
	}
}
void Calc()
{
	//nsiz1 + nsiz2 + .. + nsiz? = n ^ 2
//	printf("%lld %lld\n",f[2][1][0],f[2][1][1]);
	for(int i = 0 ; i <= tail ; i ++)	g[i][0] = 1;
	for(int i = 1 ; i <= tail ; i ++)
	{
		int siz = Q[i];//第i条链的长度  
		for(int j = 1 ; j <= n ; j ++)//枚举选的总边数 
		{
			g[i][j] = g[i - 1][j];//第i条链上不选 
			for(int k = 1 ; k < siz && k <= j ; k ++)//枚举在第i组中选择的边数 
				g[i][j] = (g[i][j] + g[i - 1][j - k] * ((f[siz][k][0] + f[siz][k][1]) % mod) % mod) % mod;
		}
		/*if(i == 1)	
		{
			for(int j = 1 ; j <= n ; j ++)
				printf("%lld ",g[i][j]);
			printf("\n");
		}*/
	}
	
	Fact[0] = 1;
	for(int i = 1 ; i <= n ; i ++)	Fact[i] = Fact[i - 1] * i % mod;
	
//	printf("%lld %lld\n",g[2][1],g[2][2]);
	LL ans = 0;
	for(int i = 0 ; i <= n ; i ++)
	{
		int type;
		if(i % 2)	type = -1;else	type = 1;
		ans = (ans + mod + type * g[tail][i] % mod * Fact[n - i] % mod) % mod;
	}
	printf("%lld\n",ans);
}
int main()
{
	freopen("2988.in","r",stdin);
	freopen("2988.out","w",stdout);
	Read();
	Dp();
	Calc();
	return 0;
}
