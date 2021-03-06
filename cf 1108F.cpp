#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int MAXN = 2E5 + 5 , MAXM = 4E5 + 5;
int n,m,ans;
int Fa[MAXN],Maxa[MAXN],Vis[MAXM];
struct wyy
{
	int x,y,val;
}Edge[MAXM];
bool cmp(wyy a,wyy b)
{
	return a.val < b.val;
}
void Read()
{
	scanf("%d%d",&n,&m);
	for(int i = 1 ; i <= m ; i ++)
		scanf("%d%d%d",&Edge[i].x,&Edge[i].y,&Edge[i].val);
}
int findA(int x)
{
	if(x == Fa[x])	return x;
	return Fa[x] = findA(Fa[x]);
}
void Calc()
{
	sort(Edge + 1 , Edge + 1 + m , cmp);
	for(int i = 1 ; i <= n ; i ++)	Fa[i] = i;
	int st = 1 , end = 1;
	while(st <= m)
	{
		while(end < m && Edge[end + 1].val == Edge[st].val)	end ++;
		for(int i = st ; i <= end ; i ++)	
		{
			int x = Edge[i].x , y = Edge[i].y;
			if(findA(x) == findA(y))	Vis[i] = 1;
		}
		for(int i = st ; i <= end ; i ++)
		{
			if(Vis[i])	continue;
			int x = Edge[i].x , y = Edge[i].y , val = Edge[i].val;
			int rootx = findA(x) , rooty = findA(y);
			if(rootx != rooty)	Fa[rootx] = rooty , Maxa[rooty] = val;
			else	if(Maxa[rootx] == val)	ans ++;
		}
		st = end + 1 , end = st;
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("yzc.in","r",stdin);
	freopen("yzc.out","w",stdout);
	Read();
	Calc();	
	return 0;
}
