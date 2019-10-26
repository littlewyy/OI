#include<bits/stdc++.h>
using namespace std;
double typedef db;
const int MAXN = 2E3 + 5;
const db eps = 1e-10;
int n,k;
db P[MAXN],f[MAXN][MAXN],g[MAXN][MAXN];
void Read()
{
	scanf("%d%d",&n,&k);
	for(int i = 1 ; i <= n ; i ++)	scanf("%lf",&P[i]);
	sort(P + 1 , P + 1 + n);
}
void Dp()
{
	f[0][0] = 1.00;
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = 0 ; j <= i ; j ++)
		{
			if(j)	f[i][j] = f[i - 1][j - 1] * P[i];
			f[i][j] += f[i - 1][j] * (1.00 - P[i]);
		}
	}
	g[n + 1][0] = 1.00;
	for(int i = n ; i >= 1 ; i --)
	{
		for(int j = 0 ; j <= n - i + 1 ; j ++)
		{
			if(j)	g[i][j] = g[i + 1][j - 1] * P[i];
			g[i][j] += g[i + 1][j] * (1.00 - P[i]);
		}
	}
}
void Calc()
{
	db ans = 0.00;
	for(int i = 0 ; i <= k ; i ++)
	{
		//细心！两者拼凑出k / 2个支持者，枚举所有情况。 
		db nans = 0.00;
		for(int j = 0 ; j <= k / 2 && j <= i ; j ++)
			nans += f[i][j] * g[n - k + i + 1][k / 2 - j];
		if(nans - ans > eps)	ans = nans;
	}				
	printf("%.10lf\n",ans);
}
int main()
{
	freopen("2992.in","r",stdin);
	freopen("2992.out","w",stdout);
	Read();
	Dp();
	Calc();
	return 0;
}
