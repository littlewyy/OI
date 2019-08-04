#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int MAXN = 4e4 + 5 , MAXK = 55;//看清数据范围。 
int n,k,cur;
int A[MAXN],Pos[MAXN],Next[MAXN];
int f[MAXN][MAXK],Root[MAXN];
int Tree[MAXN * 20],Lson[MAXN * 20],Rson[MAXN * 20];
int Build(int l,int r)
{
	int x = ++ cur;
	if(l == r)	return x;
	int mid = (l + r) >> 1;
	Lson[x] = Build(l,mid);
	Rson[x] = Build(mid + 1,r);
	return x;
}
int Copy(int x)
{
	int y = ++ cur;
	Tree[y] = Tree[x] , Lson[y] = Lson[x] , Rson[y] = Rson[x];
	return y;
}
int Update(int ori,int l,int r,int d)
{
	int x = Copy(ori);
	if(l == d && r == d)
	{
		Tree[x] ++;
		return x;
	}
	int mid = (l + r) >> 1;
	if(d <= mid)	Lson[x] = Update(Lson[x],l,mid,d);
	else	Rson[x] = Update(Rson[x],mid + 1,r,d);
	Tree[x] = Tree[Lson[x]] + Tree[Rson[x]];
	return x;
} 
int getNum(int x,int l,int r,int ql)
{
	if(l >= ql)	return Tree[x];
	int mid = (l + r) >> 1 , cur = 0;
	if(mid >= ql)	cur += getNum(Lson[x],l,mid,ql);
	cur += getNum(Rson[x],mid + 1,r,ql);
	return cur;
}
void Read()
{
	scanf("%d%d",&n,&k);
	for(int i = 1 ; i <= n ; i ++)	scanf("%d",&A[i]);
	for(int i = 1 ; i <= n ; i ++)	Pos[i] = n + 1;
	for(int i = n ; i >= 1 ; i --)	Next[i] = Pos[A[i]] , Pos[A[i]] = i;
}
void Init()
{
	Root[0] = Build(2,n + 1);//从2到n + 1 
	for(int i = 1 ; i <= n ; i ++)
		Root[i] = Update(Root[i - 1],2,n + 1,Next[i]);
}
void Solve(int l,int r,int ll,int lr,int c)
{
	int mid = (l + r) >> 1;	
	int w = 0 , dmid = 0;
	if(lr + 2 <= mid) w = getNum(Root[mid],2,n + 1,mid + 1) - getNum(Root[lr + 1],2,n + 1,mid + 1);
	for(int i = min(lr , mid - 1); i >= ll ; i --)//注意细节：决策集合为[ll,lr]。
	{
		if(Next[i + 1] > mid)	w ++;
		if(f[i][c - 1] + w > f[mid][c])	
		{
			f[mid][c] = f[i][c - 1] + w;
			dmid = i;
		}
	}	
	if(l <= mid - 1)	Solve(l,mid - 1,ll,dmid,c);
	if(mid + 1 <= r)	Solve(mid + 1,r,dmid,lr,c);
}
void Dp()
{
	for(int c = 1 ; c <= k ; c ++)	Solve(1,n,0,n - 1,c);
	printf("%d\n",f[n][k]);
}
int main()
{
	freopen("cf 834D.in","r",stdin);
	freopen("cf 834D.out","w",stdout);
	Read();
	Init();
	Dp();
	return 0;
}
