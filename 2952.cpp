#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
LL T,a,b,c,d;
LL read()
{	
	char ch = getchar();
	LL w = 0 , f = 1;
	while(ch != '-' && (ch < '0' || ch > '9'))	ch = getchar();
	if(ch == '-')	f = -1 , ch = getchar();
	while(ch >= '0' && ch <= '9')	
	{
		w = w * 10 + ch - '0';
		ch = getchar();
	}
	return w * f;
}
void getAns(LL a,LL b,LL c,LL d,LL &x,LL &y)
{
	if(b * c < a * d)	swap(a,c) , swap(b,d);
	if(b > a && d < c)	{x = 1 , y = 1;return;}
	if(d >= c)	
	{
		LL k = d / c;
		getAns(a,b - a * k,c,d - c * k,x,y);
		y += x * k;
	}
	else	if(b <= a)	getAns(b,a,d,c,y,x);	
}
int main()
{
	freopen("2952.in","r",stdin);
	freopen("2952.out","w",stdout);
	T = read();
	while(T --)
	{
		LL a = read() , b = read() , c = read() , d = read();
		LL x,y;
		getAns(a,b,c,d,x,y);
		printf("%lld %lld\n",x,y);
	}
	return 0;
}
