#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long typedef LL;
const int MAXN = 405;
const LL inf = 1ll << 60;
int n,k;
int A[MAXN],Mx[MAXN][10],Pow[MAXN];
LL f[MAXN][MAXN],Sum[MAXN];
void Read()
{
	scanf("%d%d",&n,&k);
	k ++;//包括初始。 
	for(int i = 1 ; i <= n ; i ++)	
	{
		scanf("%d",&A[i]);
		Mx[i][0] = A[i];
		Sum[i] = Sum[i - 1] + A[i];
	}
}
void Rmq()
{
	for(int L = 1 ; L < 10 ; L ++)
	{
		int len = 1 << L;
		for(int i = 1 ; i + len - 1 <= n ; i ++)
			Mx[i][L] = max(Mx[i][L - 1],Mx[i + (1 << (L - 1))][L - 1]);//位运算加括号。你个sb 
	}
	Pow[1] = 0;
	for(int i = 2 ; i <= n ; i ++)
	{
		Pow[i] = Pow[i - 1];
		if((1 << (Pow[i] + 1)) < i)	Pow[i] ++;
	}
}
int getMax(int l,int r)
{
	int len = r - l + 1 , siz = Pow[len];
	return max(Mx[l][siz],Mx[r - (1 << siz) + 1][siz]);
}
void Dp()
{
	for(int i = 0 ; i <= n ; i ++)	
		for(int j = 0 ; j <= k ; j ++)
			f[i][j] = inf; 
	f[0][0] = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = 1 ; j <= min(k,i) ; j ++)
		{
			for(int li = 0 ; li < i ; li ++)	
			{
				if(f[li][j - 1] == inf)	continue;
				f[i][j] = min(f[i][j],f[li][j - 1] + getMax(li + 1,i) * LL(i - li) - (Sum[i] - Sum[li]));
			}
		}
	}
	printf("%lld\n",f[n][k]);
}
int main()
{
	freopen("2913.in","r",stdin);
	freopen("2913.out","w",stdout);
	Read();
	Rmq();
	Dp();
	return 0;
}
