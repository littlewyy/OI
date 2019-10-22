#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 1E5 + 5;
int n;
int A[MAXN],Diff[MAXN];
LL ans,up,dow,met;
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
	n = read();
	for(int i = 1 ; i <= n ; i ++)	
	{
		A[i] = read();
		Diff[i] = A[i] - A[i - 1];
		if(i == 1)	continue;
		if(Diff[i] > 0)	up += Diff[i];
		else	dow += Diff[i];
	}	
}
void Calc()
{
	ans = max(up,-dow);
	met = abs(up + dow) + 1;
	printf("%lld\n%lld\n",ans,met);
}
int main()
{
	freopen("luogu 4552.in","r",stdin);
	freopen("luogu 4552.out","w",stdout);
	Read();
	Calc();
	return 0;
}
