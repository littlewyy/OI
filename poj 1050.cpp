#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105 , inf = 0x7fffffff;
int n,ans;
int A[MAXN][MAXN];
int Sum[MAXN][MAXN];
void Read()
{
	scanf("%d",&n);
	ans = -inf;
	for(int i = 1 ; i <= n ; i ++)
	{
		for(int j = 1 ; j <= n ; j ++)
		{
			scanf("%d",&A[i][j]);
			Sum[i][j] = Sum[i][j - 1] + A[i][j];
		}
	}
}
void Calc()
{
	for(int i = 1 ; i <= n ; i ++)//左边界 
	{
		for(int j = i ; j <= n ; j ++)//右边界
		{
			int cur = 0;
			for(int k = 1 ; k <= n ; k ++)
			{
				int x = Sum[k][j] - Sum[k][i - 1];
				cur += x;
				ans = max(ans,cur);
				if(cur < 0)	cur = 0;//小于0，对后面一定不优 
			} 
		} 
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("poj 1050.in","r",stdin);
	freopen("poj 1050.out","w",stdout);
	Read();
	Calc();
	return 0;
}
