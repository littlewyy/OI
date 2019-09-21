#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
void Exgcd(LL a,LL b,LL &x,LL &y,LL c)
{
	if(b == 0)	{x = c / a , y = 0;return;}
	Exgcd(b,a % b,x,y,c);
	LL nx = y , ny = x - a / b * y;
	x = nx , y = ny;
}
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
	freopen("luogu 1082.in","r",stdin);
	freopen("luogu 1082.out","w",stdout);
	LL a,b,x,y;
	scanf("%lld%lld",&a,&b);
	Exgcd(a,b,x,y,1);
	LL add = b / Gcd(a,b);
	if(x <= 0)	x += add * (-x / add + 1);
	else	
	{
		x -= add * (x / add);
		if(x == 0)	x += add;
	}
	printf("%lld\n",x);
	return 0;
}
