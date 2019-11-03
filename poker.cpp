#include<bits/stdc++.h>
using namespace std;
long long typedef LL;
const int MAXN = 1E5 + 5;
const LL mod = 1E9 + 7;
int n,A[MAXN];
LL ans1,ans2;
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
	for(int i = 1 ; i <= n ; i ++)	A[i] = read();
	sort(A + 1,A + 1 + n);
}
void Calc()
{
	int j = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		while(A[j + 1] < A[i])	j ++;
		ans1 = (ans1 + j) % mod;
		ans2 = (ans2 + n - 1 - j) % mod;
	}
	for(int i = 1 ; i <= n ; i ++)	
	{
		if(i == 2 || i == (n - 1))	continue;
		ans1 = ans1 * i % mod;
		ans2 = ans2 * i % mod;	
	}
	printf("%lld %lld\n",ans1,ans2);
}
int main()
{
	freopen("poker.in","r",stdin);
	freopen("poker.out","w",stdout);
	Read();
	Calc();
	return 0;
}
