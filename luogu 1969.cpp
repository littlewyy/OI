#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1E5 + 5;
int n;
int A[MAXN],Diff[MAXN];
long long ans = 0;
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
	}
	Diff[n + 1] = -A[n];
}
void Calc()
{
	long long ans = 0;
	for(int i = 1 ; i <= n + 1 ; i ++)
	{
		if(Diff[i] > 0)
			ans += Diff[i];
	}
	printf("%lld\n",ans);
}
int main()
{
	freopen("luogu 1969.in","r",stdin);
	freopen("luogu 1969.out","w",stdout);
	Read();
	Calc();
	return 0;
}
