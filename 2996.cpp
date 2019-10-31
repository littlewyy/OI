#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 1E5 + 5;
const LL mod = 998244353;
LL f[MAXN],g[MAXN],Pow[MAXN];
void Init()
{
	Pow[0] = 1;
	for(int i = 1 ; i < MAXN ; i ++)	Pow[i] = Pow[i - 1] * i % mod;
	
	f[1] = 1 , g[1] = 1;
	for(int i = 2 ; i < MAXN ; i ++)
	{
		f[i] = ((f[i - 1] + Pow[i - 1]) % mod + 2 * g[i - 1] % mod) % mod;
		f[i] = (f[i] + (i - 1) * f[i - 1] % mod) % mod;
		g[i] = ((g[i - 1] + Pow[i - 1]) % mod + (i - 1) * g[i - 1] % mod) % mod;
	}
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
void Calc()
{
	int q = read();
	while(q --)
	{
		int x = read();
		printf("%lld\n",f[x]);
	}
}
int main()
{
	freopen("2996.in","r",stdin);
	freopen("2996.out","w",stdout);
	Init();
	Calc();
	return 0;
}

