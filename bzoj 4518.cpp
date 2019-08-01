#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
using namespace std;
long long typedef LL;
const int MAXN = 3E3 + 5;
const LL inf = 1ll << 60;
int n,m;
int A[MAXN],Sum[MAXN];
LL f[3][MAXN],sum;
void Read()
{
	scanf("%d%d",&n,&m);
	for(int i = 1 ; i <= n ; i ++)
	{
		scanf("%d",&A[i]);
		sum += A[i];
		Sum[i] = Sum[i - 1] + A[i];
	}
}
void Solve(int cur,int nl,int nr,int ll,int lr)
{
	int mid = (nl + nr) / 2 , last = cur ^ 1 , best = ll;
	for(int i = ll ; i <= lr ; i ++)
	{
		if(f[last][i] + LL(Sum[mid] - Sum[i]) * (Sum[mid] - Sum[i]) < f[cur][mid])	
		{
			f[cur][mid] = f[last][i] + LL(Sum[mid] - Sum[i]) * (Sum[mid] - Sum[i]);
			best = i;
		}
	}
	if(nl <= mid - 1)	Solve(cur,nl,mid-1,ll,best);
	if(mid + 1 <= nr)	Solve(cur,mid+1,nr,best,lr);
}
void Dp()
{
	int type = 0;
	for(int i = 1 ; i <= n ; i ++)	f[0][i] = Sum[i] * Sum[i];
	for(int i = 2 ; i <= m ; i ++)
	{
		type ^= 1;
		for(int j = 1 ; j <= n ; j ++)	f[type][j] = inf;
		Solve(type,1,n,1,n);
	} 
	printf("%lld\n",m * f[type][n] - sum * sum);
}
int main()
{
	freopen("bzoj 4518.in","r",stdin);
	freopen("bzoj 4518.out","w",stdout);
	Read();
	Dp();
	return 0;
}
