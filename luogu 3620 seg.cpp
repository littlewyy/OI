#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
long long typedef LL;
const int MAXN = 1E5 + 5;
const LL inf = 1ll << 60;
int n,k;
int Pos[MAXN],Pre[MAXN],Next[MAXN];
LL Tree[MAXN * 4],D[MAXN];
void Build(int x,int l,int r)
{
	if(l == r)	
	{
		Tree[x] = D[l];
		return;
	}
	int mid = (l + r) >> 1 , ls = x << 1 , rs = ls | 1;
	Build(ls,l,mid);
	Build(rs,mid + 1,r);
	Tree[x] = min(Tree[ls],Tree[rs]);
}
int getPos(int x,int l,int r,LL val)
{
	if(l == r)	return l;
	int mid = (l + r) >> 1 , ls = x << 1 , rs = ls | 1;
	if(Tree[ls] == val)	return getPos(ls,l,mid,val);
	else	return getPos(rs,mid + 1,r,val);	
}
void Update(int x,int l,int r,int d,LL v)
{
	if(d < l || d > r)	return;//注意pre和next可能越界 
	if(l == d && r == d)	
	{
		Tree[x] = v;
		return;
	}
	int mid = (l + r) >> 1 , ls = x << 1 , rs = ls | 1;
	if(d <= mid)	Update(ls,l,mid,d,v);
	else	Update(rs,mid + 1,r,d,v);
	Tree[x] = min(Tree[ls],Tree[rs]);
}
void Read()
{
	scanf("%d%d",&n,&k);
	for(int i = 1 ; i <= n ; i ++)	
	{
		scanf("%d",&Pos[i]);
		if(i > 1)	D[i - 1] = Pos[i] - Pos[i - 1];
		if(i < n)	Pre[i] = i - 1 , Next[i] = i + 1;
	}
	Build(1,1,n - 1);//建线段树 
	Pre[0] = 0 , Next[n] = n;
} 
void Calc()
{
	long long ans = 0;
	D[0] = D[n] = inf;
	for(int i = 1 ; i <= k ; i ++)
	{
		int val = Tree[1] , pos = getPos(1,1,n - 1,val);
		int pre = Pre[pos], next = Next[pos] , ppre = Pre[pre] , nnext = Next[next];
		ans += val , D[pos] = D[pre] + D[next] - val;
		Next[ppre] = pos , Pre[pos] = ppre , Next[pos] = nnext , Pre[nnext] = pos;
		Update(1,1,n - 1,pre,inf) , Update(1,1,n - 1,next,inf) , Update(1,1,n - 1,pos,D[pos]);
	}
	printf("%lld\n",ans);
}
int main()
{
//	freopen("luogu 3620.in","r",stdin);
//	freopen("luogu 3620.out","w",stdout);
	Read();
	Calc();
	return 0;
}
