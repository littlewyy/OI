#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 1E5 + 5;
LL n,t;
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
struct wyy
{
	LL w;
}A[MAXN];
struct sta
{
	LL d,p,val;
}B[MAXN];
void Read()
{
	n = read() , t = read();
	for(int i = 1 ; i <= n ; i ++)	A[i].w = read();
	for(int i = 1 ; i <= n ; i ++)	B[i].d = read();
	for(int i = 1 ; i <= n ; i ++)	B[i].p = read();
	for(int i = 1 ; i <= n ; i ++)	B[i].val = B[i].p - B[i].d * t;
}
bool cmp(wyy x,wyy y)
{
	return x.w > y.w;
}
bool cmp2(sta x,sta y)
{
	return x.val > y.val;
}
void Calc()
{
	sort(A + 1 , A + 1 + n , cmp);	
	sort(B + 1 , B + 1 + n , cmp2);
	LL ans = 0;
	for(int i = 1 ; i <= n ; i ++)
		ans = ans + A[i].w * B[i].val;
	printf("%lld\n",ans);
}
int main()
{
	freopen("2985.in","r",stdin);
	freopen("2985.out","w",stdout);
	Read();
	Calc();
	return 0;
}
