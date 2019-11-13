#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const LL mod = 1E9 + 7;
const int MAXN = 1E3 + 5;
int n,m;
LL Fac[MAXN],g[MAXN],Inv[MAXN];
LL f[MAXN][MAXN][3][3];
LL getPow(LL x,LL times)
{
	LL ans = 1 , w = x;
	while(times)
	{
		if(times & 1)	ans = ans * w % mod;
		w = w * w % mod , times >>= 1;
	}
	return ans;
}
void Init()
{
	Fac[0] = 1;
	for(int i = 1 ; i <= 1000 ; i ++)	Fac[i] = Fac[i - 1] * i % mod;
	Inv[1000] = getPow(Fac[1000],mod - 2);
	for(int i = 999 ; i >= 0 ; i --)	Inv[i] = Inv[i + 1] * (i + 1) % mod;
}
void Dp()
{
	f[n - 1][0][0][0] = f[n - 1][1][1][0] = f[n - 1][1][2][0] = f[n - 1][1][0][1] = f[n - 1][2][1][1] = f[n - 1][2][2][1] = 1;
	for(int i = n - 1 ; i >= 2 ; i --)
	{
		//刷表法转移
		for(int j = 0 ; j <= n - i + 1 ; j ++)
		{
			for(int a = 0 ; a <= 2 ; a ++)
			{
				for(int b = 0 ; b <= 2 ; b ++)
				{
					if(!f[i][j][a][b])	continue;
					f[i - 1][j][0][a] = (f[i - 1][j][0][a] + f[i][j][a][b]) % mod;
					if(b != 1)	f[i - 1][j + 1][2][a] = (f[i - 1][j + 1][2][a] + f[i][j][a][b]) % mod;
					if(i - 1 > 1)	f[i - 1][j + 1][1][a] = (f[i - 1][j + 1][1][a] + f[i][j][a][b]) % mod;
				}
			}
		} 
	}
}
LL C(int x,int y)
{
	return Fac[x] * Inv[y] % mod * Inv[x - y] % mod;
}
void Calc()
{
	LL ans = 0 , type = 1;
	for(int i = m ; i <= n ; i ++)
	{
		for(int a = 0 ; a <= 2 ; a ++)
		{
			for(int b = 0 ; b <= 2 ; b ++)
			{
				g[i] = (g[i] + f[1][i][a][b]) % mod;
			}
		}
		//printf("%lld\n",g[i]);
		ans = (ans + g[i] * C(i,m) % mod * Fac[n - i] % mod * type + mod) % mod;
		type = -type;
	}
	//dp从n - 2开始的，意味着数的个数大于2。小于2的要特判 
	if(n == 1)	
	{
		if(m == 0)	ans = 1;
		else	ans = 0;
	}
	if(n == 2)	
	{
		if(m == 0 || m == 2)	ans = 1;
		else	ans = 0;
	}
	printf("%lld\n",ans);
}
int main()
{
	freopen("cf 285E.in","r",stdin);
	freopen("cf 285E.out","w",stdout);
	cin >> n >> m;
	Init();
	Dp();
	Calc();
	return 0;
}
