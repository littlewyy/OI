#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
long long typedef LL;
const int MAXN = 2E5 + 5 , MAXM = 25;
const LL mod = 1e9 + 7;
int n,m,q;
int A[MAXN];
LL Ans[MAXN],f[MAXN][MAXM];
struct wyy
{
	int l,r,id;
	LL ans;
}Q[MAXN],Ql[MAXN],Qr[MAXN],Aft[MAXN];
void Read()
{
	scanf("%d%d",&n,&m);
	for(int i = 1 ; i <= n ; i ++)	
	{
		int x;
		scanf("%d",&x);
		A[i] = x % m;
	}
}
void Query()
{
	scanf("%d",&q);
	for(int i = 1 ; i <= q ; i ++)
	{
		scanf("%d%d",&Q[i].l,&Q[i].r);
		Q[i].id = i , Q[i].ans = 0;
	}
}
void Solve(int l,int r,int ql,int qr)
{
	int mid = (l + r) >> 1;
	if(l == r)	
	{
		int cur = 1;
		if(A[l] == 0)	cur ++;
		for(int i = ql ; i <= qr ; i ++)	
			Q[i].ans = cur % mod; 
		return;
	}
		
	for(int i = 0 ; i < m ; i ++)	f[mid][i] = 0;
	f[mid][0] = 1 , f[mid][A[mid]] ++;
	for(int i = mid - 1 ; i >= l ; i --)	
		for(int j = 0 ; j < m ; j ++)	
			f[i][j] = (f[i + 1][j] + f[i + 1][(j + m - A[i]) % m]) % mod;
			
	for(int i = 0 ; i < m ; i ++)	f[mid + 1][i] = 0;
	f[mid + 1][0] = 1, f[mid + 1][A[mid + 1]] ++;
	for(int i = mid + 2 ; i <= r ; i ++)
		for(int j = 0 ; j < m ; j ++)
			f[i][j] = (f[i - 1][j] + f[i - 1][(j + m - A[i]) % m]) % mod;
	
	for(int i = ql ; i <= qr ; i ++)
	{
		if(Q[i].l <= mid && Q[i].r > mid)	
		{
			for(int j = 0 ; j < m ; j ++)	
				Q[i].ans = (Q[i].ans + f[Q[i].l][j] * f[Q[i].r][(m - j) % m] % mod) % mod;
			
		}
	}
	//注意已知内容不可以被覆盖掉。 三种类型区分开。 
	int lef = 0 , rig = 0 , aft = 0;
	for(int i = ql ; i <= qr ; i ++)
	{
		if(Q[i].r <= mid)	Ql[++ lef] = Q[i];
		else	if(Q[i].l > mid)	Qr[++ rig] = Q[i];
		else	Aft[++ aft] = Q[i];
	}	
	for(int i = 1 ; i <= lef ; i ++)	Q[ql + i - 1] = Ql[i];
	for(int i = 1 ; i <= rig ; i ++)	Q[ql + lef + i - 1] = Qr[i];
	for(int i = 1 ; i <= aft ; i ++)	Q[ql + lef + rig + i - 1] = Aft[i];
	Solve(l,mid,ql,ql + lef - 1);
	Solve(mid + 1,r,ql + lef,ql + lef + rig - 1);
}
void Print()
{
	for(int i = 1 ; i <= q ; i ++)	Ans[Q[i].id] = Q[i].ans;
	for(int i = 1 ; i <= q ; i ++)	printf("%lld\n",Ans[i]);
}
int main()
{
	freopen("2916.in","r",stdin);
	freopen("2916.out","w",stdout);
	Read();
	Query();
	Solve(1,n,1,q);
	Print();
	return 0;
}
