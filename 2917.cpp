#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
long long typedef LL;
const LL MAXN = 25;
const LL mod = 1e9 + 7;
LL n,s,A[MAXN];
void Read()
{
	scanf("%lld%lld",&n,&s);
	for(LL i = 1 ; i <= n ; i ++)	scanf("%lld",&A[i]);
}
LL getFrac(LL x)
{
	LL cur = 1ll;
	for(LL i = 1 ; i <= x ; i ++)
		cur = cur * i % mod;
	return cur;
}
LL getPow(LL x,LL times)
{
	if(times == 0)	return 1ll % mod;
	LL cur = 1ll % mod;
	LL half = getPow(x,times >> 1ll);
	cur = half * half % mod;
	if(times & 1ll)	cur = cur * x % mod;
	return cur;	
}
LL getAns(LL nown)
{
	LL nowm = n - 1 , cur = 1ll;
	for(LL i = nown ; i >= nown - nowm + 1 ; i --)	cur = cur * i % mod;
	return cur;
}
void Calc()
{
	LL rev = getPow(getFrac(n - 1),mod - 2) , ans = 0; // (n-1)! 的乘法逆元
	for(LL i = 0 ; i < (1ll << n) ; i ++)
	{
		LL cnt = s , type = 1;
		for(LL j = 0 ; j < n ; j ++)
		{
			if((1ll << j) & i)	
				cnt -= A[j + 1] + 1 ,
				type = - type;
		}
		//cnt个分n组（可不放）C(cnt + n - 1 ,n - 1) 
        //涉及减法需要 + mod！ 
		if(cnt >= 0)	ans = (ans + mod + type * getAns(cnt + n - 1) * rev % mod) % mod; 
	}	
	printf("%lld\n",ans);
}
int main()
{
	freopen("2917.in","r",stdin);
	freopen("2917.out","w",stdout);
	Read();
	Calc();
	return 0; 
}
