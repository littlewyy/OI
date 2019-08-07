#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 5E4 + 5 , MAXM = 1E5 + 5;
int n,m,need,mid;
int Fa[MAXN];
struct wyy
{
	int u,v,val,col;
}E[MAXM],Edge[MAXM];
void Read()
{
	scanf("%d%d%d",&n,&m,&need);
	for(int i = 1 ; i <= m ; i ++)
		scanf("%d%d%d%d",&E[i].u,&E[i].v,&E[i].val,&E[i].col);
}
bool cmp(wyy x,wyy y)
{
	if(x.val == y.val)	return x.col < y.col;
	else	return x.val < y.val;
}
int findA(int x)
{
	if(x == Fa[x])	return x;
	return Fa[x] = findA(Fa[x]);
}
void Judge(int add,int &num,int &sum)
{
	num = sum = 0;
	for(int i = 1 ; i <= m ; i ++)
	{
		Edge[i] = E[i];
		if(!Edge[i].col)	Edge[i].val += add;
	}
	sort(Edge + 1 , Edge + 1 + m , cmp);
	for(int i = 0 ; i < n ; i ++)	Fa[i] = i;
	for(int i = 1 ; i <= m ; i ++)
	{
		int u = Edge[i].u , v = Edge[i].v;
		int root1 = findA(u) , root2 = findA(v);
		if(root1 != root2)
		{
			sum += Edge[i].val;
			if(!Edge[i].col)	num ++;
			Fa[root1] = root2;
		}
	}
}
void WQS()
{
	int lo = -105 , hi = 105;//иооб╫Гё©
	int ans = 0x7fffffff;
	while(lo + 1 < hi)
	{
		mid = (lo + hi) >> 1;
		int num,sum;
		Judge(mid,num,sum);
		//printf("%d %d %d\n",mid,num,sum);
		if(num >= need)	ans = min(ans,sum - need * mid) , lo = mid;
		else	hi = mid;
	} 
	printf("%d\n",ans);
}
int main()
{
	freopen("bzoj 2654.in","r",stdin);
	freopen("bzoj 2654.out","w",stdout);
	Read();
	WQS();
	return 0;
}
