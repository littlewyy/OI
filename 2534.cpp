#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 1E5 + 5;
int n,m,r;
int C[MAXN],R[MAXN];
LL SumR[MAXN],SumC[MAXN],SumF[MAXN],SumQ[MAXN];
struct wyy
{
	int q,p;
}S[MAXN];
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
void Read()
{
	n = read() , m = read() , r = read();
	for(int i = 1 ; i <= n ; i ++)	C[i] = read();
	for(int i = 1 ; i <= m ; i ++)	S[i].q = read() , S[i].p = read();
	for(int i = 1 ; i <= r ; i ++)	R[i] = read();
}
bool cmp(int x,int y)
{
	return x > y;
}
bool cmp2(wyy x,wyy y)
{
	return x.p > y.p;
}
int Div(LL sum)
{
	int lo = 0 , hi = m + 1;
	while(lo + 1 < hi)
	{
		int mid = (lo + hi) >> 1;
		if(SumQ[mid] <= sum)	lo = mid;
		else	hi = mid;
	}
	return lo;
}
LL getExtra(LL sum)
{
	int id = Div(sum);
	LL ans = SumF[id];
	if(sum > SumQ[id] && id < m)	ans += (sum - SumQ[id]) * S[id + 1].p;
	return ans;
}
void Calc()
{
	sort(C + 1 , C + 1 + n , cmp);//c从大到小排  
	sort(S + 1 , S + 1 + m , cmp2);//p从大到小排 
	sort(R + 1 , R + 1 + r , cmp);//r从大到小排 
	for(int i = 1 ; i <= m ; i ++)	SumQ[i] = SumQ[i - 1] + S[i].q;
	for(int i = 1 ; i <= m ; i ++)	SumF[i] = SumF[i - 1] + LL(S[i].q) * S[i].p;
	for(int i = 1 ; i <= n ; i ++)	SumC[i] = SumC[i - 1] + C[i];
	for(int i = 1 ; i <= r ; i ++)	SumR[i] = SumR[i - 1] + R[i];
	//i头给小卖部  
	LL ans = 0;
	for(int i = 0 ; i <= n ; i ++)
	{
		if(n - i > r)	continue;
		//n - i头给农场 
		LL nans = SumR[n - i] + getExtra(SumC[i]);
		ans = max(ans,nans);
	}
	printf("%lld\n",ans);
}
int main()
{
	freopen("2534.in","r",stdin);
	freopen("2534.out","w",stdout);
	Read();
	Calc();
	return 0;
}
