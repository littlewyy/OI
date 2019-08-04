#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cstdlib>
using namespace std;
const int MAXN = 4E4 + 5 , MAXK = 55;
int n,k;
int Pre[MAXN],Pos[MAXN],A[MAXN],f[MAXK][MAXN];
int Tree[4 * MAXN],Delay[4 * MAXN];
void Read()
{
	scanf("%d%d",&n,&k);
	for(int i = 1 ; i <= n ; i ++)	
	{
		scanf("%d",&A[i]);
		Pre[i] = Pos[A[i]];
		Pos[A[i]] = i;
	}
}
void Build(int x,int l,int r,int c)//将0~n-1存入1~n中 
{
	Delay[x] = 0;
	if(l == r)	
	{
		Tree[x] = f[c][l - 1];
		return;
	}
	int mid = (l + r) >> 1 , ls = x << 1 , rs = ls | 1;
	Build(ls,l,mid,c);
	Build(rs,mid + 1,r,c);
	Tree[x] = max(Tree[ls],Tree[rs]);
}
void PushDown(int x,int ls,int rs)//传Delay标记 
{
	Tree[ls] += Delay[x] , Tree[rs] += Delay[x];
	Delay[ls] += Delay[x], Delay[rs] += Delay[x];
	Delay[x] = 0;
}
void Update(int x,int l,int r,int s,int t)//[s,t]区间加1 
{
	if(s <= l && r <= t)	
	{
		Tree[x] ++;//最大值 
		Delay[x] ++;
		return;
	}
	int mid = (l + r) >> 1 , ls = x << 1 , rs = ls | 1;
	PushDown(x,ls,rs);
	if(s <= mid)	Update(ls,l,mid,s,t);
	if(t > mid)	Update(rs,mid + 1,r,s,t);
	Tree[x] = max(Tree[ls],Tree[rs]);
}
int getMax(int x,int l,int r,int s,int t)
{
	if(s <= l && r <= t)	return Tree[x];
	int mid = (l + r) >> 1 , ls = x << 1 , rs = ls | 1 , cur = 0;
	PushDown(x,ls,rs);
	if(s <= mid)	cur = max(cur,getMax(ls,l,mid,s,t));
	if(t > mid)	cur = max(cur,getMax(rs,mid + 1,r,s,t));
	return cur;
}
void Dp()
{
	for(int c = 1 ; c <= k ; c ++)
	{
		for(int i = 1 ; i <= n ; i ++)
		{ 
			Update(1,1,n,Pre[i] + 1,i);
			f[c][i] = getMax(1,1,n,1,i);
		}
		Build(1,1,n,c);
	}
	printf("%d\n",f[k][n]);
}
int main()
{
	Read();
	Dp();
	return 0;
}
