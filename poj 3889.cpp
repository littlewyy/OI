#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
unsigned long long typedef LL;
int T,n;
LL a,b;
pair<LL,LL> Calc(int n,LL p)
{
	if(n == 0) return make_pair(0,0);
	LL len = 1ll << (n - 1) , each = 1ll << (2 * n - 2);
	pair<LL,LL> next = Calc(n - 1,p % each);
	LL x = next.first , y = next.second;
	LL t = p / each;
	if(t == 0)	return make_pair(y,x);
	if(t == 1)	return make_pair(x,y + len);
	if(t == 2)	return make_pair(x + len,y + len);
	if(t == 3)	return make_pair(2 * len - y - 1, len - x - 1);
}
int main()
{
	freopen("poj 3889.in","r",stdin);
	freopen("poj 3889.out","w",stdout);
	scanf("%d",&T);
	while(T --)
	{
		scanf("%d%lld%lld",&n,&a,&b);
		pair<LL,LL> pos1 = Calc(n,a - 1);//标号从0开始。
		pair<LL,LL> pos2 = Calc(n,b - 1);
		LL x = pos1.first - pos2.first , y = pos1.second - pos2.second;
		//printf("%lld %lld\n",x,y);
		printf("%.0f\n",(double)sqrt(x * x + y * y) * 10);
	}
	return 0;
}
