#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
double eps = 1e-8;
int n,root,Fa[MAXN];
int Sum[MAXN],Num[MAXN],Ori[MAXN];
double Val[MAXN];
vector<int>E[MAXN];
vector<int>Set[MAXN];
void Read()
{
	scanf("%d%d",&n,&root);
	for(int i = 1 ; i <= n ; i ++)	
	{
		scanf("%d",&Sum[i]); 
		Ori[i] = Sum[i];
		Val[i] = (double)Sum[i] , Num[i] = 1;
		Set[i].push_back(i);//操作序列 
	}	
	for(int i = 1 ; i < n ; i ++)
	{
		int fa,x;
		scanf("%d%d",&fa,&x);
		Fa[x] = fa;
		E[fa].push_back(x);
	}
}
void Calc()
{
	for(int i = 1 ; i < n ; i ++)//缩n - 1次点. 
	{
		double std = -1.0;
		int id = -1;
		for(int j = 1 ; j <= n ; j ++)	
		{
			if(j != root && Val[j] - std > eps)//val最大者。 
			{
				std = Val[j];
				id = j;
			}
		}
		if(id != -1)	
		{
			int fa = Fa[id];
			Sum[fa] += Sum[id] , Num[fa] += Num[id];
			Val[fa] = (double)Sum[fa] / (double)Num[fa];//更新权值。
			int size = Set[id].size();
			for(int j = 0 ; j < size ; j ++)
			{
				int cur = Set[id][j];
				Set[fa].push_back(cur);//更新序列 
			}		
			//清走空点。减少空间占用。 
			for(int j = 0 ; j < size ; j ++)	Set[id].pop_back();
				
			size = E[id].size();//修改连边。 
			for(int j = 0 ; j < size ; j ++)
			{
				int cur = E[id][j];
				E[fa].push_back(cur);
				Fa[cur] = fa;//fa也要改. 
			}
			Val[id] = -1.0;
			for(int j = 0 ; j < size ; j ++)	E[id].pop_back();
		}
	}
	int ans = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		int x = Set[root][i - 1];
		ans += Ori[x] * i;
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("poj 2054.in","r",stdin);
	freopen("poj 2054.out","w",stdout);
	Read();
	Calc();
	return 0;
}
