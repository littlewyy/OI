#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
int T;
LL a0,a1,b0,b1;
LL Gcd(LL a,LL b)
{
	while(b)
	{
		LL c = a % b;
		a = b;
		b = c;
	}
	return a;
}
int main()
{
	freopen("luogu 1072.in","r",stdin);
	freopen("luogu 1072.out","w",stdout);
	scanf("%d",&T);
	while(T --)
	{
		scanf("%lld %lld %lld %lld",&a0,&a1,&b0,&b1);
		//x为b1的因数，a1的倍数
		/*for(LL x = a1 ; (x * x) <= b1 ; x += a1)
		{
			if((b1 % x) != 0)	continue;//枚举小于等于根号b1的因数 
			if(Gcd(x / a1 , p) == 1 && Gcd(b1 / x , q) == 1)	
			{
				ans ++;
				printf("%lld\n",x);
			}
			LL y = b1 / x;
			if((x * x) != b1 && ((b1 / x) % a1) == 0 && Gcd(b1 / x / a1 , a0 / a1) == 1 && Gcd(x , b1 / b0) == 1)
			{
				ans ++;
				printf("%lld\n",b1 / x);
			}			
		}*/
		//有严重的问题：外层应枚举b1的因数，只枚举出大小在根号n以内的。
		//注意x与b1 / x与a1是否 整除没有直接联系。故枚举因数时不能直接枚举a1的倍数。
		//可能x是b1的因数，x不是a1的倍数，但b1 / x是a1的倍数。这就计数错误了。
		//以后；能不投机先不投机。投机之前列清楚是否等价。
		LL ans = 0 , p = a0 / a1 , q = b1 / b0;
		for(LL x = 1 ; x * x <= b1 ; x ++)
		{
			if((b1 % x) != 0)	continue;//枚举小于等于根号b1的因数 
			if(x % a1 == 0 && Gcd(x / a1 , p) == 1 && Gcd(b1 / x , q) == 1)	ans ++;
			LL y = b1 / x;
			if(x != y && y % a1 == 0 && Gcd(y / a1 , p) == 1 && Gcd(b1 / y , q) == 1)				
				ans ++;	
		}
		printf("%lld\n",ans);
	}	
	return 0;
}
