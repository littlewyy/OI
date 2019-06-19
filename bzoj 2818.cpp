#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
long long typedef LL;
const int MAXN = 1E7 + 5;
int n,p;
int Miu[MAXN],Prime[MAXN / 10],Sum[MAXN],SumMiu[MAXN];
bool Vis[MAXN];
void GetMiu()
{
	Miu[1] = 1 , Vis[1] = 1;
	for(int i = 2 ; i <= 1e7 ; i ++)
	{
		if(!Vis[i])	Prime[++ p] = i , Miu[i] = -1;
		for(int j = 1 ; j <= p ; j ++)
		{
			LL tar = i * (LL)Prime[j];
			if(tar > 1e7)	break;
			Vis[tar] = 1;
			if(i % Prime[j])	Miu[tar] = - Miu[i];
			else	{Miu[tar] = 0; break;}
		}
	} 
}
LL f(int a)
{
	LL ans = 0;
	for(int d = 1 , end ; d <= a ; d = end + 1)
	{
		end = a / (a / d);
		ans += LL(SumMiu[end] - SumMiu[d - 1]) * (a / d) * (a / d);
	}
	return ans;
}
void Calc()
{
	scanf("%d",&n);
	for(int i = 1 ; i <= n ; i ++)
		Sum[i] = Sum[i - 1] + (Vis[i] == 0),
		SumMiu[i] = SumMiu[i - 1] + Miu[i];
		//printf("%d %d\n",i,Sum[i]);
	LL ans = 0;
	for(int i = 1 , end ; i <= n ; i = end + 1)
	{
		end = n / (n / i);
		ans += (Sum[end] - Sum[i - 1]) * f(n / i);
	//	printf("%lld\n",ans);
	}
	printf("%lld\n",ans);
}
int main()
{
	freopen("bzoj 2818.in","r",stdin);
	freopen("bzoj 2818.out","w",stdout);
	GetMiu();
	Calc();
	return 0;
}
