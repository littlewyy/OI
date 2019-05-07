#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long typedef LL;
const int MAXN = 1e6 + 5;
const LL mod = 1e9 + 7;
int n;
int A[MAXN],Sum[MAXN];
LL f[MAXN];
int read()
{
	char ch = getchar();int w = 0;
	while(ch < '0' || ch > '9')	ch = getchar();
	while(ch >= '0' && ch <= '9')	
	{
		w = w * 10 + (int)(ch - '0');
		ch = getchar();
	}
	return w;
}
void Read()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++)
	{
		A[i] = read();
		Sum[A[i]] ++;
	}
}
LL Pow(int x)
{
	if(x == 0)	return 1;
	LL mid = Pow(x / 2) , nowAns = mid * mid % mod;
	if(x % 2)	nowAns = nowAns * 2 % mod;
	return nowAns;
}
void GetF()
{
	for(int bit = 1 ; bit <= 20 ; bit ++)
	{
		for(int i = 1e6 ; i >= 0 ; i --)
		{
			if(i & (1 << (bit - 1)))	
				Sum[i ^ (1 << (bit - 1))] += Sum[i];
		}
	}
	for(int i = 0 ; i <= 1e6 ; i ++)	f[i] = (Pow(Sum[i]) - 1 + mod) % mod;
}
LL getCnt(int x)
{
	int cnt = 0;
	for(int i = 0 ; i < 20 ; i ++)
	{
		if((1 << i) & x)	
			cnt ++;
	}
	return cnt;
}
void Calc()
{
	LL ans = 0;
	for(int i = 0 ; i <= 1e6 ; i ++)
	{
		int type;
		if(getCnt(i) % 2)	type = -1; else	type = 1;
		ans = (ans + type * f[i] + mod) % mod;
	}
	//printf("%I64d\n",ans);
	printf("%lld\n",ans);
}
int main()
{
	freopen("cf 449D.in","r",stdin);
	freopen("cf 449D.out","w",stdout);
	Read();
	GetF();
	Calc();
	return 0;
}
