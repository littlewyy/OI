#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
LL n,m,k,x;
LL getPow(LL a,LL b)
{
	LL cur = 1 , w = a;
	while(b)
	{
		if(b & 1)	cur = cur * w % n;
		w = w * w % n , b >>= 1;
	}
	return cur;
}
int main()
{
	freopen("luogu 1965.in","r",stdin);
	freopen("luogu 1965.out","w",stdout);
	scanf("%lld %lld %lld %lld",&n,&m,&k,&x);
	LL ans = getPow(10,k);//10^k % n
	ans = (x + ans * m % n) % n;
	printf("%lld\n",ans);
	return 0;
}
