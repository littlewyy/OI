#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 1005 , MAXM = 1E4 + 5;
const LL mod = 1e9 + 7;
int n,x,maxa;
int A[MAXN],B[MAXN],C[MAXN];
LL f[MAXN][MAXM];
LL g[MAXN][2 * MAXM];
LL ans = 0;
void Read()
{
	scanf("%d%d",&n,&x);
	for(int i = 1 ; i <= n ; i ++)
	{
		scanf("%d%d%d",&A[i],&B[i],&C[i]);
		maxa = max(maxa,A[i]);//面值最大值。 
	}		
}
void Dp1()
{
	f[0][0] = 1;
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = 0 ; j <= maxa - 1 ; j ++)
		{
			f[i][j] = f[i - 1][j];//第i项不参与 
			if(j >= A[i])	f[i][j] = (f[i][j] + f[i][j - A[i]]) % mod;
			if(j >= A[i] * (C[i] + 1))	f[i][j] = (f[i][j] - f[i - 1][j - A[i] * (C[i] + 1)] + mod) % mod;
		}
 	}
}
void Dp2()
{
	g[n + 1][0] = 1;
	for(int i = n ; i >= 1 ; i --)//从第i个到第n个， 
	{
		for(int j = 0 ; j <= x + maxa - 1 ; j ++)//总共给出j 
		{
			if(j >= A[i])//至少有1个i参与 
			{
				g[i][j] = g[i][j - A[i]];
				if(j >= A[i] * (B[i] + 1))	g[i][j] = (g[i][j] - g[i + 1][j - A[i] * (B[i] + 1)] + mod) % mod;
				if(j >= x && j <= x + A[i] - 1)	ans = (ans + g[i][j] * f[n][j - x] % mod) % mod;
			}
			g[i][j] = (g[i][j] + g[i + 1][j]) % mod;
		}
	}
	printf("%lld\n",ans);
}
int main()
{
	freopen("2944.in","r",stdin);
	freopen("2944.out","w",stdout);
	Read();
	Dp1();
	Dp2();
	return 0;
}
