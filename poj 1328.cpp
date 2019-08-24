#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
const double eps = 1e-8 , inf = 0x7fffffff;
int n,dis;
bool ok = true;
struct wyy
{
	double l,r;
	bool operator < (const wyy &t)const
	{
		return r < t.r;
	}
}A[MAXN];
void Read()
{
	scanf("%d%d",&n,&dis);
	for(int i = 1 ; i <= n ; i ++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		if(y > dis)
		{
			ok = false;
			return;
		}
		double del = sqrt(dis * dis - y * y);
		A[i].l = (double)x - del;
		A[i].r = (double)x + del;
	}
}
void Calc()
{
	sort(A + 1 , A + 1 + n);
//	for(int i = 1 ; i <= n ; i ++)	printf("%.4lf %.4lf\n",A[i].l,A[i].r);
	double pos = -inf;
	int ans = 0;
	for(int i = 1 ; i <= n ; i ++)
	{
		if(pos + eps < A[i].l)
		{
			ans ++;
			pos = A[i].r;
		}
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("poj 1328.in","r",stdin);
	freopen("poj 1328.out","w",stdout);
	Read();
	if(ok)	Calc();
	else	printf("-1\n");
	return 0;
}
