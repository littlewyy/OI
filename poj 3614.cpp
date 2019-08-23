#include<bits/stdc++.h>
using namespace std;
const int MAXN = 3005;
int n,m;
struct wyy
{
	int l,r;
}A[MAXN];
struct node
{
	int val,num;
}B[MAXN];
void Read()
{
	scanf("%d%d",&n,&m);
	for(int i = 1 ; i <= n ; i ++)	scanf("%d%d",&A[i].l,&A[i].r);
	for(int i = 1 ; i <= m ; i ++)	scanf("%d%d",&B[i].val,&B[i].num);
}
bool cmp(wyy x,wyy y)
{
	return x.r < y.r;
}
bool cmp2(node x,node y)
{
	return x.val < y.val;
}
void Calc()
{
	sort(A + 1 , A + 1 + n , cmp);
	sort(B + 1 , B + 1 + m , cmp2);
	int ans = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		int l = A[i].l , r = A[i].r;
		for(int j = 1 ; j <= m ; j ++)
		{
			if(l <= B[j].val && B[j].val <= r && B[j].num > 0)
			{
				B[j].num --;
				ans ++;
				break;
			}
		}
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("poj 3614.in","r",stdin);
	freopen("poj 3614.out","w",stdout);
	Read();
	Calc();
	return 0;
}
