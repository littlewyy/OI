#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 505;
const LL mod = 998244353;
int n,m;
int A[MAXN],Mid[MAXN][MAXN];
LL f[MAXN][MAXN],g[MAXN][MAXN];
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
	for(int i = 1 ; i <= n ; i ++)	A[i] = read();
	for(int l = 1 ; l <= n ; l ++)
	{
		for(int r = l ; r <= n ; r ++)
		{
			int mina = n + 1;
			//Mid[l,r]:[l,r]中最小的元素所在的位置。 
			for(int k = l ; k <= r ; k ++)
				if(A[k] < mina)	
					Mid[l][r] = k , mina = A[k];
		}
	}
	/*for(int i = 1 ; i <= n ; i ++)	
	{
		for(int j = i ; j <= n ; j ++)
			printf("%d ",Mid[i][j]);
		printf("\n");
	}*/
} 
void Dp()
{
	for(int i = 1 ; i <= n ; i ++)	f[i][i] = 1 , g[i][i] = 2;
	for(int i = 1 ; i <= n + 1; i ++)	f[i][i - 1] = g[i][i - 1] = 1;
	for(int len = 2 ; len <= n ; len ++)
	{
		for(int i = 1 ; i + len - 1 <= n ; i ++)
		{
			int j = i + len - 1 , mid = Mid[i][j];
			for(int l = i ; l <= mid ; l ++)//枚举mid的覆盖区域 
				f[i][j] = (f[i][j] + f[i][l - 1] * f[l][mid - 1] % mod * g[mid + 1][j] % mod) % mod;
			for(int k = i - 1 ; k <= j ; k ++)	g[i][j] = (g[i][j] + f[i][k] * f[k + 1][j] % mod) % mod; 
		}
	}
/*	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = 1 ; j <= n ; j ++)
		{
			printf("%d %d %lld\n",i,j,f[i][j]);
		}
	}
	printf("\n");*/
	printf("%lld\n",f[1][n]);
}
int main()
{
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	Read();
	Dp();
	return 0;
}
