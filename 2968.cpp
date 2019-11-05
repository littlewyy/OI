#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 5E5 + 5;
const LL mod = 323232323;
LL n;
LL A[MAXN],Fac[MAXN * 2],Inv[MAXN * 2];
LL P[MAXN],Dev[MAXN];
LL read()
{
	char ch = getchar();LL w = 0;
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
	n = read();
	for(int i = 1 ; i <= n ; i ++)	A[i] = read();
}
LL getPow(LL x,LL times)
{
	//特判：0的任意次方都是1
	if(x == 0)	return 1ll % mod; 
	LL nans = 1 , w = x;
	while(times)
	{
		if(times & 1)	nans = nans * w % mod;
		w = w * w % mod , times >>= 1;
	}
	return nans;
}
void Init()
{
	Fac[0] = 1;
	for(int i = 1 ; i < 2 * MAXN ; i ++)	Fac[i] = Fac[i - 1] * i % mod;
	//预处理阶乘的逆元
	Inv[2 * MAXN - 1] = getPow(Fac[2 * MAXN - 1],mod - 2);
	for(int i = 2 * MAXN - 2 ; i >= 0 ; i --)	Inv[i] = Inv[i + 1] * (i + 1) % mod; 
	//for(int i = 1 ; i < 100 ; i ++)	printf("%lld %lld\n",Pow[i],Fac[i]);
}
LL C(LL x,LL y)
{
	LL nans = 1;
	nans = nans * Fac[x] * Inv[x - y] % mod * Inv[y] % mod;//细心！ 
	return nans;
}
void Dp()
{
	//printf("%lld\n",C(1,0));
	//printf("%lld %lld %lld\n",Inv[0],Inv[1],Inv[2]);
	for(int i = 0 ; i < MAXN ; i ++)	
	{
		P[i] = C(A[1] + i - 1,i) * getPow(Inv[2],A[1] + i) % mod;
		//if(i == 0)	printf("%d %d %lld\n",A[1] + i - 1 , i , C(A[1] + i - 1,i));
		Dev[i] = P[i] * i % mod;
		if(i)	P[i] = (P[i - 1] + P[i]) % mod , Dev[i] = (Dev[i - 1] + Dev[i]) % mod;
		if(i < 100)	printf("%lld\n",P[i]);
		//printf("%lld %lld\n",P[i],Dev[i]);
	}
	//printf("%lld\n",P[0]);
	LL ans = A[1];
	for(int i = 2 ; i <= n ; i ++)
	{
		ans = (ans + Dev[A[i]]) % mod;
		ans = (ans + (1 - P[A[i]] + mod) % mod * A[i] % mod) % mod;
	}
	printf("%lld\n",ans);
}
int main()
{
	freopen("2968.in","r",stdin);
	//freopen("2968.out","w",stdout);
	freopen("std.out","w",stdout);
	Read();
	Init();
	Dp();
	return 0;
}
